
#ifndef  __POWER_H
#define  __POWER_H

#define     RUN_LED1_ON()			HAL_GPIO_WritePin(GPIOF, GPIO_PIN_7, GPIO_PIN_RESET)
#define     RUN_LED1_OFF()			HAL_GPIO_WritePin(GPIOF, GPIO_PIN_7, GPIO_PIN_SET)
#define     RUN_LED1_Toggle()		HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_7);


///////////////////12V///////////////////////////////////////////////////////
#define		PWR_12V_ON		GPIO_PIN_RESET
#define		PWR_12V_OFF		GPIO_PIN_SET

//12V�ܿ���
#define		PWR_W_12V(x)		(((x) == 0) ? HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, PWR_12V_OFF) : HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, PWR_12V_ON))
#define		PWR_R_12V()		((HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_5) == PWR_12V_OFF) ? 0 : 1))

//��Ҫ��������������
#define		PWR_W_12V1(x)		(((x) == 0) ? HAL_GPIO_WritePin(GPIOG, GPIO_PIN_15, PWR_12V_OFF) : HAL_GPIO_WritePin(GPIOG, GPIO_PIN_15, PWR_12V_ON))
#define		PWR_R_12V1()		((HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_15) == PWR_12V_OFF) ? 0 : 1))

//��Ҫ������ɽ������
#define		PWR_W_12V2(x)		(((x) == 0) ? HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, PWR_12V_OFF) : HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, PWR_12V_ON))
#define		PWR_R_12V2()		((HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_14) == PWR_12V_OFF) ? 0 : 1))

//��Ҫ����������Ǵ�����
#define		PWR_W_12V3(x)		(((x) == 0) ? HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, PWR_12V_OFF) : HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, PWR_12V_ON))
#define		PWR_R_12V3()		((HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_6) == PWR_12V_OFF) ? 0 : 1))

//#define		PWREN_12V()				HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_RESET)	//12V�ܿ���
//#define		PWRDIS_12V()			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_SET)
////#define		PWREN_12V1()			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET)	//��Ҫ��������������
////#define		PWRDIS_12V1()			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET)
////#define		PWREN_12V2()			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET)	//��Ҫ������ɽ������
////#define		PWRDIS_12V2()			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET)
//#define		PWREN_12V3()			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_RESET)	//��Ҫ����������Ǵ�����
//#define		PWRDIS_12V3()			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_SET)



///////////////////ETH///////////////////////////////////////////////////////
#define		PWR_ETH_ON		GPIO_PIN_SET
#define		PWR_ETH_OFF		GPIO_PIN_RESET

#define		PWR_W_ETH(x)		(((x) == 0) ? HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, PWR_ETH_OFF) : HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, PWR_ETH_ON))
#define		PWR_R_ETH()		((HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_12) == PWR_ETH_OFF) ? 0 : 1))

//#define		PWREN_ETH()		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, PWR_ETH_ON)
//#define		PWRDIS_ETH()		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, PWR_ETH_OFF)


///////////////////485///////////////////////////////////////////////////////

#define		PWR_485_ON		GPIO_PIN_SET
#define		PWR_485_OFF		GPIO_PIN_RESET

#define		PWR_W_485(x)		(((x) == 0) ? HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, PWR_485_OFF) : HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, PWR_485_ON))
#define		PWR_R_485()		((HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) == PWR_485_OFF) ? 0 : 1))

//#define		PWREN_485()				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET)
//#define		PWRDIS_485()			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET)


///////////////////DTU///////////////////////////////////////////////////////
#define		PWR_DTU_ON		GPIO_PIN_SET
#define		PWR_DTU_OFF		GPIO_PIN_RESET

#define		PWR_W_DTU(x)		(((x) == 0) ? HAL_GPIO_WritePin(GPIOF, GPIO_PIN_11, PWR_DTU_OFF) : HAL_GPIO_WritePin(GPIOF, GPIO_PIN_11, PWR_DTU_ON))
#define		PWR_R_DTU()		((HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_11) == PWR_DTU_OFF) ? 0 : 1))

#define		DTU_DTR_ON		GPIO_PIN_RESET
#define		DTU_DTR_OFF		GPIO_PIN_SET

#define		DTU_W_DTR(x)		(((x) == 0) ? HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, DTU_DTR_OFF) : HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, DTU_DTR_ON))

//#define		Wake_up_DTU()			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET)



///////////////////CAM///////////////////////////////////////////////////////
#define		PWR_CAM_ON		GPIO_PIN_RESET
#define		PWR_CAM_OFF		GPIO_PIN_SET

#define		PWR_W_CAM1(x)		(((x) == 0) ? HAL_GPIO_WritePin(GPIOG, GPIO_PIN_9, PWR_CAM_OFF) : HAL_GPIO_WritePin(GPIOG, GPIO_PIN_9, PWR_CAM_ON))
#define		PWR_R_CAM1()		((HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_9) == PWR_CAM_OFF) ? 0 : 1))

//#define		PWRDIS_CAMERA1()		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_9, GPIO_PIN_SET)
//#define		PWREN_CAMERA1()		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_9, GPIO_PIN_RESET)

#define		PWR_W_CAM2(x)		(((x) == 0) ? HAL_GPIO_WritePin(GPIOG, GPIO_PIN_10, PWR_CAM_OFF) : HAL_GPIO_WritePin(GPIOG, GPIO_PIN_10, PWR_CAM_ON))
#define		PWR_R_CAM2()		((HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_10) == PWR_CAM_OFF) ? 0 : 1))

//#define		PWRDIS_CAMERA2()		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_10, GPIO_PIN_SET)
//#define		PWREN_CAMERA2()		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_10, GPIO_PIN_RESET)

//#define		camera_on(x)		(((x) == 1) ? PWREN_CAMERA1_L() : PWREN_CAMERA2_L())
//#define		camera_off(x)		(((x) == 1) ? PWREN_CAMERA1_H() : PWREN_CAMERA2_H())


void power_init(void);
void mode_4G_init(void);
void mode_485_init(void);	
void camera_on(char ch);
void camera_off(char ch);

void DTU_reset(void);

extern unsigned char power1_camera1,power1_camera2;
	
#endif /* __POWER_H */


