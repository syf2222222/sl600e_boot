/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usart.h"
#include "spi.h"
#include "gpio.h"
#include "fmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
#include <stdio.h>			//printf();
#include <string.h>			//字符操作
#include "sram.h" 
#include "iap.h" 
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
#define     RUN_LED1_ON()			HAL_GPIO_WritePin(GPIOF, GPIO_PIN_7, GPIO_PIN_RESET)
#define     RUN_LED1_OFF()			HAL_GPIO_WritePin(GPIOF, GPIO_PIN_7, GPIO_PIN_SET)
#define     RUN_LED1_Toggle()		HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_7);


void delay(int cnt)
{
	while(cnt) cnt--;
}
///重定向c库函数printf到串口，重定向后可使用printf函数
int fputc(int ch, FILE *f)
{
	
	HAL_UART_Transmit(&huart1,(uint8_t *) &ch, 1, 1000);
	return (ch);
}

int iap_load_app(uint32_t appxaddr);
void flash_test(void);
int iap_updata(uint32_t appxaddr,uint8_t *appbuf,uint32_t appsize);
void Rev4g_polling(void * p_arg);
extern int sent_time;
unsigned int checksum_16bit(unsigned char* a,unsigned int n);
int flash_read(uint8_t *ADD,uint8_t *buf,int len);


uint8_t bootstate=0;
uint32_t iap_data_len;
uint32_t ur1_cnt=0,ur1_cnt_old=0;			//接收的字节数

uint8_t iap_buf[lenmax1] __attribute__ ((at(iap_buf_add)));//接收缓冲,最大USART_REC_LEN个字节,起始地址为0X20001000.  
uint32_t systime=0,cnt100ms=0;

uint8_t ur5[100],ur5_cnt=0,ur5_cnt_old=0;

uint8_t ur3[lenmax3];
uint16_t ur3_cnt=0,ur3_cnt_old=0;

extern uint8_t DTU_OK;


//void HAL_Delay(uint32_t Delay)
//{
//	OS_ERR      err;
//	OSTimeDly ( 2, OS_OPT_TIME_DLY, & err ); 
//}

///////////////////DTU///////////////////////////////////////////////////////
#define		PWR_DTU_ON		GPIO_PIN_SET
#define		PWR_DTU_OFF		GPIO_PIN_RESET

#define		PWR_W_DTU(x)		(((x) == 0) ? HAL_GPIO_WritePin(GPIOF, GPIO_PIN_11, PWR_DTU_OFF) : HAL_GPIO_WritePin(GPIOF, GPIO_PIN_11, PWR_DTU_ON))
#define		PWR_R_DTU()		((HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_11) == PWR_DTU_OFF) ? 0 : 1))

#define		DTU_DTR_ON		GPIO_PIN_RESET
#define		DTU_DTR_OFF		GPIO_PIN_SET

#define		DTU_W_DTR(x)		(((x) == 0) ? HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, DTU_DTR_OFF) : HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, DTU_DTR_ON))

//#define		Wake_up_DTU()			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET)

void DTU_reset(void)
{
	PWR_W_DTU(0);
	DTU_W_DTR(0);	
	printf("\r\nDTUoff");
	HAL_Delay(6000);
	PWR_W_DTU(1);
	DTU_W_DTR(1);	
	printf("\r\nDTUon");
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
//	SCB->VTOR = FLASH_BASE | 0x0000;//设置偏移量	
  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
//	HAL_Init();里面设置中断优先级组
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_FMC_Init();
  MX_SPI2_Init();
  MX_USART3_UART_Init();
  MX_LPUART1_UART_Init();
  /* USER CODE BEGIN 2 */
//#if EN_USART1_RX
	
//#endif	

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	
	printf("\r\n\r\n引导程序,%d,",updata_flag[0]);	
	__HAL_UART_ENABLE_IT(&huart1,UART_IT_RXNE);		//开启接收中断
		HAL_NVIC_EnableIRQ(USART1_IRQn);				//使能USART1中断通道
		HAL_NVIC_SetPriority(USART1_IRQn,4,4);			//抢占优先级3，子优先级3
		
	if(updata_flag[0]==0xaa)		//工作台升级
	{
		printf("\r\n准备接收工作台updata数据");
		updata_flag[0]=0;
		ur1_cnt=0;
		bootstate=2;
		
//		__HAL_UART_ENABLE_IT(&huart3,UART_IT_RXNE);		//开启接收中断
//		HAL_NVIC_EnableIRQ(USART3_IRQn);				//使能USART1中断通道
//		HAL_NVIC_SetPriority(USART3_IRQn,3,3);			//抢占优先级3，子优先级3
//		
//		__HAL_UART_ENABLE_IT(&hlpuart1,UART_IT_RXNE);		//开启接收中断
//		HAL_NVIC_EnableIRQ(LPUART1_IRQn);				//使能USART1中断通道
//		HAL_NVIC_SetPriority(LPUART1_IRQn,3,3);			//抢占优先级3，子优先级3
//		DTU_reset();
	}
	else 
	if(updata_flag[0]==0x55)//||(updata_flag[0]==0xaa))	//南网后台升级 //if(1)//	
	{
		printf("\r\n准备接收4G后台updata数据");
		updata_flag[0]=0;
		ur3_cnt=0;
		bootstate=3;
		
		__HAL_UART_ENABLE_IT(&huart3,UART_IT_RXNE);		//开启接收中断
		HAL_NVIC_EnableIRQ(USART3_IRQn);				//使能USART1中断通道
		HAL_NVIC_SetPriority(USART3_IRQn,3,3);			//抢占优先级3，子优先级3
		
		__HAL_UART_ENABLE_IT(&hlpuart1,UART_IT_RXNE);		//开启接收中断
		HAL_NVIC_EnableIRQ(LPUART1_IRQn);				//使能USART1中断通道
		HAL_NVIC_SetPriority(LPUART1_IRQn,3,3);			//抢占优先级3，子优先级3
		DTU_reset();
		
		flash_read(STAA,STAA,7);
	}
	else
	{
//		printf("\r\n准备接收updata数据");
//		iap_load_app(APP1_ADD);
		bootstate=1; //测试用
	}
		
  while (1)
  {	
//		delay(10000000);
		delay(1000);
		if(HAL_GetTick()>(cnt100ms+100))//if(uwTick>(systime+1000))
		{
			cnt100ms+=100;
			systime++;			
			if(ur1_cnt)
			{
				if(systime%3==0)
				{
					if(ur1_cnt_old==ur1_cnt)
					{
						if((ur1_cnt>=3000)&&(bootstate==2))
						{					
							iap_data_len=ur1_cnt;
							printf("\r\n工作台升级程序接收完成!");
							printf("\r\n代码长度:%d",iap_data_len);
							printf("\r\n计算校验和:%04x",checksum_16bit(iap_buf,iap_data_len));
							
							if(iap_updata(APP1_ADD,iap_buf,iap_data_len)!=0)
							{
								printf("\r\n接收数据错误");
							}
							iap_load_app(APP1_ADD);
						}
						else if(strncmp((char *)iap_buf,"RB",2)==0)
						{
							HAL_NVIC_SystemReset();
						}
						else if(strncmp((char *)iap_buf,"updata",6)==0)
						{
							if(bootstate==1)
							{
								printf("\r\n等待接收程序");
								bootstate=2;
							}
						}
						else
						{
							if(bootstate!=3) iap_load_app(APP1_ADD); 
						}
						ur1_cnt=0;
						systime=0;
					}
					else	
					{
						ur1_cnt_old=ur1_cnt;			
					}
				}
			}
			else
			{		
				if(systime%5==0)
				{
					printf(".");
				}
				if(bootstate==1)
				{
					if(systime>=30) iap_load_app(APP1_ADD);
				}
				else if(bootstate==2)
				{
					if(systime>=300) iap_load_app(APP1_ADD);
				}
				else if(bootstate==3)
				{
					
					if(ur5_cnt)
					{
						if(ur5_cnt_old != ur5_cnt) ur5_cnt_old=ur5_cnt;
						else
						{
							printf("\r\n%s",ur5);
							ur5_cnt=0;
							if ((0 == memcmp("\r\nPB DONE", ur5, sizeof("\r\nPB DONE") - 1))||(0 == memcmp("PB DONE", ur5, sizeof("PB DONE") - 1)))
							{
								DTU_OK=1;
								sent_time=systime;
							}
						}
					}
					if(DTU_OK) Rev4g_polling(0);
	//				if(systime>=150) iap_load_app(APP1_ADD);
				}
			}

			
		}
		

	
		
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 20;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_USART3
                              |RCC_PERIPHCLK_LPUART1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInit.Usart3ClockSelection = RCC_USART3CLKSOURCE_PCLK1;
  PeriphClkInit.Lpuart1ClockSelection = RCC_LPUART1CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure the main internal regulator output voltage 
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
