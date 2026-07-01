#ifndef __nvr_H
#define __nvr_H

//
#define SECTOR_SIZE 128

#define NVR1_START_ADDR 0X00	//NVR1扇区首地址
#define NVR2_START_ADDR 0X80	//NVR2扇区首地址
#define NVR3_START_ADDR 0X100	//NVR3扇区首地址
#define NVR4_START_ADDR 0X180	//NVR4扇区首地址
#define NVR5_START_ADDR 0X200	//NVR1扇区首地址
#define NVR6_START_ADDR 0X280	//NVR2扇区首地址
#define NVR7_START_ADDR 0X300	//NVR3扇区首地址
#define NVR8_START_ADDR 0X380	//NVR4扇区首地址
#define NVR9_START_ADDR 0X400	//NVR1扇区首地址
#define NVR10_START_ADDR 0X480	//NVR2扇区首地址
#define NVR11_START_ADDR 0X500	//NVR3扇区首地址
#define NVR12_START_ADDR 0X670	//NVR4扇区首地址



#define NVR_FLASH_MARK_ENABLE_ADDR 0x10C
#define NVR_FLASH_MARK_ENABLE_CMD 0xAA
#define NVR_FLASH_MARK_ADDR 0x10D
#define NVR_FLASH_MARK_DATA 0x80

#define NVR_UNLOCK 0X78
//#define NVR_WRITE 0X86
#define NVR_WRITE 0X82
//#define NVR_ERASE 0X87
#define NVR_ERASE 0X83
#define INNER_FLASH_ERASE_UN-MASK 0X04
//#define NVR_BANDGAP_TRIMMING_ENABLE 0x100
//#define NVR_BANDGAP_TRIMMING_AUTOLOAD_VALUE 0x101
#define NVR_LOCK 0X87
#define NVR_READ 0X81
//#define NVR_READ 0X85

void EraseNVR(unsigned short SectorAddr);
void WriteDataNVR(unsigned char *buf,unsigned short SectorAddr,unsigned short len);
void readDatafromNVR(unsigned char *buf,unsigned short SectorAddr,unsigned short len);
void FlashCodeErase(unsigned short SectorNum,unsigned short len);

#endif

