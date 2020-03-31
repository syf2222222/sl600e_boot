
//#include "bsp.h"
//#include "nw.h"
#include "sram.h" 
#include <stdio.h>			//printf();
#include <string.h>			//字符操作

void data_rst(void)
{
//	char i,buf[20];
	printf("\r\n重写数据");
	*STAA=0x68;

	strncpy((char *)TID, "CC019612341234",14);

	*SV=1;
	*HBT=1;
	*GDT=10;
	*SLT=0;
	*OLT=10;	
	RST[0]=0;
	RST[1]=2;
	RST[2]=3;
	
//////IP	
	HostIP[0]=183;HostIP[1]=63;HostIP[2]=92;HostIP[3]=43; //183.63.92.43,17953
	*HostPort=13012;// 17953;//
	LoclIP[0]=192;LoclIP[1]=168;LoclIP[2]=1;LoclIP[3]=119;
	GWIP[0]=192;GWIP[1]=168;GWIP[2]=1;GWIP[3]=1;
	CH1IP[0]=192;CH1IP[1]=168;CH1IP[2]=1;CH1IP[3]=11;
	CH2IP[0]=192;CH2IP[1]=168;CH2IP[2]=1;CH2IP[3]=12;
	NetMst[0]=255;NetMst[1]=255;NetMst[2]=255;NetMst[3]=0;
	*WidthxHeight=7;//目前只支持 7和 10  1280*720,1280*960
	*bLevel=60;
	*cLevel=60;
	*sLevel=60;

	printf("\r\n启动时间:\r\n");

//	WriteFM25Operation(sys_buf_flash,sys_buf_sram,250);

}


void data_read(void)
{
	uint32_t time_saved_buf;
//	ReadFM25Operation(sys_buf_flash,sys_buf_sram,250);
	printf("\r\n");
	printf("\r\nSTAA\t=%x",STAA[0]);
	printf("\r\nTID\t=%02x%02x%02x%02x%02x%02x",TID[0],TID[1],TID[2],TID[3],TID[4],TID[5]);
	printf("\r\nCHW\t=%02x%02x%02x%02x",CHW[0],CHW[1],CHW[2],CHW[3]);printf("(验证密文)");
	printf("\r\nPSW\t=%02x%02x%02x%02x",PSW[0],PSW[1],PSW[2],PSW[3]);
	printf("\r\nSV\t=%d",*SV);
	printf("\r\nHBT\t=%d",*HBT);
	printf("\r\nGDT\t=%d",*GDT);
	printf("\r\nSLT\t=%d",*SLT);
	printf("\r\nOLT\t=%d",*OLT);
	printf("\r\nRST:\t%d日 %d时 %d分",RST[0],RST[1],RST[2]);
	printf("\r\nHostIP:\t%d,%d,%d,%d,%d",HostIP[0],HostIP[1],HostIP[2],HostIP[3],*HostPort); printf("(为存储数据,发 CONFIGDTU 配置)");
//	printf("\r\nHostIP:\t%d,%d,%d,%d,%d",0,0,0,0,0);
	printf("\r\nLoclIP:\t%d,%d,%d,%d",LoclIP[0],LoclIP[1],LoclIP[2],LoclIP[3]);
//	printf("\r\nLoclIP:\t%d,%d,%d,%d,%d",0,0,0,0,0);
	printf("\r\nGWIP:\t%d,%d,%d,%d",GWIP[0],GWIP[1],GWIP[2],GWIP[3]);
	printf("\r\nCH1IP:\t%d,%d,%d,%d",CH1IP[0],CH1IP[1],CH1IP[2],CH1IP[3]);
	printf("\r\nCH2IP:\t%d,%d,%d,%d",CH2IP[0],CH2IP[1],CH2IP[2],CH2IP[3]);
	printf("\r\nNetMst:\t%d,%d,%d,%d",NetMst[0],NetMst[1],NetMst[2],NetMst[3]);
	
	
}

void data_write()
{
//	char i,buf[20];
	
	if(*STAA !=0x68)
	{
		printf("\r\n检测存储数据为空,初始化");
		data_rst();
	}
	else 
	{
//		printf("\r\n检测已有存储数据");
	}
}

void SRAM_data_int(void)
{
//	uint32_t temp;
	
//	data_rst();
	data_read();
	data_write();

}

