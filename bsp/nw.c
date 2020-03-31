
//#include "bsp.h"
//#include "nw.h"
#include "sram.h" 
#include <stdio.h>			//printf();
#include <string.h>			//�ַ�����
#include "sram.h" 
#include "iap.h" 
#include "nw.h" 

//extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart3,hlpuart1;


uint8_t sent[20],sent_cnt=0;
int sent_time=0;
uint16_t next_peck=0;
extern uint32_t systime,cnt100ms;


//int CRC16(byte[] Frame, int Length)     // ����ҪУ������������䳤��  
//{
//	byte CRCHi = 0xFF;
//	byte CRCLo = 0xFF;
//	int iIndex = 0;


//	for (int i = 0; i < Length; i++ )
//	{
//			iIndex = CRCLo ^ (Frame[i++]);
//			CRCLo = (byte)(CRCHi ^ aucCRCHi[iIndex]);
//			CRCHi = aucCRCLo[iIndex];
//	}


//	return ( int )( CRCHi << 8 | CRCLo );// CRCУ�鷵��ֵ   // CRCHI �����ƶ��������������Ĵ���            
//}

//unsigned short CRC16_MODBUS(unsigned char *puchMsg, unsigned int usDataLen)  
//{  
//  unsigned short wCRCin = 0xFFFF;  
//  unsigned short wCPoly = 0x8005;  
//  unsigned char wChar = 0;  
//    
//  while (usDataLen--)     
//  {  
//        wChar = *(puchMsg++);  
//        InvertUint8(&wChar,&wChar);  
//        wCRCin ^= (wChar << 8);  
//        for(int i = 0;i < 8;i++)  
//        {  
//          if(wCRCin & 0x8000)  
//            wCRCin = (wCRCin << 1) ^ wCPoly;  
//          else  
//            wCRCin = wCRCin << 1;  
//        }  
//  }  
//  InvertUint16(&wCRCin,&wCRCin);  
//  return (wCRCin) ;  
//}

//unsigned short CRC16(uint16_t c,uint16_t s,uint8_t *in,unsigned int len)
//{
//	uint16_t crc;
//	uint8_t cnt;
//	
//	crc=s;
//	for (unsigned int i = 0; i < len; i++ )
//	{
//		crc = (crc ^(in[i]));
//		for(cnt=0;cnt<8;cnt++)
//		{
//			while(((crc & 0x01)==0)&&(cnt<8))
//			{
//				cnt++;
//				crc = (crc>>1);
//			}
////			cnt++;
//			crc = (crc>>1);
//			crc = (crc ^ c);
//		}
//	}
//	
//	printf("\r\nCRC=%08x",crc);
//}	

//unsigned short CRC16(uint16_t Init,uint16_t Init,uint8_t *in,unsigned int len)
//{
//	uint16_t crc;
//	uint8_t da,flag;
//	
//	crc=s;
//	for (unsigned int i = 0; i < len; i++ )
//	{
//		da=in[i];
//		for (unsigned char cnt = 0; cnt < 8; cnt++ )
//		{
//			if(crc & 0x80)
//			{
//				flag=1;
//			}
//			else flag=0;
//			
//			crc = (crc<<1);
//			if(da & 0x80) crc |= 0x01;
//			da =(da<<8);
//			if(flag) crc ^= c;
//		}
//	}
//	
//	printf("\r\nCRC0=%08x",crc);
//}
//void InvertUint8(uint8_t *out,uint8_t *in)
//{
//	uint8_t temp;
//	temp = *in;
//	
//	for(uint8_t i=0;i<8;i++)
//	{
//		if(temp & 0x01) *out |= 0x01;
//		temp = (temp>>1);
//		*out = (*out<<1);
//	}
//}
//void InvertUint16(uint16_t *out,uint16_t *in)
//{
//	uint16_t temp;
//	
//	temp = *in;
//	
//	for(uint8_t i=0;i<16;i++)
//	{
//		if(temp & 0x01) *out |= 0x01;
//		temp = (temp>>1);
//		*out = (*out<<1);
//	}
//}
//CRC0=5930
//CRC0=ee16
//CRC0=810d
//CRC0=807f
//CRC0=5930
//CRC0=d4d2
//CRC0=2b2d
//CRC0=a6cf

void InvertUint8(unsigned char *dBuf,unsigned char *srcBuf)  
{  
    int i;  
    unsigned char tmp[4];  
    tmp[0] = 0;  
    for(i=0;i< 8;i++)  
    {  
      if(srcBuf[0]& (1 << i))  
        tmp[0]|=1<<(7-i);  
    }  
    dBuf[0] = tmp[0];  
      
}  
void InvertUint16(unsigned short *dBuf,unsigned short *srcBuf)  
{  
    int i;  
    unsigned short tmp[4];  
    tmp[0] = 0;
    for(i=0;i< 16;i++)  
    {  
      if(srcBuf[0]& (1 << i))  
        tmp[0]|=1<<(15 - i);  
    }  
    dBuf[0] = tmp[0];  
}  
unsigned short CRC16_CCITT(unsigned char *puchMsg, unsigned int usDataLen)  
{  
  unsigned short wCRCin = 0x0000;  
  unsigned short wCPoly = 0x1021;  
  unsigned char wChar = 0;  
    
  while (usDataLen--)     
  {  
        wChar = *(puchMsg++);  
        InvertUint8(&wChar,&wChar);  
        wCRCin ^= (wChar << 8);  
        for(int i = 0;i < 8;i++)  
        {  
          if(wCRCin & 0x8000)  
            wCRCin = (wCRCin << 1) ^ wCPoly;  
          else  
            wCRCin = wCRCin << 1;  
        }  
  }  
  InvertUint16(&wCRCin,&wCRCin);  
  return (wCRCin) ;  
}  
unsigned short CRC16_CCITT_FALSE(unsigned char *puchMsg, unsigned int usDataLen)  
{  
  unsigned short wCRCin = 0xFFFF;  
  unsigned short wCPoly = 0x1021;  
  unsigned char wChar = 0;  
    
  while (usDataLen--)     
  {  
        wChar = *(puchMsg++);  
        wCRCin ^= (wChar << 8);  
        for(int i = 0;i < 8;i++)  
        {  
          if(wCRCin & 0x8000)  
            wCRCin = (wCRCin << 1) ^ wCPoly;  
          else  
            wCRCin = wCRCin << 1;  
        }  
  }  
  return (wCRCin) ;  
}  
unsigned short CRC16_XMODEM(unsigned char *puchMsg, unsigned int usDataLen)  
{  
  unsigned short wCRCin = 0x0000;  
  unsigned short wCPoly = 0x1021;  
  unsigned char wChar = 0;  
    
  while (usDataLen--)     
  {  
        wChar = *(puchMsg++);  
        wCRCin ^= (wChar << 8);  
        for(int i = 0;i < 8;i++)  
        {  
          if(wCRCin & 0x8000)  
            wCRCin = (wCRCin << 1) ^ wCPoly;  
          else  
            wCRCin = wCRCin << 1;  
        }  
  }  
  return (wCRCin) ;  
}  
  
unsigned short CRC16_X25(unsigned char *puchMsg, unsigned int usDataLen)  
{  
  unsigned short wCRCin = 0xFFFF;  
  unsigned short wCPoly = 0x1021;  
  unsigned char wChar = 0;  
    
  while (usDataLen--)     
  {  
        wChar = *(puchMsg++);  
        InvertUint8(&wChar,&wChar);  
        wCRCin ^= (wChar << 8);  
        for(int i = 0;i < 8;i++)  
        {  
          if(wCRCin & 0x8000)  
            wCRCin = (wCRCin << 1) ^ wCPoly;  
          else  
            wCRCin = wCRCin << 1;  
        }  
  }  
  InvertUint16(&wCRCin,&wCRCin);  
  return (wCRCin^0xFFFF) ;  
}

unsigned short CRC16_X25_my(unsigned char *puchMsg, unsigned int usDataLen)
{  
  unsigned short wCRCin = 0xFFFF;  
  unsigned short wCPoly = 0x1021;  
  unsigned char wChar = 0;  
    
  while (usDataLen--)     
  {  
        wChar = *(puchMsg++);  
        InvertUint8(&wChar,&wChar);  
        wCRCin ^= (wChar << 8);  
        for(int i = 0;i < 8;i++)  
        {  
          if(wCRCin & 0x8000)  
            wCRCin = (wCRCin << 1) ^ wCPoly;  
          else  
            wCRCin = wCRCin << 1;  
        }  
  }  
//  InvertUint16(&wCRCin,&wCRCin);  
  return (wCRCin^0xFFFF) ;  
} 
  
unsigned short CRC16_MODBUS(unsigned char *puchMsg, unsigned int usDataLen)  
{  
  unsigned short wCRCin = 0xFFFF;  
  unsigned short wCPoly = 0x8005;  
  unsigned char wChar = 0;  
    
  while (usDataLen--)     
  {  
        wChar = *(puchMsg++);  
        InvertUint8(&wChar,&wChar);  
        wCRCin ^= (wChar << 8);  
        for(int i = 0;i < 8;i++)  
        {  
          if(wCRCin & 0x8000)  
            wCRCin = (wCRCin << 1) ^ wCPoly;  
          else  
            wCRCin = wCRCin << 1;  
        }  
  }  
  InvertUint16(&wCRCin,&wCRCin);  
  return (wCRCin) ;  
}  
unsigned short CRC16_IBM(unsigned char *puchMsg, unsigned int usDataLen)  
{  
  unsigned short wCRCin = 0x0000;  
  unsigned short wCPoly = 0x8005;  
  unsigned char wChar = 0;  
    
  while (usDataLen--)     
  {  
        wChar = *(puchMsg++);  
        InvertUint8(&wChar,&wChar);  
        wCRCin ^= (wChar << 8);  
        for(int i = 0;i < 8;i++)  
        {  
          if(wCRCin & 0x8000)  
            wCRCin = (wCRCin << 1) ^ wCPoly;  
          else  
            wCRCin = wCRCin << 1;  
        }  
  }  
  InvertUint16(&wCRCin,&wCRCin);  
  return (wCRCin) ;  
}  
unsigned short CRC16_MAXIM(unsigned char *puchMsg, unsigned int usDataLen)  
{  
  unsigned short wCRCin = 0x0000;  
  unsigned short wCPoly = 0x8005;  
  unsigned char wChar = 0;  
    
  while (usDataLen--)     
  {  
        wChar = *(puchMsg++);  
        InvertUint8(&wChar,&wChar);  
        wCRCin ^= (wChar << 8);  
        for(int i = 0;i < 8;i++)  
        {  
          if(wCRCin & 0x8000)  
            wCRCin = (wCRCin << 1) ^ wCPoly;  
          else  
            wCRCin = wCRCin << 1;  
        }  
  }  
  InvertUint16(&wCRCin,&wCRCin);  
  return (wCRCin^0xFFFF) ;  
}  
unsigned short CRC16_USB(unsigned char *puchMsg, unsigned int usDataLen)  
{  
  unsigned short wCRCin = 0xFFFF;  
  unsigned short wCPoly = 0x8005;  
  unsigned char wChar = 0;  
    
  while (usDataLen--)     
  {  
        wChar = *(puchMsg++);  
        InvertUint8(&wChar,&wChar);  
        wCRCin ^= (wChar << 8);  
        for(int i = 0;i < 8;i++)  
        {  
          if(wCRCin & 0x8000)  
            wCRCin = (wCRCin << 1) ^ wCPoly;  
          else  
            wCRCin = wCRCin << 1;  
        }  
  }  
  InvertUint16(&wCRCin,&wCRCin);  
  return (wCRCin^0xFFFF) ;  
}

unsigned short CRC16_DNP(unsigned char *puchMsg, unsigned int usDataLen)  
{  
  unsigned short wCRCin = 0x0000;  
  unsigned short wCPoly = 0x3d65;  
  unsigned char wChar = 0;  
    
  while (usDataLen--)     
  {  
        wChar = *(puchMsg++);  
        InvertUint8(&wChar,&wChar);  
        wCRCin ^= (wChar << 8);  
        for(int i = 0;i < 8;i++)  
        {  
          if(wCRCin & 0x8000)  
            wCRCin = (wCRCin << 1) ^ wCPoly;  
          else  
            wCRCin = wCRCin << 1;  
        }  
  }  
  InvertUint16(&wCRCin,&wCRCin);  
  return (wCRCin^0xFFFF) ;  
}

unsigned short CRC16_CCITT(unsigned char *puchMsg, unsigned int usDataLen);  
unsigned short CRC16_CCITT_FALSE(unsigned char *puchMsg, unsigned int usDataLen); 
unsigned short CRC16_XMODEM(unsigned char *puchMsg, unsigned int usDataLen); 
unsigned short CRC16_X25(unsigned char *puchMsg, unsigned int usDataLen);
unsigned short CRC16_MODBUS(unsigned char *puchMsg, unsigned int usDataLen);
unsigned short CRC16_IBM(unsigned char *puchMsg, unsigned int usDataLen);
unsigned short CRC16_MAXIM(unsigned char *puchMsg, unsigned int usDataLen);
unsigned short CRC16_USB(unsigned char *puchMsg, unsigned int usDataLen);
// ��������������,У���:03c7,���볤��:331636
//CRC0=c733
//CRC0=ee16
//CRC0=810d
//CRC0=83cf
//CRC0=c733
//CRC0=81c2
//CRC0=7e3d
//CRC0=38cc

//��������������,У���:033a,���볤��:329348
//CRC0=3ad8
//CRC0=a2fb
//CRC0=bdc6
//CRC0=a00c
//CRC0=3ad8
//CRC0=0369
//CRC0=fc96
//CRC0=c527
//CRC0=8b1b
//CRC0=3005

//��������������,У���:03d4,���볤��:8904
//CRC0=d4f0
//CRC0=22b4
//CRC0=8753
//CRC0=42b8
//CRC0=d4f0
//CRC0=497f
//CRC0=b680
//CRC0=2b0f
//CRC0=9fc5
//CRC0=1d42

//��������������,У���:d4f0,���볤��:8904
//CRC0=d4f0
//CRC0=22b4
//CRC0=8753
//CRC0=42b8
//CRC0=d4f0
//CRC0=497f
//CRC0=b680
//CRC0=2b0f
//CRC0=9fc5
//CRC0=1d42
unsigned int checksum_16bit(unsigned char* a,unsigned int n)
{
//	printf("\r\nCRC0=%04x",CRC16_MODBUS(a, n) );
//	printf("\r\nCRC0=%04x",CRC16_CCITT_FALSE(a, n) );
//	printf("\r\nCRC0=%04x",CRC16_XMODEM(a, n) );
//	printf("\r\nCRC0=%04x",CRC16_X25(a, n) );
//		
//	printf("\r\nCRC0=%04x",CRC16_MODBUS(a, n) );
//	printf("\r\nCRC0=%04x",CRC16_IBM(a, n) );
//	printf("\r\nCRC0=%04x",CRC16_MAXIM(a, n) );
//	printf("\r\nCRC0=%04x",CRC16_USB(a, n) );
//	
//	printf("\r\nCRC0=%04x",CRC16_DNP(a, n) );
//	
//	printf("\r\nCRC0=%04x",CRC16_X25_my(a, n) );
	
	return CRC16_MODBUS(a, n);
}

//unsigned int checksum_16bit(unsigned char* a,unsigned int n)
//{
//	unsigned int checksum;
//	unsigned int len;
//	unsigned int i;
//	
//	checksum=0;
//	len=n;
//	
//	if(n & 0x01) 
//	{
//		a[n]=0;
//		len=n+1;
//	}
//	
//	for(i=0;i<len;i+=2)
//	{
//		checksum += (a[i]<<8)+a[i+1];
//	}
//	printf("\r\nchecksum0=%08x",checksum);
//	
//	checksum=0;
//	for(i=0;i<len;i+=2)
//	{
//		checksum += (a[i+1]<<8)+a[i];
//	}
//	printf("\r\nchecksum1=%08x",checksum);
//	
//	checksum=0;
//	for(i=0;i<len;i++)
//	{
//		checksum += a[i];
//	}
//	printf("\r\nchecksum3=%08x",checksum);
//	
//	checksum=~checksum;
//	return checksum;	
//}
//unsigned short checksum_16(unsigned short *addr,int len)
//{
//    unsigned short chksum;
//    unsigned int sum = 0;

//    while(len > 1)
//    {
//        sum += *addr++;
//        len -= 2;
//    }

//    if(len == 1)
//        sum += *(unsigned char*)addr;

//    sum = (sum>>16) + (sum & 0xffff);
//    sum += (sum>>16);
//    chksum = ~sum;
//    return (chksum);
//}

unsigned char checksum_4g(unsigned char* a,unsigned int n)
{
	unsigned char checksum;
	unsigned int i;
	
	checksum=0;
	for(i=0;i<n;i++)
	{
		checksum += a[i];
	}
	checksum=~checksum;
	return checksum;	
}


int get_nw_data(uint8_t **pack_point, uint16_t *pack_len)
{
//	OS_ERR      err;
	uint16_t date_len;
	uint8_t *udata;	//��ȡ�������ݵ�ַ
	uint16_t ulen;	//��ȡ�������ݳ���

	if(ur3_cnt)
	{
		if(ur3_cnt_old==ur3_cnt)
		{
			udata=ur3;
			ulen=ur3_cnt;
		}
		else
		{
			ur3_cnt_old=ur3_cnt;
			return 1;
		}
	}
	else
	{
		return 0;
	}

	if(ulen<12)//10
	{
		printf("\r\ns->m data too short err"); //���ϵ��Ǵβ���		
		return -1;
	}
	
__date_rev:	
//	rdata=udata;
	
	if (0 != memcmp(udata, sent, 7))
	{		
		if(ulen>12)
		{
			(ulen)--;
			udata++;
			goto __date_rev;
		}
		else
		{
			printf("\r\ns->m data stat err");
//			point3_last=point3_now; //����һ������,��һ���ж��Ƿ��м�������
			return -1;	
		}
	}
	
	date_len=(udata[8]<<8)+udata[9]; //���ݳ���
		
	*pack_point=udata;
	*pack_len = date_len+12; //�ȸ������ ���� ���� С�� ����Ҫ��������İ���С
		
	if(*pack_len>lenmax3) //1029+12
	{
		printf("\r\ns->m package length err:");
		return -1;	
	}
	
	if(*pack_len > ulen)
	{
		printf("\r\ns->m data length err:");
		return -1;	
	}
	
	if(udata[date_len+11]!=0x16)
	{
		printf("\r\ns->m data end err");
		return -1;	
	}
	
	if((checksum_4g(&udata[1],date_len+6+1+2)!=udata[date_len+10]))
	{
		printf("\r\ns->m data checksum err");
		return -1;	
	}
		
	printf("\r\nS->M %x,dlen=%d",udata[7],date_len);//systime[3],systime[4],systime[5]
	
	return 2;	//����OK
}

//��ʼ�� װ�ú��� ������ ���ݳ��� ������ У���� ������
//68H 6 �ֽ� FFH 2 �ֽ� 02H 1 �ֽ� 16H

void  nw_sent_data(uint8_t cmd,uint16_t dlen,uint8_t *dbuf) //unsigned char command,unsigned char * t_data,unsigned int dlong
{
	unsigned char i;

//	memcpy(sent,STAA, 7); //����APP1ȷ���� ID ��,���ܴ�������
	sent[0]=0x68;
	strncpy((char *)(&sent[1]), "CC0196",6); // "CC0196" ���ܸ���
	
	sent[7]=cmd;
	sent[8]=(dlen>>8);
	sent[9]=dlen;
	
	for(i=0;i<dlen;i++)
	{
		sent[10+i]=dbuf[i];
	}
	sent[10+dlen]=checksum_4g(&sent[1],9+dlen);
	sent[11+dlen]=0x16;

	HAL_UART_Transmit(&huart3, sent, (12+dlen),100);


	printf("\r\nM->S %x,dlen=%d",cmd,dlen);
}

uint16_t pk_nb=0,tt_pk_nb=0,tt_pk_nb_r=0;

int iap_load_app(uint32_t appxaddr);
int iap_updata(uint32_t appxaddr,uint8_t *appbuf,uint32_t appsize);
uint8_t DTU_OK=0;

//void sent_Contact()
//{
//	uint8_t dbuf[3];
//	dbuf[0]=1;
//	dbuf[1]=0;
//	nw_sent_data(Contact,2,dbuf);
//}

void Rev4g_polling(void * p_arg)
{
	uint8_t *pack_in;
	uint16_t pack_len;
	int ur_err;
	uint8_t cmd;
	uint8_t *data_in;
	uint16_t data_len;
	uint8_t dbuf[6];
	

	if((((systime-sent_time)>=10*5)&&(next_peck==1))||(next_peck==0))//10s��һ��
	{
		if(++sent_cnt>8)//20
		{
			iap_load_app(APP1_ADD);
		}
		else
		{
			sent_time=systime;
			next_peck=1;
			dbuf[0]=0x02;
			nw_sent_data(0xff,1,dbuf);
			
//			dbuf[0]=1;
//			dbuf[1]=0;
//			nw_sent_data(Contact,2,dbuf);
		}
	}	
	ur_err=get_nw_data(&pack_in,&pack_len);

	
	if(ur_err==-1)
	{
		ur3_cnt=0;
	}
	else if(ur_err==2)
	{
		cmd=pack_in[7];
		data_len=(pack_in[8]<<8)+pack_in[9];
		data_in=pack_in+10;

		if((cmd==0xff)&&(data_in[0]==0x02)&&(data_len>5))
		{
			tt_pk_nb_r=(data_in[1]<<8)+data_in[2];
			pk_nb=(data_in[3]<<8)+data_in[4];
			if(next_peck==1)
			{
				tt_pk_nb=tt_pk_nb_r;
			}
				
			if((pk_nb==next_peck)&&(tt_pk_nb_r==tt_pk_nb))
			{
				printf("\r\n�յ���%d��,��%d��",next_peck,tt_pk_nb);
				memcpy(&iap_buf[iap_data_len],&data_in[5], data_len-5);
				iap_data_len += data_len-5;
				next_peck++;
				
				dbuf[0]=0x02;
				dbuf[1]=data_in[3];
				dbuf[2]=data_in[4];
				dbuf[3]=0;
				nw_sent_data(0xff,4,dbuf);
			}
			else
			{
				dbuf[0]=0x02;
				dbuf[1]=data_in[3];
				dbuf[2]=data_in[4];
				dbuf[3]=0xff;
				nw_sent_data(0xff,4,dbuf);
			}
			ur3_cnt=0;
		}
		if((cmd==0xff)&&(data_in[0]==0x03))
		{
			if(next_peck==tt_pk_nb+1)
			{
				uint16_t cheaksum,cheaksum_r;
				cheaksum_r=(data_in[1]<<8)+data_in[2];
				
									
				printf("\r\n��������������,У���:%04x,���볤��:%d",cheaksum_r,iap_data_len);
				cheaksum=checksum_16bit(iap_buf,iap_data_len);
				printf("\r\n����У���:%04x",cheaksum);
				
				if(cheaksum==cheaksum_r)
				{
					while(iap_updata(APP1_ADD,iap_buf,iap_data_len))
					{
						HAL_Delay(1000);
						printf("\r\nд�����");
					}
				}
				for(int i=0;i<lenmax3;i++)
				{
					ur3[i]=0;
				}
				for(int i=0;i<lenmax5;i++)
				{
					ur5[i]=0;
				}
				ur1_cnt=0;
				ur3_cnt=0;
				ur5_cnt=0;
				ur1_cnt_old=0;
				ur3_cnt_old=0;
				ur5_cnt_old=0;
				
				__HAL_UART_DISABLE_IT(&huart3,UART_IT_RXNE);		//���������ж�
//				HAL_NVIC_DisableIRQ(USART3_IRQn);				//ʹ��USART1�ж�ͨ��
//				HAL_NVIC_SetPriority(USART3_IRQn,3,3);			//��ռ���ȼ�3�������ȼ�3
				
				__HAL_UART_DISABLE_IT(&hlpuart1,UART_IT_RXNE);		//���������ж�
//				HAL_NVIC_DisableIRQ(LPUART1_IRQn);				//ʹ��USART1�ж�ͨ��
//				HAL_NVIC_SetPriority(LPUART1_IRQn,3,3);			//��ռ���ȼ�3�������ȼ�3
//				DTU_reset();
				
				iap_load_app(APP1_ADD);
			}
		}
	}
}
//void  nw_sent_8(uint8_t *t_data,uint16_t len) //unsigned char command,unsigned char * t_data,unsigned int dlong
//{


//	HAL_UART_Transmit(&huart3, t_data, len,100);

//	printf("\r\nM->S %x,",t_data[7]);
//}

//void  nw_sent_st(struct nw_ctl *t_data) //unsigned char command,unsigned char * t_data,unsigned int dlong
//{
//	unsigned char i;
//	
//	memcpy(sent,STAA, 7);
//	sent[7]=t_data->cmd;
//	sent[8]=(t_data->len>>8);
//	sent[9]=t_data->len;
//	
//	for(i=0;i<t_data->len;i++)
//	{
//		sent[10+i]=t_data->data[i];
//	}
//	sent[10+t_data->len]=checksum_4g(&sent[1],9+t_data->len);
//	sent[11+t_data->len]=0x16;
////	LastTxT=runningtime;
//	nw_sent_8(sent,(12+t_data->len));
//	
//}
//��ʼ�� װ�ú��� ������ 			���ݳ��� ������ У���� ������
// 68H 	 6 �ֽ� 	FFH 2 �ֽ� 	1 �ֽ� 									16H
//������
//ʶ���� ������λ 	������λ 	�Ӱ��Ÿ�λ �Ӱ��ŵ�λ 	�ļ�����
//02H 		1 �ֽ� 		1 �ֽ� 			1 �ֽ� 			1 �ֽ� 							<=1024 �ֽ�

//��ʼ�� װ�ú��� ������ ���ݳ��� ������ У���� ������
//68H 6 �ֽ� FFH 2 �ֽ� 1 �ֽ� 16H
//������
//ʶ���� �ļ� CRC16
//03H 2 �ֽڣ���λ��ǰ����λ�ں�

//ʶ���� �Ӱ��Ÿ�λ �Ӱ��ŵ�λ ״̬��
//02H 1 �ֽ� 1 �ֽ� 1 �ֽ� 


