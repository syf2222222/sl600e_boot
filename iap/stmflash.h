#ifndef __STMFLASH_H
#define __STMFLASH_H
//#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F429������
//STM32�ڲ�FLASH��д ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2016/1/16
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	

//FLASH��ʼ��ַ
//#define STM32_FLASH_BASE 0x08000000 	//STM32 FLASH����ʼ��ַ
#define FLASH_WAITETIME  50000          //FLASH�ȴ���ʱʱ��

////FLASH ��������ʼ��ַ
//#define ADDR_FLASH_SECTOR_0     ((unsigned int)0x08000000) 	//����0��ʼ��ַ, 16 Kbytes  
//#define ADDR_FLASH_SECTOR_1     ((unsigned int)0x08004000) 	//����1��ʼ��ַ, 16 Kbytes  
//#define ADDR_FLASH_SECTOR_2     ((unsigned int)0x08008000) 	//����2��ʼ��ַ, 16 Kbytes  
//#define ADDR_FLASH_SECTOR_3     ((unsigned int)0x0800C000) 	//����3��ʼ��ַ, 16 Kbytes  
//#define ADDR_FLASH_SECTOR_4     ((unsigned int)0x08010000) 	//����4��ʼ��ַ, 64 Kbytes  
//#define ADDR_FLASH_SECTOR_5     ((unsigned int)0x08020000) 	//����5��ʼ��ַ, 128 Kbytes  
//#define ADDR_FLASH_SECTOR_6     ((unsigned int)0x08040000) 	//����6��ʼ��ַ, 128 Kbytes  
//#define ADDR_FLASH_SECTOR_7     ((unsigned int)0x08060000) 	//����7��ʼ��ַ, 128 Kbytes  
//#define ADDR_FLASH_SECTOR_8     ((unsigned int)0x08080000) 	//����8��ʼ��ַ, 128 Kbytes  
//#define ADDR_FLASH_SECTOR_9     ((unsigned int)0x080A0000) 	//����9��ʼ��ַ, 128 Kbytes  
//#define ADDR_FLASH_SECTOR_10    ((unsigned int)0x080C0000) 	//����10��ʼ��ַ,128 Kbytes  
//#define ADDR_FLASH_SECTOR_11    ((unsigned int)0x080E0000) 	//����11��ʼ��ַ,128 Kbytes 

//#define ADDR_FLASH_SECTOR_12		((unsigned int)0x08100000) 	//����12��ʼ��ַ, 16 Kbytes  
//#define ADDR_FLASH_SECTOR_13		((unsigned int)0x08104000) 	//����13��ʼ��ַ, 16 Kbytes  
//#define ADDR_FLASH_SECTOR_14  	((unsigned int)0x08108000) 	//����14��ʼ��ַ, 16 Kbytes  
//#define ADDR_FLASH_SECTOR_15		((unsigned int)0x0810C000) 	//����15��ʼ��ַ, 16 Kbytes  
//#define ADDR_FLASH_SECTOR_16  	((unsigned int)0x08110000) 	//����16��ʼ��ַ, 64 Kbytes  
//#define ADDR_FLASH_SECTOR_17		((unsigned int)0x08120000) 	//����17��ʼ��ַ, 128 Kbytes  
//#define ADDR_FLASH_SECTOR_18		((unsigned int)0x08140000) 	//����18��ʼ��ַ, 128 Kbytes  
//#define ADDR_FLASH_SECTOR_19		((unsigned int)0x08160000) 	//����19��ʼ��ַ, 128 Kbytes  
//#define ADDR_FLASH_SECTOR_20		((unsigned int)0x08180000) 	//����20��ʼ��ַ, 128 Kbytes  
//#define ADDR_FLASH_SECTOR_21		((unsigned int)0x081A0000) 	//����21��ʼ��ַ, 128 Kbytes  
//#define ADDR_FLASH_SECTOR_22		((unsigned int)0x081C0000) 	//����22��ʼ��ַ, 128 Kbytes  
//#define ADDR_FLASH_SECTOR_23		((unsigned int)0x081E0000) 	//����23��ʼ��ַ, 128 Kbytes   
 
//unsigned int STMFLASH_ReadWord(unsigned int faddr);		  	//������  
//int STMFLASH_Write(unsigned int WriteAddr,unsigned int *pBuffer,unsigned int NumToWrite,unsigned int TypeProgram);		//��ָ����ַ��ʼд��ָ�����ȵ�����
//void STMFLASH_Read(unsigned int ReadAddr,unsigned int *pBuffer,unsigned int NumToRead);   		//��ָ����ַ��ʼ����ָ�����ȵ�����

#endif
