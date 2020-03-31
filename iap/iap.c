
#include "main.h"
#include "usart.h"
#include "gpio.h"
#include <stdio.h>			//printf();
#include <string.h>			//字符操作

#include "sram.h" 
#include "iap.h" 

#define u32 uint32_t
#define u16 uint16_t
#define u8 uint8_t

//void myMain(void) __attribute__((section(".ARM.__at_0x8002000")));

u32 iapbuf[512]; 	//2K字节缓存  
//appxaddr:应用程序的起始地址
//appbuf:应用程序CODE.
//appsize:应用程序大小(字节).
int STMFLASH_Write(u32 WriteAddr,u32 *pBuffer,u32 NumToWrite,uint32_t TypeProgram);
	
int iap_write_appbin(u32 appxaddr,u8 *appbuf,u32 appsize)
{
	u32 t;
	u16 i=0;
	u32 temp;
	u32 fwaddr=appxaddr;//当前写入的地址
	u8 *dfu=appbuf;
	
	for(t=0;t<appsize;t+=4)
	{						   
		temp=(u32)dfu[3]<<24;   
		temp|=(u32)dfu[2]<<16;    
		temp|=(u32)dfu[1]<<8;
		temp|=(u32)dfu[0];	  
		dfu+=4;//偏移4个字节
		iapbuf[i++]=temp;	    
		if(i==512)
		{
			i=0; 
			if(STMFLASH_Write(fwaddr,iapbuf,512,FLASH_TYPEPROGRAM_FAST)!=0)
			{
				return -1;
			}
			fwaddr+=2048;//偏移2048  512*4=2048
		}
	} 
	if(i)
	{
		if(STMFLASH_Write(fwaddr,iapbuf,i,FLASH_TYPEPROGRAM_FAST_AND_LAST)!=0) //将最后的一些内容字节写进去.  
		{
			return -1;
		}
	}
	return 0;
}

uint32_t app_stack_add,app_main_add;

int iap_updata(u32 appxaddr,u8 *appbuf,u32 appsize)
{
	uint32_t DATA_BUF_ADD;
	
	DATA_BUF_ADD = (uint32_t)appbuf;
	
	if(DATA_BUF_ADD & 0x03) //非必要条件
	{
		printf("\r\n升级数据的存储地址非四字节对齐");
		return -1;
	}
	
	app_stack_add=(*(volatile uint32_t*)(DATA_BUF_ADD+0));
	app_main_add=(*(volatile uint32_t*)(DATA_BUF_ADD+4));
	
//栈顶地址:100057a0
//main地址:080081d1
	printf("\r\n栈顶地址:%08x",app_stack_add);
	printf("\r\nmain地址:%08x",app_main_add);


	if((((app_stack_add>SRAM1_BASE)&&(app_stack_add<SRAM1_BASE+SRAM1_SIZE_MAX))||((app_stack_add>SRAM2_BASE)&&(app_stack_add<SRAM2_BASE+SRAM2_SIZE)))	//堆顶地址合法
	&&(app_main_add>=appxaddr+8)&&(app_main_add<appxaddr+appsize))	//main函数入口地址合法  0x8008000- 0x8080000
	{
		if(iap_write_appbin(appxaddr,appbuf,appsize)==0)
		{
			app_stack_add=(*(volatile uint32_t*)(appxaddr+0));
			app_main_add=(*(volatile uint32_t*)(appxaddr+4));
			if((((app_stack_add>SRAM1_BASE)&&(app_stack_add<SRAM1_BASE+SRAM1_SIZE_MAX))||((app_stack_add>SRAM2_BASE)&&(app_stack_add<SRAM2_BASE+SRAM2_SIZE)))	//堆顶地址合法
			&&(app_main_add>=appxaddr+8)&&(app_main_add<appxaddr+appsize))	//main函数入口地址合法  0x8008000- 0x8080000
			{
				printf("写入值正确");
			}
		}
		else
		{
			return -1;
		}
	}
	else
	{
		printf("\r\n入口函数地址错误%08x",*(volatile uint32_t*)(0X20001000+4));
		return -1;
	}
	return 0;
}

//__set_PRIMASK(1)	
//__set_CONTROL(0);		改 MSP /PSP
//#define NVIC_BASE           (SCS_BASE +  0x0100UL)                    /*!< NVIC Base Address */

//				__HAL_UART_DISABLE_IT(&huart3,UART_IT_RXNE);		//开启接收中断
// USART3_IRQn                 = 39,     /*!< USART3 global Interrupt     
//				HAL_NVIC_DisableIRQ(USART3_IRQn);				//使能USART1中断通道		
//				__HAL_UART_DISABLE_IT(&hlpuart1,UART_IT_RXNE);		//开启接收中断
//				HAL_NVIC_DisableIRQ(LPUART1_IRQn);				//使能USART1中断通道

//__STATIC_INLINE void __NVIC_DisableIRQ(IRQn_Type IRQn)
//{
//  if ((int32_t)(IRQn) >= 0)
//  {
//    NVIC->ICER[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
//    __DSB();
//    __ISB();
//  }
//}

void (*jump2app)();
int iap_load_app(uint32_t appxaddr)
{
	if((((*(volatile uint32_t*)appxaddr)&0x2FFE0000)==0x20000000)||(((*(volatile uint32_t*)appxaddr)&0x1FFE0000)==0x10000000))	//检查栈顶地址是否合法.
	{
		printf("\r\n转入%08x",appxaddr);
		jump2app=(void(*)())*(volatile uint32_t*)(appxaddr+4);		//用户代码区第二个字为程序开始地址(复位地址)		
		__set_MSP(*(volatile uint32_t*) appxaddr);//初始化APP堆栈指针(用户代码区的第一个字用于存放栈顶地址)
		
		for(int i = 0; i < 8; i++)
		{
			NVIC->ICER[i] = 0xFFFFFFFF;	/* 关闭中断*/ //此为中断通道
			NVIC->ICPR[i] = 0xFFFFFFFF;	/* 清除中断标志位 */
		}
		jump2app();									//跳转到APP.
		
		printf("\r\n转入%08x没成功?",appxaddr);
	}
	else
	{
		printf("\r\niap栈顶地址错误");
		return -1;
	}
	return 0;
}

//void Jump_Address(void)
//{
//if (((*(volatile u32*)ApplicationAddress) & 0x2FFE0000 )== 0x20000000)
//{
//test = (*(volatile u32*)ApplicationAddress);
//JumpAddress = *(volatile u32*) (ApplicationAddress + 4);
//Jump_To_Application = (pFunction) JumpAddress;
//__set_MSP(*(volatile u32*) ApplicationAddress);
//              Jump_To_Application();
//}
//}


//#define appxaddr	0x8002000
 
//跳转到应用程序段
//appxaddr:用户代码起始地址.

//在STM32中的sys.c文件编译报出这个错误时：

//__ASM void MSR_MSP(u32 addr)
//{
//MSR MSP, r0 //set Main Stack value
//BX r14
//}

//如果你上上面那种写法的话，那就修改成下面这种应该就没事了

//void MSR_MSP(uint32_t addr)
//{
//	__ASM volatile("MSR MSP, r0"); 
//	__ASM volatile("BX r14");
//}




