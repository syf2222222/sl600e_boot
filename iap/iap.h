
#ifndef __IAP_H
#define __IAP_H

#include "stm32l4xx_hal.h"

#define uint8_t unsigned char
#define uint16_t unsigned short
#define uint32_t unsigned int

#define bootlen				0x8000

#define FLASH_BANK1_BASE	0x08000000
#define FLASH_BANK2_BASE	0x08080000

#define Boot_ADD			FLASH_BANK1_BASE
#define APP1_ADD			FLASH_BANK1_BASE+bootlen	// 0x8008000
#define APP2_ADD			FLASH_BANK2_BASE					// 0x8080000

#define APP1_FLASH_MAX  	(APP2_ADD-APP1_ADD)	// 0x80000 为 bank1 max


#define iap_buf_add			FMC_BANK1_1+0x100 		//0X20001000//	FMC_BANK1_1+0x100

#define lenmax1  		APP1_FLASH_MAX				//定义最大接收字节数, 不超过bank1
#define lenmax3			1041//  1041
#define lenmax5			100

extern uint32_t iap_data_len;
extern uint32_t ur1_cnt,ur1_cnt_old;			//接收的字节数

extern uint8_t iap_buf[lenmax1] __attribute__ ((at(iap_buf_add)));//接收缓冲,最大USART_REC_LEN个字节,起始地址为0X20001000.  
extern uint32_t systime,cnt100ms;

extern uint8_t ur5[lenmax5],ur5_cnt,ur5_cnt_old;

extern uint8_t ur3[lenmax3];
extern uint16_t ur3_cnt,ur3_cnt_old;
	





#endif /*__IAP_H */

