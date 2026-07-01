 /**
  ******************************************************************************
  * @file    
  * @author  
  * @version V1.0
  * @date    2019-05-16
  * @brief   Inner eeprom read and write
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */
  
#include "eeprom.h"
#include "WS51F6240.h"	

/*****************************************************
*函数名称：void writeData2EEPROM(unsigned char *buf,unsigned short SectorAddr,unsigned short len)
*函数功能：EEPROM写
*入口参数：buf,要写入数据的指针
		   SectorAddr 地址
		   len,写入长度
*出口参数：void
*****************************************************/
void writeData2EEPROM(unsigned char *buf,unsigned short SectorAddr,unsigned short len)
{
	unsigned char i=0;
	//1 EPPROM Unlock
	FSFLG=EPPROM_UNLOCK;
	//2 EEPROM Enable write
	FSCMD=EPPROM_WRITE_CMD;
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
		FSFLG=EPPROM_LOCK;
}


/*****************************************************
*函数名称：void readDatafromEEPROM(unsigned char *buf,unsigned short SectorAddr,unsigned short len)
*函数功能：EEPROM写
*入口参数：buf,要读出数据的指针
		   SectorAddr 地址
		   len,读出长度
*出口参数：void
*****************************************************/
void readDatafromEEPROM(unsigned char *buf,unsigned short SectorAddr,unsigned short len)
{
	unsigned char i=0;
	//1 EEPROM Enable read
	//FSFLG=INNER_EPPROM_UNLOCK;
	FSCMD=EPPROM_READ_CMD;
	for(i=0;i<len;++i)
	{
			//2  write address		
			FSDARL=(SectorAddr&0xff);
			FSDARH=((SectorAddr>>8)&0xff);
			SectorAddr++;
			//3 write data
			buf[i]=FSDAT;
	}
}




   
/*********************************************END OF FILE**********************/
