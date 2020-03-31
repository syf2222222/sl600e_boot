

#ifndef	__GLOBAL_H
#define	__GLOBAL_H

#ifdef   NW_MODULE
#define  GLOBAL_EXT
#else
#define  GLOBAL_EXT  extern
#endif



#include 	"stdint.h"		//uint ����

#include <stdio.h>			//printf();
#include <string.h>			//�ַ�����

#include <main.h>			//������ЩHAL����
#include <power_ctrl.h>			

//#include "stm32l4xx_hal_def.h"
//extern void UART_data_clear(UART_HandleTypeDef *huart);	
//char UART_Receive(UART_HandleTypeDef *huart,uint8_t **pack_point, uint16_t *pack_len,int wait_time);
//char UART_Receive_s(UART_HandleTypeDef *huart,uint8_t **pack_point, uint16_t *pack_len,int time_out);

#define	data_flag00				0x0001
#define	data_flag01				0x0002
#define	data_flag05				0x0004
#define	data_flag05_ok		0x0008

#define	data_flag06				0x0010
#define	data_flag0a				0x0020
#define	data_flag22				0x0040
#define	data_flag25				0x0080

#define	data_flag84_1		0x0100		//��������
#define	data_flag86_1		0x0200		//���ͽ���
#define	data_flag84_2		0x0400		//��������
#define	data_flag86_2		0x0800		//���ͽ���

#define	data_flag81_1		0x1000		//����ͼ�����
#define	data_flag81_2		0x2000		//����ͼ�����


GLOBAL_EXT uint32_t	senttask_Asim;	//assignment  �����ɵ�����
GLOBAL_EXT uint32_t	senttask_Pend;	//�ȴ����


#define	gat_data_time			0x0001		//
#define	gat_a_ll_req			0x0002		//
GLOBAL_EXT uint32_t	datagettask_Asim;

GLOBAL_EXT uint16_t ll_sent_cnt;
GLOBAL_EXT uint16_t ll_gain_cnt;

GLOBAL_EXT uint16_t qx_sent_cnt;
GLOBAL_EXT uint16_t qx_gain_cnt;

GLOBAL_EXT uint16_t ph_sent_cnt;
GLOBAL_EXT uint16_t ph_gain_cnt;



GLOBAL_EXT uint32_t	hktask_Pend;	//�ȴ����

#define HK_post_max	520
GLOBAL_EXT uint8_t HK_post_buf[HK_post_max+10];//
GLOBAL_EXT uint16_t HK_post_cnt;

//1	0	���������Դ
//2	����Ԥ�õ�	��������ڵ�ָ��Ԥ�õ�
//3	0	���ϵ���1����λ
//4	0	���µ���1����λ
//5	0	�������1����λ
//6	0	���ҵ���1����λ
//7	0	������Զ������1����λ����ͷ�䱶�Ŵ�
//8	0	�������������1����λ
//����ͷ�䱶��С��
//9	��������Ԥ�õ�	���浱ǰλ��ΪĳԤ�õ�
//10	�ر��������Դ	
//11		��Ȧ�Ŵ�1����λ
//12		��Ȧ��С1����λ
//13		�۽�����1����λ
//14		�۽�����1����λ
//15	Ѳ����	��ʼѲ��
//16	Ѳ����	ֹͣѲ��
//17	�������غ�	�򿪸�������
//18	�������غ�	�رո�������
//19	0	��ʼ�Զ�ɨ��
//20	0	ֹͣ�Զ�ɨ��
//21	0	��ʼ���ɨ��
//22	0	ֹͣ���ɨ��
//23	0	�����ȫ��
//24	0	����ư뿪
//25	0	����ƹر�
//26 	����Ԥ��λ��	ɾ��Ԥ��λ��
//27	0	�����Զ�ɨ����߽�
//28	0	�����Զ�ɨ���ұ߽�
//29	0	�����Զ�ɨ���ٶȣ�1-10������
//30	ÿ��λ�Ĳ���	������̨�������ҵ���ʱ����1����λ���Ĳ�����
//31	Ѳ�����	��ʼѲ��
//32	Ѳ�����	ֹͣѲ��
//48	0	ֹͣ���������
//49	�ٶ�	��ʼ����������˶�
//50	�ٶ�	��ʼ����������˶�
//51	�ٶ�	��ʼ����������˶�
//52	�ٶ�	��ʼ����������˶�
//53	�ٶ�	��ʼ������������˶�
//54	�ٶ�	��ʼ������������˶�
//55	�ٶ�	��ʼ������������˶�
//56	�ٶ�	��ʼ������������˶�
//57	0	��ʼ�����������Զ�����ڣ���ͷ�䱶�Ŵ�
//58	0	��ʼ�����������������ڣ���ͷ�䱶��С�� 
//59	�ٶ�	��ʼ�������Ȧ�Ŵ�
//60	�ٶ�	��ʼ�������Ȧ��С
//61	�ٶ�	��ʼ������۽�����
//62	�ٶ�	��ʼ������۽�����


//����	ͨ����	����ָ��	ָ�����
//4�ֽ�	1�ֽ�		1�ֽ�			1�ֽ�

//0x88ָ���µ� ָ�� 1-62
#define		hk_pwr_on					1
#define		hk_preset_goto		2
#define		hk_up							3
#define		hk_down						4
#define		hk_left						5
#define		hk_right					6
#define		hk_pwr_off				10
#define		hk_preset					9


#define		hk_par_cfg				0x81		//parameter configuration
#define		hk_get_ph					0x83		//parameter configuration







//uint32_t ask_data_flag;
//uint32_t rep_data_flag;
//typedef 

typedef enum
{
  bempty = 0,
	bpre_bready,
  bready,
	
  bpre_load_hk,
	bloading_hk,
	
	bpre_sent_buf,
  bsenting_buf,
	
} buf_state;


//enum
//{
//  sys_normal = 0,
//	sys_reset_wait,
//  sys_reset_ing,
//	sys_sleep_wait,
//	sys_sleep_ing
//		
//} sys_state;

GLOBAL_EXT buf_state		PH_sram_buf;


typedef struct __NWD_HandleTypeDef
{
	uint16_t        sav_nb;     
	uint16_t        sav_Pt;  
	uint16_t				sav_add;
	buf_state				state;
	
}NWD_HandleTypeDef;

GLOBAL_EXT NWD_HandleTypeDef	hll[3],hqx,hph;

//#define test_mode
//#define test_mode2

#ifdef test_mode
#define		hk_power_on_time	200
#define testdvi	5
#else
#define		hk_power_on_time	10

#ifdef test_mode2
#define testdvi	5
#else
#define testdvi	1
#endif

#endif

#define delayT	10

#define		nw_pk_len		1024 //1460 1040-16
#define		nw_pk_max		200000

#define		y_min		19
#define		y_max		50
#endif	/*__GLOBAL_H*/


#define ur3_rdma


GLOBAL_EXT unsigned char signal,volt;//nw_sent_buf[50],nw_recv_buf[50],
//GLOBAL_EXT unsigned char function_buf[20],function_nub;


int UART_Receive_s(UART_HandleTypeDef *huart,uint8_t **pack_point, uint16_t *pack_len,int time_out);


extern unsigned int runningtime;










