
#include "main.h"
#include "stmflash.h"
#include <stdio.h>			//printf();
#include <string.h>			//字符操作

#define u32 uint32_t
#define u16 uint16_t
#define u8 uint8_t

//读取指定地址的字(32位数据) 
//faddr:读地址 
//返回值:对应数据.
u32 STMFLASH_ReadWord(u32 faddr)
{
	return *(__IO uint32_t *)faddr; 
}

//获取某个地址所在的flash扇区
//addr:flash地址
//返回值:0~11,即addr所在的扇区


//BANK1  256*FLASH_PAGE_SIZE = 256*2048 =0x80000
//BANK2  256*FLASH_PAGE_SIZE = 256*2048 =0x80000
//BANK1 + BANK2 = 0x100000
//基地址 0x8000000
// 0x8000000- 0x8007fff 为引导程序  page 0-0x0f  
//FLASH_PAGE_SIZE

int STMFLASH_GetFlashPage(u32 addr)
{
	uint32_t hpage;
	
	if(addr<0x8000000) return -1;

	printf("\r\naddr=%04x",addr);
	hpage = (addr-0x8000000)/FLASH_PAGE_SIZE;
	
	return hpage;
}


//从指定地址开始写入指定长度的数据
//特别注意:因为STM32F4的扇区实在太大,没办法本地保存扇区数据,所以本函数
//         写地址如果非0XFF,那么会先擦除整个扇区且不保存扇区数据.所以
//         写非0XFF的地址,将导致整个扇区数据丢失.建议写之前确保扇区里
//         没有重要数据,最好是整个扇区先擦除了,然后慢慢往后写. 
//该函数对OTP区域也有效!可以用来写OTP区!
//OTP区域地址范围:0X1FFF7800~0X1FFF7A0F(注意：最后16字节，用于OTP数据块锁定，别乱写！！)
//WriteAddr:起始地址(此地址必须为4的倍数!!)
//pBuffer:数据指针
//NumToWrite:字(32位)数(就是要写入的32位数据的个数.) 
int STMFLASH_Write(u32 WriteAddr,u32 *pBuffer,u32 NumToWrite,uint32_t TypeProgram)	
{ 
	FLASH_EraseInitTypeDef FlashEraseInit;
	HAL_StatusTypeDef FlashStatus=HAL_OK;
	u32 SectorError=0;
	u32 addrx=0;
	u32 endaddr=0;	
	uint64_t wrlw;
	
  if(WriteAddr<FLASH_BASE||WriteAddr%4)
	{
		printf("\r\n非法地址");
		return -1;	//非法地址
	}
	if(WriteAddr<(FLASH_BASE | 0x2000)) //0x8000
	{
		printf("\r\n引导区地址不可改写");
		return -1;	//引导区地址不可改写
	}
	if(WriteAddr & 0x7ff) 
	{
		printf("\r\n非页开头");
		return -1;	//以2k为一个单元
	}
	
 	HAL_FLASH_Unlock();             //解锁	
	addrx=WriteAddr;				//写入的起始地址
	endaddr=WriteAddr+NumToWrite*4;	//写入的结束地址


	if(addrx<0X1FFF0000)
	{
		while(addrx<endaddr)		//扫清一切障碍.(对非FFFFFFFF的地方,先擦除)
		{
			if(STMFLASH_ReadWord(addrx)!=0XFFFFFFFF)//有非0XFFFFFFFF的地方,要擦除这个扇区
			{   
				FlashEraseInit.TypeErase=FLASH_TYPEERASE_PAGES;							//擦除类型，页擦除 
				FlashEraseInit.Banks=FLASH_BANK_1;	   											//要擦除的BANK
				FlashEraseInit.Page=STMFLASH_GetFlashPage(addrx);     		//要擦除的Page
				FlashEraseInit.NbPages=1;												//要擦除的总页数,一页		总页:NumToWrite/FLASH_PAGE_SIZE+1; 
				
				if((FlashEraseInit.Page<0x10)||(FlashEraseInit.Page>=256))//0x0f
				{
					printf("\r\n计算页结果超限,%d",FlashEraseInit.Page);
					HAL_FLASH_Lock();           //上锁
					return -1;
				}
				if(HAL_FLASHEx_Erase(&FlashEraseInit,&SectorError)!=HAL_OK) 
				{
					printf("\r\n擦除失败");
					HAL_FLASH_Lock();           //上锁
					return -2;//发生错误了	
				}
			}
			else addrx+=8;
			
			FLASH_WaitForLastOperation(FLASH_WAITETIME);                //等待上次操作完成
		}
	}
		
  FlashStatus=FLASH_WaitForLastOperation(FLASH_WAITETIME);            //等待上次操作完成
	
//FLASH_TYPEPROGRAM_DOUBLEWORD	
//FLASH_TYPEPROGRAM_FAST
//FLASH_TYPEPROGRAM_FAST_AND_LAST
	

	if(FlashStatus==HAL_OK)
	{
		while(WriteAddr<endaddr)//写数据
		{			
			wrlw=pBuffer[0]+((uint64_t)pBuffer[1]<<32);//0x1234567887654321;//
      if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD,WriteAddr,wrlw)!=HAL_OK)//写入数据 FLASH_TYPEPROGRAM_FAST
			{ 
				printf("\r\n写入异常");
				HAL_FLASH_Lock();           //上锁
				return -2;	//写入异常
			}
			WriteAddr+=8;//FLASH_NB_DOUBLE_WORDS_IN_ROW * 2 *32;
			pBuffer +=2;  //字寻址,
		}
	}
	HAL_FLASH_Lock();           //上锁
	return 0;
} 

//从指定地址开始读出指定长度的数据
//ReadAddr:起始地址
//pBuffer:数据指针
//NumToRead:字(32位)数
void STMFLASH_Read(u32 ReadAddr,u32 *pBuffer,u32 NumToRead)   	
{
	u32 i;
	for(i=0;i<NumToRead;i++)
	{
		pBuffer[i]=STMFLASH_ReadWord(ReadAddr);//读取4个字节.
		ReadAddr+=4;//偏移4个字节.	
	}
}

//////////////////////////////////////////测试用///////////////////////////////////////////
//WriteAddr:起始地址
//WriteData:要写入的数据
void Test_Write(u32 WriteAddr,u32 *WriteData)   	
{
	STMFLASH_Write(WriteAddr,WriteData,2,FLASH_TYPEPROGRAM_FAST_AND_LAST);//写入一个字 FLASH_TYPEPROGRAM_DOUBLEWORD. FLASH_TYPEPROGRAM_FAST_AND_LAST
}

extern	u32 iapbuf[512];

void flash_test(void)   	
{
	int i;
	
	iapbuf[0]=0x12345;
	iapbuf[1]=0x54321;
	Test_Write(0x8004000,iapbuf);
	
	STMFLASH_Read(0x8004000,iapbuf,5); 
	printf("\r\n");
	for(i=0;i<10;i++) printf("%04x,",iapbuf[i]);
}

