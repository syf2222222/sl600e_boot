#ifndef __NW__H
#define __NW__H

#ifdef   NW_MODULE
#define  NW_EXT
//unsigned char start_and_device_number[7]={0x68,0x43,0x43,0x30,0x31,0x39,0x36};
unsigned char version[2]={3,0};

//	����	4�ֽ�
//	�������	1�ֽ�
//	�ɼ����	2�ֽ�
//	����ʱ��	2�ֽ�
//	����ʱ��	2�ֽ�
//	Ӳ������ʱ���	3�ֽ�
//	������֤��	4�ֽ�
//unsigned char Password[4]={'1','2','3','4'};//
//unsigned char Heabtime=60;//���������װ��������Ϣ���ͼ������λ���ӣ���������ӦΪ1����;
//unsigned short getdatetime=20;//�ɼ��������ÿ�����ٷ��Ӳ���һ�Σ��ɼ����������ʱ���޹أ�����λ���ӣ���������ӦΪ20���ӣ�
//unsigned short sleeptime=0;//����ʱ�������ݲɼ����ܹرջ�ͨ���豸����ʱ�䣬��ʱ���ڿ�֧�ֶ��Ż����绽�ѣ���λ���ӣ���Ϊ0��װ�ò����ߣ�
//unsigned short onlinetime=10;		//����ʱ����ͨ���豸�������ݲɼ�������ͨ���豸����ʱ�䣻��λ���ӣ�
//unsigned char resettime[3]={1,0,0};	//3bye Ӳ������ʱ��㣺Ϊ��֤װ������ɿ�����װ��Ӧ֧�ֶ�ʱ������
//unsigned short checkword[4]={'1','2','3','4'};	//������֤��4�ֽڣ�װ�ó�ʼΪ�ַ���1234����31H32H33H34H����Ϊȷ��װ�����ݵ���ȷ�ԣ���ֹ�Ƿ��û�������ƭ��������
//���������ڷ�ֹ�Ƿ�װ���û������ݱ���վ�Ͽɣ���װʱװ���趨Ĭ�����ģ�������װ��ɺ�
//��վ�·�ָ���޸ĸ�װ�����ģ���װ����վ��¼������һ��ʱ�Ӹ����ݺϷ���Ч���������Ρ�
#else
#define  NW_EXT  extern
//extern	unsigned char start_and_device_number[7];
//extern	unsigned char version[2];

//extern	unsigned char Password[4];//
//extern	unsigned char Heabtime;//���������װ��������Ϣ���ͼ������λ���ӣ���������ӦΪ1����;
//extern	unsigned short getdatetime;//�ɼ��������ÿ�����ٷ��Ӳ���һ�Σ��ɼ����������ʱ���޹أ�����λ���ӣ���������ӦΪ20���ӣ�
//extern	unsigned short sleeptime;//����ʱ�������ݲɼ����ܹرջ�ͨ���豸����ʱ�䣬��ʱ���ڿ�֧�ֶ��Ż����绽�ѣ���λ���ӣ���Ϊ0��װ�ò����ߣ�
//extern	unsigned short onlinetime;		//����ʱ����ͨ���豸�������ݲɼ�������ͨ���豸����ʱ�䣻��λ���ӣ�
//extern	unsigned char resettime[3];	//3bye Ӳ������ʱ��㣺Ϊ��֤װ������ɿ�����װ��Ӧ֧�ֶ�ʱ������
//extern	unsigned short checkword[4];	//������֤��4�ֽڣ�װ�ó�ʼΪ�ַ���1234����31H32H33H34H����Ϊȷ��װ�����ݵ���ȷ�ԣ���ֹ�Ƿ��û�������ƭ��������
#endif



struct aut_get_photo
{
	unsigned char h;
	unsigned char m;
	unsigned char p;   
};

//struct nw_cmd
//{
//	unsigned char cmd;
//	unsigned char cmd_state;
//	unsigned char data;   
//};

struct nw_ctl
{
	unsigned char cmd;
	unsigned int len;
	unsigned char data[50];   
};





//unsigned char cmu[]={0x68,0x43,0x43,0x30,0x31,0x39,0x36,0x00,0x00,0x02,0x03,0x00};
//unsigned char start_and_series[]={0x68,0x43,0x43,0x30,0x31,0x39,0x36,0x00,0x00,0x02,0x03,0x00};
//unsigned char nw_sent_data[72]={0x68,0x43,0x43,0x30,0x31,0x39,0x36,0,0,0,0,0};
//unsigned char device_number[6]={0x43,0x43,0x30,0x31,0x39,0x36};
//unsigned char start_and_device_number[7]={0x68,0x43,0x43,0x30,0x31,0x39,0x36};


#define	Contact								0x00	//	����������Ϣ	װ�ÿ�������������Ϣ
#define CheckT								0x01	//	Уʱ	�������������·�������
#define SetPassword 					0x02	//	����װ������	װ�ó������룺�ַ�����1234����31H32H33H34H��
#define Pcfg 									0x03	//	��վ�·���������	��ָ��Ҫ�����ݲɼ�װ�ý��յ��������ԭ�����
#define HeartBeat 						0x05	//	װ��������Ϣ	������վ���װ������ʱ�䡢IP��ַ�Ͷ˿ںš������ź�ǿ�ȼ����ص�ѹ
#define chang_ip	 						0x06	//	������վIP��ַ���˿ںźͿ���	
#define check_ip 							0x07	//	��ѯ��վIP��ַ���˿ںźͿ���	
#define ResetDev	 						0x08	//	װ�ø�λ	��վ��װ�ý��и�λ
#define waikup_device_m				0x09	//	���Ż���	��վ�Զ��ŷ�ʽ��������״̬��װ��
#define check_device_cfg 			0x0A	//	��ѯװ�����ò���	
#define device_function_cfg		0x0B	//	װ�ù�������	
#define device_Sleep 					0x0C	//	װ������	
#define check_device_time 		0x0D	//	��ѯװ���豸ʱ��	
#define sent_msg					 		0x0E	//	����ȷ�϶���
#define request_data 					0x21	//	��վ����װ������	��վ����ɼ�װ�òɼ����ݲ���������
#define request_la_qj 				0x22	//	�ϴ��������������������	
#define request_qx 						0x25	//	�ϴ���������	

#define	updata_online					0xff	//	����������Ϣ	װ�ÿ�������������Ϣ
/*
#define  0x26 //	�ϴ������¶ȡ����ߵ�������	
#define  0x27 //	�ϴ�����������	
#define  0x29 //	�ϴ��趯���Ƶ������	
#define  0x2A //	�ϴ�������б����	
#define  0x2B //	�ϴ�����΢��������	
#define  0x2C //	�ϴ��ۺϷ�������	
#define  0x2D //	����ɽ�𱨾�����	
#define  0x2E //	���ʹ���趯��������	
#define  0x30 //	�ϴ��豸������Ϣ	
#define  0x31 //	��վ����΢���񶯶�̬����	
#define  0x32 //	΢���񶯶�̬��������	
#define  0x33 //	΢���񶯶�̬�������ͽ������	
#define  0x34 //	΢���񶯶�̬���ݲ����·�	
#define  0x35 //	��վ�����趯��̬����	
#define  0x36 //	�趯��̬��������	
#define  0x37 //	�趯��̬�������ͽ������	
#define  0x38 //	�趯��̬���ݲ����·�	
#define  0x39 //	��վ����������ƫ�Ƕ�̬����	
#define  0x3A //	������ƫ�Ƕ�̬��������	
#define  0x3B //	������ƫ�Ƕ�̬�������ͽ������	
#define  0x3C //	������ƫ�Ƕ�̬���ݲ����·�	
#define  0x41 //	�ϴ��ۻ�����	
#define  0x42 //	�ϴ����߻�������	
#define  0x43 //	�ϴ������¶�����	
#define  0x44 //	�ϴ����»���ӵص�������	
#define  0x45 //	�ϴ����϶�λ����	
#define  0x46 //	�ϴ����¾ַ�����	
#define  0x47 //	�ϴ����¾ַ���ͼ����	
#define  0x60 //	��վ���ù��ϲ���ն˲���	
#define  0x6A //	��վ��ѯ���ϲ���ն˲���	
#define  0x61 //	�ϴ����ϲ���ն˹�������	
#define  0x62 //	�ն�װ������վ�����ϴ���Ƶ���ϲ�������	
#define  0x63 //	�ϴ���Ƶ���ϲ�������	
#define  0x64 //	��Ƶ���ϲ��������ϴ�������־	
#define  0x65 //	��վ���ն˷��͹�Ƶ���ϲ������ݲ���	
#define  0x66 //	�ն�װ������վ�����ϴ������в���������	
#define  0x67 //	�ϴ������в���������	
#define  0x68 //	�����в����������ϴ�������־	
#define  0x69 //	��վ���ն˷����в��������ݲ���	

//#define  0x����Ϊ�ļ����䲿��
71 //	��վ��ѯװ���ļ��б�	
72 //	��վ����װ�������ļ�	
73 //	װ�����������ļ�	
74 //	�ļ�����	
75 //	�ļ����ͽ������	
76 //	�ļ����������·�	
����Ϊͼ����Ƶ��ⲿ��
81 //	ͼ��ɼ���������	��վ�·��ɼ�װ�õ�ɫ��ѡ��ͼ���ߣ����ȣ��Աȶȣ����Ͷȵ���Ϣ
82 //	����ʱ�������	���òɼ�װ���Զ�������Ƭ��ʱ�䡢λ��
83 //	��վ����������Ƭ	�����ֶ�����������Ƭʱʹ��
84 //	�ɼ�װ������������Ƭ	�ɼ�װ�òɼ���ͼ�����ݺ�����վ��������ͼ������������վԭ�����
85 //	ͼ����������	����ͼ���ֺ��N�����ݰ�
86 //	ͼ���������ͽ������	������վ�ж�ͼ�������Ƿ��������
87 //	���������·�	��վ�ӵ�86Hָ��󣬽�������������δ�յ��İ����·����ɼ�װ��
88 //	�����Զ�̵���	�ϡ��¡����ҡ�Զ�������ڣ�Ԥ��λԶ�����á�����
89 //	����������Ƶ����	
8A //	��ֹ������Ƶ����	
8B //	��ѯ����ʱ���	
8C //	��Ƶ�ɼ���������	
8D //	��Ƶ�ɼ�������ѯ	
8E //	OSD��������	
8F //	OSD������ѯ	
90 //	¼����Բ�������	
91 //	¼����Բ�����ѯ	
92 //	ͨ��¼��״̬��ѯ	
93 //	��վ�����������Ƶ	
94 //	�ɼ��ն��������Ͷ���Ƶ	
95 //	����Ƶ��������	
96 //	����Ƶ�������ͽ������	
97 //	����Ƶ���������·�	
98 //	��վ��ѯ�ն�¼���ļ���Ŀ	
99 //	��վ��ѯ�ն�¼���ļ��б�	
9A //	��վ�������¼���ļ��ط�	
9B //	��վ�������¼���ļ��طſ���	
9C //	��վ�������¼���ļ��طŶϿ�	
9D //	��վ�������¼������	
9E //	��վ�������¼���ļ����ضϿ�	
A0 //	����������Ƶ����	
A1 //	��ֹ������Ƶ����	
A2 //	��վ�������ն˽��������㲥	
A3 //	��վ�������ն˶Ͽ������㲥	
A4 //	����������������	
A5 //	��������������ѯ	
A6 //	��·����������	
A7 //	��·��������ѯ	
A8 //	��·Ѳ���������	
A9 //	��·Ѳ�������ѯ	
AA //	���ܷ����澯�ϱ�	
AB //	������������	
AC //	����������ѯ	
AD //	������������Ƶ���Ӳ�������	
AE //	������������Ƶ���Ӳ�����ѯ	
B1 //	�����3D�������	
*/


//HAL_StatusTypeDef HAL_UART_Transmit_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);


//void AppTaskNWS(void);
//LogFlag:�������ã�bit0
//bit7:LOG=80,��ӡ���Ź�������������
//bit6:LOG=40,��ӡ�ļ�ϵͳ���ݴ洢������ģ�����ݳ�ʼ����¼��
//bit5:LOG=20,��ӡ������������������Ϣ
//bit4:LOG=10,��ӡ�����¶�/���������������򡢵�ѹ����ֵ(MCP3202)��������Ϣ
//bit3:LOG=08,����
//bit2:LOG=04,��������ͨ��2
//bit1:LOG=02,��������ͨ��1
//bit0:LOG=01,��ӡ���ݲɼ����

//typedef __packed struct 
//{
//	uint8_t  DtuRunStep;              //ͨ�Ž׶�״̬
//  uint32_t DtuCheckCount;	
//	uint8_t  UpdataFlag;              //��������Ҫ���ͱ�־
//	uint8_t  UpdataType;              //��ͬ���ݷ��ͱ�־
//	uint8_t  SramFlag;               //SDRAM����洢�����Ƿ���Ч��־
//	uint8_t  ConnModeStatus;          //ͨ��ģ�鹤��״̬ ����:0 ���� :1
//	uint8_t  PicSendRetryCount;       //ͼƬ�ϴ����׶ε����Դ���
//	uint8_t  PicSendRetryCycle;       //ͼƬ�ϴ����׶ε���������
//	uint8_t  PicSendFlag;             //ͼƬ���͹��̱�־ 00H: �����ϴ�, 01H: �ϴ�����, 02H: �ϴ�������־, 03H: �ش�
//	uint32_t PicSendIndex;            //ͼƬ�������ݰ���
//	uint8_t  VideoSendRetryCount;      //С��Ƶ�ϴ����׶ε����Դ���
//	uint8_t  VideoSendRetryCycle;      //С��Ƶ�ϴ����׶ε���������
//	uint8_t  VideoSendFlag;            //С��Ƶ���͹��̱�־ 00H: �����ϴ�, 01H: �ϴ�����, 02H: �ϴ�������־, 03H: �ش�
//	uint32_t VideoSendIndex;           //С��Ƶ�������ݰ���
//	uint32_t DtuDisconnect;           //DTUͨ��δ������
//	uint32_t DtuDisconnectTimes;           //DTUͨ��δ������
//  uint16_t DtuRemainingTime;        //DTU���߻�����ʣ��ʱ�� ��λ����
//  uint32_t DtuRemainingTimeCount;
//	uint8_t  dtu_sleep_flag;
//	uint8_t  DtuFirstSleepFlag;
//	uint16_t DtuSubRemainingTime;     //DTU��Դ����ʣ��ʱ��   ��λ����
//	uint8_t  DtuPwr;	                 //DTU��Դ���� 1:��; 0: �ر�
//	uint8_t  DtuWorkStatus;           //DTU����״̬ 1:����;0:����
//  uint8_t  UpdataChannl[3];            //��Ҫ�ϴ���ͨ��

//	uint16_t  Voltage;                 //���ص�ѹ
//	uint32_t HeartBeatCount;
//  uint32_t HeartRemaingTime;        //����ʣ��ʱ��          
//  uint8_t  SoftSwitchEnable;        //�����л���־
//	uint8_t  LogFlag;                 //��������
//	uint8_t  RtcTime[6];              //Year,Month,Date,Hours,Minutes,Seconds
//	uint32_t RtcSubSecond;
//	uint8_t  ChannelSelect;           //���ͨ��ѡ��
//	uint16_t CameraPowerResidue[2];      //�����Դ����(�������),��Դ��ر�ʱ��,
//	uint32_t CameraPowerResidueCount[2];  //�����Դ����(�������),��Դ��ر�ʱ��,
//	uint16_t  ModulePowerResidue;      //��������Դ����(�������),��Դ��ر�ʱ��,��λ:30S
//	uint32_t  OversampleTime;          //ģ�������ʱ��, ��λ: ��	
//	uint8_t  PitureStoreFlag;         //ͼƬ�洢��־
//	uint8_t  PicureSearchFlag;        //ͼƬ������־
//	uint8_t  SdPictureNum;
//	uint8_t  NoSignalFlag;            //û���źţ��ܹ��յ����������ؼ�OK
//  uint8_t  NoSignalFlagOld;
//	uint8_t  DtuSignal;               //DTU�ź�ǿ��	
//	uint8_t time_camera_schedule_count[2];  //��ʱ��������¼	
//	uint8_t time_continuous_flag[2]; //��������ı�?
//	uint32_t continuous_capture_prev[2];//���ĳ�ʱ��־
//	uint8_t schedule_total[2];//���ձ�ÿ��ʱ��ε���������		
//	uint8_t FaultTimerFlag;	
//	uint8_t camera_preset ;
//	uint8_t camera_channel ;
//	uint32_t SD_noraml_volume;//SD������
//	float display_Voltage;//��ѹ��ӡ��Ϣ

//	uint8_t  dtu_config_flag;

//  uint32_t UpdataRecordTime;             //��ʷ��¼����ʱ����
//	uint8_t take_photos_type;   //��������
//	uint8_t record_new_picture; //��¼�µ���Ƭ
//	uint8_t sampling_self_checking_flag;//�Լ����
//	uint8_t Camera_waiting_time;//����ȴ�ʱ�� 
//	uint8_t SamplingMboxData[3];//�������ɼ�
//	uint8_t read_towerangle_flag;
//	uint8_t ModuleBusyFlag;
//	uint8_t SamplingStartFlag;//�������ɼ���־
//	uint8_t  RainfallCounter;//����������
//	uint8_t MPSample_Start_End_Flag;//MP�ɼ���ʼ��ֹͣ
//	
//	uint8_t  Cruise_Serial_Num;
//	uint8_t Cruise_cmd[2];//Ѳ����������
//	uint8_t group_number[2];//Ѳ����������
//	uint8_t video_time[2];//�������ʱ��
//	uint8_t record_new_socket_flag;//¼������socket��־

//	uint16_t video_time_count[2];//¼��ʱ�����
//  uint32_t video_time_prev[2];
//	uint32_t file_num_index;//¼���б��ļ�����
//	uint32_t file_num_size;//¼���б��ļ���С
//	uint8_t  time_video_type[2];//��ʱ¼������
//	uint8_t  time_video_parameter[2];//��ʱ¼�����
//	uint16_t mdat_nalu_count;//MP4 mdat ���ݳ���
//	uint16_t mdat_nalu_count_add;//MP4 mdat ���ݳ��� ��������֡��ֻ�п�ͷ��û�н���
//  uint32_t mdat_data_total_num;//MP4 mdat ���ݴ�С
//	uint32_t ftyp_moov_boox_offset;//Mp4�ļ�ͷ��ƫ����
//	uint8_t  camere_set_flag;//���������־
//	uint16_t camera_live_open_time[2];//ʵʱ��Ƶ����ʱ��
//	uint16_t dtu_recieve_count;//DTU���յȴ�ʱ��
//	
//	
//	uint8_t camera_busy_log[2];//���æ��־	
//	uint8_t test_dayin_flag;//���Դ�ӡ��Ϣ
//}SysValue;

//unsigned char Password[4]={'1','2','3','4'};//
//unsigned char Heabtime=60;//���������װ��������Ϣ���ͼ������λ���ӣ���������ӦΪ1����;
//unsigned short getdatetime=20;//�ɼ��������ÿ�����ٷ��Ӳ���һ�Σ��ɼ����������ʱ���޹أ�����λ���ӣ���������ӦΪ20���ӣ�
//unsigned short sleeptime=0;//����ʱ�������ݲɼ����ܹرջ�ͨ���豸����ʱ�䣬��ʱ���ڿ�֧�ֶ��Ż����绽�ѣ���λ���ӣ���Ϊ0��װ�ò����ߣ�
//unsigned short onlinetime=10;		//����ʱ����ͨ���豸�������ݲɼ�������ͨ���豸����ʱ�䣻��λ���ӣ�
//unsigned int resettime;	//3bye  Ӳ������ʱ��㣺Ϊ��֤װ������ɿ�����װ��Ӧ֧�ֶ�ʱ������
//unsigned short checkword[4]={'1','2','3','4'};	//������֤��4�ֽڣ�װ�ó�ʼΪ�ַ���1234����31H32H33H34H����Ϊȷ��װ�����ݵ���ȷ�ԣ���ֹ�Ƿ��û�������ƭ��������
////���������ڷ�ֹ�Ƿ�װ���û������ݱ���վ�Ͽɣ���װʱװ���趨Ĭ�����ģ�������װ��ɺ�
////��վ�·�ָ���޸ĸ�װ�����ģ���װ����վ��¼������һ��ʱ�Ӹ����ݺϷ���Ч���������Ρ�
#endif  /* __NW__H */

