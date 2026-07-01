/*********************************************************
*Copyright (C), 2020-2030, 深圳前海维晟智能技术有限公司
*文件名:	flash.c
*作  者:	
*版  本:
*日  期:
*描  述:	
*备  注:     
**********************************************************/
#include "WS51F6240.h"
#include "flash.h"
/**
* @brief  erase innner code area
* @param  SectorNum: the nume of sector , value is 0 to 8*1024/128
* @param  len: how many sector need to erase
* @retval no
*/
void FlashCodeErase(unsigned short SectorNum,unsigned short len)
{//扇区是进行擦除操作的最小单位，每个扇区大小为 128 字节；默认情况下64扇区都为code
	unsigned int i=0;
	unsigned short StartAddr;
	//1  Flash unlock
	FSFLG=FLASH_UNLOCK;
	//2  Flash CODE unlock
	FSFLG=FLASH_CODE_UNLOCK;
	//3  write address
	StartAddr=SECTOR_SIZE*SectorNum;
	for(i=0;i<len;++i)
	{
		FSDARL=((StartAddr+i*SECTOR_SIZE)&0xff);
		FSDARH=(((StartAddr+i*SECTOR_SIZE)>>8)&0xff);
		//4 Write CMD
		FSCMD=FLASH_ERASE_CODE;
	}
	//5 CODE lock
	FSFLG=FLASH_CODE_LOCK;
	//6 Flash lock
	FSFLG=FLASH_LOCK;
}

/**
  * @brief  erase innner code area
	* @param  SectorNum: the nume of sector , value is 0 to 8*1024/128
	* @param  len: how many sector need to erase
  * @retval no
  */
void FlashDataErase(unsigned short SectorNum,unsigned short len)
{
	unsigned int i=0;
	unsigned short StartAddr;
	//1  Flash unlock
	FSFLG=FLASH_UNLOCK;
	//2  Flash DATA unlock
	FSFLG=FLASH_DATA_UNLOCK;
	//3  write address
	StartAddr=SECTOR_SIZE*SectorNum;
	for(i=0;i<len;++i)
	{
		FSDARL=((StartAddr+i*SECTOR_SIZE)&0xff);
		FSDARH=(((StartAddr+i*SECTOR_SIZE)>>8)&0xff);
		//4 Write CMD
		FSCMD=FLASH_ERASE_DATA;
	}
	//5 DATA lock
	FSFLG=FLASH_DATA_LOCK;
	//6 Flash lock
	FSFLG=FLASH_LOCK;
}

 /**
  * @brief  对FLASH写入数据，调用本函数写入数据前需要先擦除扇区
  * @param	pBuffer，要写入数据的指针
  * @param  WriteAddr，写入地址
  * @param  NumByteToWrite，写入数据长度
  * @retval 无
  */
void FLASHCodeBufferWrite(unsigned char* pBuffer, unsigned short WriteAddr, unsigned short NumByteToWrite)
{
	unsigned int i=0;
	//1  Flash unlock
	FSFLG=FLASH_UNLOCK;
	//2  Flash CODE unlock
	FSFLG=FLASH_CODE_UNLOCK;
	
	FSCMD=FLASH_WRITE_CODE;
	for(i=0;i<NumByteToWrite;++i)
	{
		FSDARL=((WriteAddr+i)&0xff);
		FSDARH=(((WriteAddr+i)>>8)&0xff);
		//4 Write data
		FSDAT=pBuffer[i];
	}
	//5 CODE lock
	FSFLG=FLASH_CODE_LOCK;
	//6 Flash lock
	FSFLG=FLASH_LOCK;
}

 /**
  * @brief  对FLASH写入数据，调用本函数写入数据前需要先擦除扇区
  * @param	dByte，要写入数据
  * @param  WriteAddr，写入地址
  * @param  
  * @retval 无
  */
void FLASHCodeByteWrite(unsigned char dByte, unsigned short WriteAddr)
{
	unsigned int i=0;
	//1  Flash unlock
	FSFLG=FLASH_UNLOCK;
	//2  Flash CODE unlock
	FSFLG=FLASH_CODE_UNLOCK;
	
	FSCMD=FLASH_WRITE_CODE;

	FSDARL=(WriteAddr&0xff);
	FSDARH=((WriteAddr>>8)&0xff);
	//4 Write data
	FSDAT=dByte;
	
	//5 CODE lock
	FSFLG=FLASH_CODE_LOCK;
	//6 Flash lock
	FSFLG=FLASH_LOCK;
}

/**
* @brief  读取FLASH数据
* @param 	pBuffer，存储读出数据的指针
* @param   ReadAddr，读取地址
* @param   NumByteToRead，读取数据长度
* @retval 无
*/
void FLASHCodeBufferRead(unsigned char* pBuffer, unsigned short ReadAddr, unsigned short NumByteToRead)
{
	unsigned int i=0;

	
//	//1  Flash unlock
//	FSFLG=FLASH_UNLOCK;
//	//2  Flash CODE unlock
//	FSFLG=FLASH_CODE_UNLOCK;
	
  //1  Flash code read
	FSCMD=FLASH_READ_CODE;
	for(i=0;i<NumByteToRead;++i)
	{
		FSDARL=((ReadAddr+i)&0xff);
		FSDARH=(((ReadAddr+i)>>8)&0xff);
		//2 read data
		pBuffer[i]=FSDAT;
	}
//	//5 CODE lock
//	FSFLG=FLASH_CODE_LOCK;
//	//6 Flash lock
//	FSFLG=FLASH_LOCK;
}

/**
  * @brief  对FLASH写入数据，调用本函数写入数据前需要先擦除扇区
  * @param	pBuffer，要写入数据的指针
  * @param  WriteAddr，写入地址
  * @param  NumByteToWrite，写入数据长度
  * @retval 无
  */
void FLASHDataBufferWrite(unsigned char* pBuffer, unsigned short WriteAddr, unsigned short NumByteToWrite)
{
	unsigned int i=0;
  //1  Flash unlock
	FSFLG=FLASH_UNLOCK;
	//2  Flash CODE unlock
	FSFLG=FLASH_DATA_UNLOCK;
	
	FSCMD=FLASH_WRITE_DATA;
	for(i=0;i<NumByteToWrite;++i)
	{
		FSDARL=((WriteAddr+i)&0xff);
		FSDARH=(((WriteAddr+i)>>8)&0xff);
		//4 Write data
		FSDAT=pBuffer[i];
	}
	//5 CODE lock
	FSFLG=FLASH_DATA_LOCK;
	//6 Flash lock
	FSFLG=FLASH_LOCK;
}

 /**
  * @brief  读取FLASH数据
  * @param 	pBuffer，存储读出数据的指针
  * @param   ReadAddr，读取地址
  * @param   NumByteToRead，读取数据长度
  * @retval 无
  */
void FLASHDataBufferRead(unsigned char* pBuffer, unsigned short ReadAddr, unsigned short NumByteToRead)
{
	unsigned int i=0;
  //1  Flash code read
	FSCMD=FLASH_READ_DATA;
	for(i=0;i<NumByteToRead;++i)
	{
		FSDARL=((ReadAddr+i)&0xff);
		FSDARH=(((ReadAddr+i)>>8)&0xff);
		//2 read data
		pBuffer[i]=FSDAT;
	}
	
}


   
/*********************************************END OF FILE**********************/