/*********************************************************
*Copyright (C), 2020-2030, 深圳前海维晟智能技术有限公司
*文件名:	nvr.c
*作  者:	
*版  本:	
*日  期:	
*描  述:	
*备  注:     
**********************************************************/

#include "WS51F6240.h"
#include "nvr.h"

/*****************************************************
*函数名称：void EraseNVR(unsigned short SectorAddr))
*函数功能：NVR扇区擦除 
*入口参数：SectorAddr_扇区首地址(NVR1/2/3/4_START_ADDR)
*出口参数：void
*****************************************************/
void EraseNVR(unsigned short SectorAddr)
{
	//1  Flash unlock
	FSFLG=NVR_UNLOCK;

	//2  write address
	FSDARL=(SectorAddr&0xff);
	FSDARH=((SectorAddr>>8)&0xff);
	//3  Flash erase cmd
	FSCMD=NVR_ERASE;
	//4 NVR lock
	FSFLG=NVR_LOCK;
}
/*****************************************************
*函数名称：void WriteDataNVR(unsigned char *buf,unsigned short SectorAddr,unsigned short len)
*函数功能：NVR扇区写
*入口参数：buf,要写入数据的指针
		   SectorAddr,扇区地址
		   len,写入长度
*出口参数：void
*****************************************************/
void WriteDataNVR(unsigned char *buf,unsigned short SectorAddr,unsigned short len)
{
	unsigned char i=0;
	//1  Flash unlock
	FSFLG=NVR_UNLOCK;
	//2  Flash  write cmd
	FSCMD=NVR_WRITE;	
	for(i=0;i<len;++i)
	{
		//3  write address		
		FSDARL=(SectorAddr&0xff);
		FSDARH=((SectorAddr>>8)&0xff);
		SectorAddr++;
		//4 write data
		FSDAT=buf[i];
	}
	//4 NVR lock
	FSFLG=NVR_LOCK;
}

/*****************************************************
*函数名称：void readDatafromNVR(unsigned char *buf,unsigned short SectorAddr,unsigned short len)
*函数功能：NVR扇区读
*入口参数：buf,要保存数据的缓存
		   SectorAddr,扇区地址
		   len,写入长度
*出口参数：void
*****************************************************/
void readDatafromNVR(unsigned char *buf,unsigned short SectorAddr,unsigned short len)
{
	unsigned char i=0;
	//1  read cmd
	FSCMD=NVR_READ;
	for(i=0;i<len;++i)
	{
		//2  write address		
		FSDARL=(SectorAddr&0xff);
		FSDARH=((SectorAddr>>8)&0xff);
		++SectorAddr;
		//3 read data
		buf[i]=FSDAT;
	}
}
   
/*********************************************END OF FILE**********************/
