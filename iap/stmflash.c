
#include "main.h"
#include "stmflash.h"
#include <stdio.h>			//printf();
#include <string.h>			//�ַ�����

#define u32 uint32_t
#define u16 uint16_t
#define u8 uint8_t

//��ȡָ����ַ����(32λ����) 
//faddr:����ַ 
//����ֵ:��Ӧ����.
u32 STMFLASH_ReadWord(u32 faddr)
{
	return *(__IO uint32_t *)faddr; 
}

//��ȡĳ����ַ���ڵ�flash����
//addr:flash��ַ
//����ֵ:0~11,��addr���ڵ�����


//BANK1  256*FLASH_PAGE_SIZE = 256*2048 =0x80000
//BANK2  256*FLASH_PAGE_SIZE = 256*2048 =0x80000
//BANK1 + BANK2 = 0x100000
//����ַ 0x8000000
// 0x8000000- 0x8007fff Ϊ��������  page 0-0x0f  
//FLASH_PAGE_SIZE

int STMFLASH_GetFlashPage(u32 addr)
{
	uint32_t hpage;
	
	if(addr<0x8000000) return -1;

	printf("\r\naddr=%04x",addr);
	hpage = (addr-0x8000000)/FLASH_PAGE_SIZE;
	
	return hpage;
}


//��ָ����ַ��ʼд��ָ�����ȵ�����
//�ر�ע��:��ΪSTM32F4������ʵ��̫��,û�취���ر�����������,���Ա�����
//         д��ַ�����0XFF,��ô���Ȳ������������Ҳ�������������.����
//         д��0XFF�ĵ�ַ,�����������������ݶ�ʧ.����д֮ǰȷ��������
//         û����Ҫ����,��������������Ȳ�����,Ȼ����������д. 
//�ú�����OTP����Ҳ��Ч!��������дOTP��!
//OTP�����ַ��Χ:0X1FFF7800~0X1FFF7A0F(ע�⣺���16�ֽڣ�����OTP���ݿ�����������д����)
//WriteAddr:��ʼ��ַ(�˵�ַ����Ϊ4�ı���!!)
//pBuffer:����ָ��
//NumToWrite:��(32λ)��(����Ҫд���32λ���ݵĸ���.) 
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
		printf("\r\n�Ƿ���ַ");
		return -1;	//�Ƿ���ַ
	}
	if(WriteAddr<(FLASH_BASE | 0x2000)) //0x8000
	{
		printf("\r\n��������ַ���ɸ�д");
		return -1;	//��������ַ���ɸ�д
	}
	if(WriteAddr & 0x7ff) 
	{
		printf("\r\n��ҳ��ͷ");
		return -1;	//��2kΪһ����Ԫ
	}
	
 	HAL_FLASH_Unlock();             //����	
	addrx=WriteAddr;				//д�����ʼ��ַ
	endaddr=WriteAddr+NumToWrite*4;	//д��Ľ�����ַ


	if(addrx<0X1FFF0000)
	{
		while(addrx<endaddr)		//ɨ��һ���ϰ�.(�Է�FFFFFFFF�ĵط�,�Ȳ���)
		{
			if(STMFLASH_ReadWord(addrx)!=0XFFFFFFFF)//�з�0XFFFFFFFF�ĵط�,Ҫ�����������
			{   
				FlashEraseInit.TypeErase=FLASH_TYPEERASE_PAGES;							//�������ͣ�ҳ���� 
				FlashEraseInit.Banks=FLASH_BANK_1;	   											//Ҫ������BANK
				FlashEraseInit.Page=STMFLASH_GetFlashPage(addrx);     		//Ҫ������Page
				FlashEraseInit.NbPages=1;												//Ҫ��������ҳ��,һҳ		��ҳ:NumToWrite/FLASH_PAGE_SIZE+1; 
				
				if((FlashEraseInit.Page<0x10)||(FlashEraseInit.Page>=256))//0x0f
				{
					printf("\r\n����ҳ�������,%d",FlashEraseInit.Page);
					HAL_FLASH_Lock();           //����
					return -1;
				}
				if(HAL_FLASHEx_Erase(&FlashEraseInit,&SectorError)!=HAL_OK) 
				{
					printf("\r\n����ʧ��");
					HAL_FLASH_Lock();           //����
					return -2;//����������	
				}
			}
			else addrx+=8;
			
			FLASH_WaitForLastOperation(FLASH_WAITETIME);                //�ȴ��ϴβ������
		}
	}
		
  FlashStatus=FLASH_WaitForLastOperation(FLASH_WAITETIME);            //�ȴ��ϴβ������
	
//FLASH_TYPEPROGRAM_DOUBLEWORD	
//FLASH_TYPEPROGRAM_FAST
//FLASH_TYPEPROGRAM_FAST_AND_LAST
	

	if(FlashStatus==HAL_OK)
	{
		while(WriteAddr<endaddr)//д����
		{			
			wrlw=pBuffer[0]+((uint64_t)pBuffer[1]<<32);//0x1234567887654321;//
      if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD,WriteAddr,wrlw)!=HAL_OK)//д������ FLASH_TYPEPROGRAM_FAST
			{ 
				printf("\r\nд���쳣");
				HAL_FLASH_Lock();           //����
				return -2;	//д���쳣
			}
			WriteAddr+=8;//FLASH_NB_DOUBLE_WORDS_IN_ROW * 2 *32;
			pBuffer +=2;  //��Ѱַ,
		}
	}
	HAL_FLASH_Lock();           //����
	return 0;
} 

//��ָ����ַ��ʼ����ָ�����ȵ�����
//ReadAddr:��ʼ��ַ
//pBuffer:����ָ��
//NumToRead:��(32λ)��
void STMFLASH_Read(u32 ReadAddr,u32 *pBuffer,u32 NumToRead)   	
{
	u32 i;
	for(i=0;i<NumToRead;i++)
	{
		pBuffer[i]=STMFLASH_ReadWord(ReadAddr);//��ȡ4���ֽ�.
		ReadAddr+=4;//ƫ��4���ֽ�.	
	}
}

//////////////////////////////////////////������///////////////////////////////////////////
//WriteAddr:��ʼ��ַ
//WriteData:Ҫд�������
void Test_Write(u32 WriteAddr,u32 *WriteData)   	
{
	STMFLASH_Write(WriteAddr,WriteData,2,FLASH_TYPEPROGRAM_FAST_AND_LAST);//д��һ���� FLASH_TYPEPROGRAM_DOUBLEWORD. FLASH_TYPEPROGRAM_FAST_AND_LAST
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

