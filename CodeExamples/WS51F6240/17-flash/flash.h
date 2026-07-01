
#ifndef	__flash_H
#define	__flash_H

#define SECTOR_SIZE 128		//扇区大小为 128 字节
#define FlASH_SIZE (32*1024)

#define FLASH_UNLOCK 0X12
#define FLASH_ERASE_UNMASK 0X04
#define FLASH_CODE_UNLOCK 0X34
#define FLASH_DATA_UNLOCK 0X56

#define FLASH_WRITE_DATA 0X02
#define FLASH_WRITE_CODE 0X06

#define FLASH_READ_CODE 0X05
#define FLASH_READ_DATA 0X01

#define FLASH_ERASE_CODE 0X07
#define FLASH_ERASE_DATA 0X03
#define FLASH_ERASE_WHOLE	0X04

#define FLASH_LOCK 0XFF
#define FLASH_CODE_LOCK 0X43
#define FLASH_DATA_LOCK 0X65

#define FLASH_CHECK_SUM_CODE 0x0c
#define FLASH_CHECK_SUM_DATA 0x08
/*----------------------------------------------------------------*/

void FlashCodeErase(unsigned short SectorNum,unsigned short len);
void FlashDataErase(unsigned short SectorNum,unsigned short len);
void FLASHCodeByteWrite(unsigned char dByte, unsigned short WriteAddr);
void FLASHCodeBufferWrite(unsigned char* pBuffer, unsigned short WriteAddr, unsigned short NumByteToWrite);
void FLASHCodeBufferRead(unsigned char* pBuffer, unsigned short ReadAddr, unsigned short NumByteToRead);
void FLASHDataBufferWrite(unsigned char* pBuffer, unsigned short WriteAddr, unsigned short NumByteToWrite);
void FLASHDataBufferRead(unsigned char* pBuffer, unsigned short ReadAddr, unsigned short NumByteToRead);

#endif
