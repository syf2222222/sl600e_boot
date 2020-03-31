
#include "main.h"
#include "usart.h"
#include "gpio.h"
#include <stdio.h>			//printf();
#include <string.h>			//�ַ�����

#include "sram.h" 
#include "iap.h" 

#define u32 uint32_t
#define u16 uint16_t
#define u8 uint8_t

//void myMain(void) __attribute__((section(".ARM.__at_0x8002000")));

u32 iapbuf[512]; 	//2K�ֽڻ���  
//appxaddr:Ӧ�ó������ʼ��ַ
//appbuf:Ӧ�ó���CODE.
//appsize:Ӧ�ó����С(�ֽ�).
int STMFLASH_Write(u32 WriteAddr,u32 *pBuffer,u32 NumToWrite,uint32_t TypeProgram);
	
int iap_write_appbin(u32 appxaddr,u8 *appbuf,u32 appsize)
{
	u32 t;
	u16 i=0;
	u32 temp;
	u32 fwaddr=appxaddr;//��ǰд��ĵ�ַ
	u8 *dfu=appbuf;
	
	for(t=0;t<appsize;t+=4)
	{						   
		temp=(u32)dfu[3]<<24;   
		temp|=(u32)dfu[2]<<16;    
		temp|=(u32)dfu[1]<<8;
		temp|=(u32)dfu[0];	  
		dfu+=4;//ƫ��4���ֽ�
		iapbuf[i++]=temp;	    
		if(i==512)
		{
			i=0; 
			if(STMFLASH_Write(fwaddr,iapbuf,512,FLASH_TYPEPROGRAM_FAST)!=0)
			{
				return -1;
			}
			fwaddr+=2048;//ƫ��2048  512*4=2048
		}
	} 
	if(i)
	{
		if(STMFLASH_Write(fwaddr,iapbuf,i,FLASH_TYPEPROGRAM_FAST_AND_LAST)!=0) //������һЩ�����ֽ�д��ȥ.  
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
	
	if(DATA_BUF_ADD & 0x03) //�Ǳ�Ҫ����
	{
		printf("\r\n�������ݵĴ洢��ַ�����ֽڶ���");
		return -1;
	}
	
	app_stack_add=(*(volatile uint32_t*)(DATA_BUF_ADD+0));
	app_main_add=(*(volatile uint32_t*)(DATA_BUF_ADD+4));
	
//ջ����ַ:100057a0
//main��ַ:080081d1
	printf("\r\nջ����ַ:%08x",app_stack_add);
	printf("\r\nmain��ַ:%08x",app_main_add);


	if((((app_stack_add>SRAM1_BASE)&&(app_stack_add<SRAM1_BASE+SRAM1_SIZE_MAX))||((app_stack_add>SRAM2_BASE)&&(app_stack_add<SRAM2_BASE+SRAM2_SIZE)))	//�Ѷ���ַ�Ϸ�
	&&(app_main_add>=appxaddr+8)&&(app_main_add<appxaddr+appsize))	//main������ڵ�ַ�Ϸ�  0x8008000- 0x8080000
	{
		if(iap_write_appbin(appxaddr,appbuf,appsize)==0)
		{
			app_stack_add=(*(volatile uint32_t*)(appxaddr+0));
			app_main_add=(*(volatile uint32_t*)(appxaddr+4));
			if((((app_stack_add>SRAM1_BASE)&&(app_stack_add<SRAM1_BASE+SRAM1_SIZE_MAX))||((app_stack_add>SRAM2_BASE)&&(app_stack_add<SRAM2_BASE+SRAM2_SIZE)))	//�Ѷ���ַ�Ϸ�
			&&(app_main_add>=appxaddr+8)&&(app_main_add<appxaddr+appsize))	//main������ڵ�ַ�Ϸ�  0x8008000- 0x8080000
			{
				printf("д��ֵ��ȷ");
			}
		}
		else
		{
			return -1;
		}
	}
	else
	{
		printf("\r\n��ں�����ַ����%08x",*(volatile uint32_t*)(0X20001000+4));
		return -1;
	}
	return 0;
}

//__set_PRIMASK(1)	
//__set_CONTROL(0);		�� MSP /PSP
//#define NVIC_BASE           (SCS_BASE +  0x0100UL)                    /*!< NVIC Base Address */

//				__HAL_UART_DISABLE_IT(&huart3,UART_IT_RXNE);		//���������ж�
// USART3_IRQn                 = 39,     /*!< USART3 global Interrupt     
//				HAL_NVIC_DisableIRQ(USART3_IRQn);				//ʹ��USART1�ж�ͨ��		
//				__HAL_UART_DISABLE_IT(&hlpuart1,UART_IT_RXNE);		//���������ж�
//				HAL_NVIC_DisableIRQ(LPUART1_IRQn);				//ʹ��USART1�ж�ͨ��

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
	if((((*(volatile uint32_t*)appxaddr)&0x2FFE0000)==0x20000000)||(((*(volatile uint32_t*)appxaddr)&0x1FFE0000)==0x10000000))	//���ջ����ַ�Ƿ�Ϸ�.
	{
		printf("\r\nת��%08x",appxaddr);
		jump2app=(void(*)())*(volatile uint32_t*)(appxaddr+4);		//�û��������ڶ�����Ϊ����ʼ��ַ(��λ��ַ)		
		__set_MSP(*(volatile uint32_t*) appxaddr);//��ʼ��APP��ջָ��(�û��������ĵ�һ�������ڴ��ջ����ַ)
		
		for(int i = 0; i < 8; i++)
		{
			NVIC->ICER[i] = 0xFFFFFFFF;	/* �ر��ж�*/ //��Ϊ�ж�ͨ��
			NVIC->ICPR[i] = 0xFFFFFFFF;	/* ����жϱ�־λ */
		}
		jump2app();									//��ת��APP.
		
		printf("\r\nת��%08xû�ɹ�?",appxaddr);
	}
	else
	{
		printf("\r\niapջ����ַ����");
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
 
//��ת��Ӧ�ó����
//appxaddr:�û�������ʼ��ַ.

//��STM32�е�sys.c�ļ����뱨���������ʱ��

//__ASM void MSR_MSP(u32 addr)
//{
//MSR MSP, r0 //set Main Stack value
//BX r14
//}

//���������������д���Ļ����Ǿ��޸ĳ���������Ӧ�þ�û����

//void MSR_MSP(uint32_t addr)
//{
//	__ASM volatile("MSR MSP, r0"); 
//	__ASM volatile("BX r14");
//}




