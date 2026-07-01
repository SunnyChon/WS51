/*********************************************************
*Copyright (h), 2020-2030, 深圳前海维晟智能技术有限公司
*文件名:	eeprom.h
*作  者:	
*版  本:	
*日  期:
*描  述:	
*备  注:     
**********************************************************/
#ifndef __EEPROM_H
#define __EEPROM_H

#define EPPROM_UNLOCK 0X9A
//#define EPPROM_WRITE_CMD 0X46
#define EPPROM_WRITE_CMD 0X42
#define EPPROM_LOCK 0XA9

#define EPPROM_READ_CMD 0X45
//#define EPPROM_READ_CMD 0X41
#define EEPROM_START_ADDR 0x00

void writeData2EEPROM(unsigned char *buf,unsigned short SectorAddr,unsigned short len);
void readDatafromEEPROM(unsigned char *buf,unsigned short SectorAddr,unsigned short len);
#endif /* __SPI_FLASH_H */

