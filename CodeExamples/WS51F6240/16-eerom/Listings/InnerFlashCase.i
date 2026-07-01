
#line 1 "InnerFlashCase.c" /0
  
#line 1 "WS51F6132.h" /0
 
 sfr SP          = 0x81;
 sfr DP0L        = 0x82;
 sfr DP0H        = 0x83;
 sfr DP1L        = 0x84;
 sfr DP1H        = 0x85;
 sfr SCCON       = 0x86;
 sfr PCON        = 0x87;
 sfr TCON        = 0x88;
 sfr TMOD        = 0x89;
 sfr TL0         = 0x8a;
 sfr TL1         = 0x8b;
 sfr TH0         = 0x8c;
 sfr TH1         = 0x8d;
 
 sfr P1          = 0x90;
 sfr HRCON       = 0x96;
 sfr LRCON       = 0x97;
 sfr S0CON       = 0x98;
 sfr S0BUF       = 0x99;
 sfr S0CFG       = 0x9a;
 sfr RSTFLG      = 0x9f;
 
 sfr I2CCON      = 0xa1;
 sfr I2CADR      = 0xa2;
 sfr I2CFG0      = 0xa3;
 sfr I2CFG1      = 0xa4;
 sfr I2CTXD      = 0xa5;
 sfr I2CRXD      = 0xa6;
 sfr I2CFLG      = 0xa7;
 sfr IE          = 0xa8;
 sfr WDTCON      = 0xa9;
 sfr WDTFLG      = 0xaa;
 
 sfr P3          = 0xb0;
 sfr DACON       = 0xb1;
 sfr IP          = 0xb8;
 sfr LVDCON      = 0xb9;
 
 sfr T2CON       = 0xc8;
 sfr T2MOD       = 0xc9;
 sfr T2CL        = 0xca;
 sfr T2CH        = 0xcb;
 sfr TL2         = 0xcc;
 sfr TH2         = 0xcd;
 
 sfr PSW         = 0xd0;
 sfr WKTCON      = 0xd1;
 sfr EPIE        = 0xd8;
 sfr EPIF        = 0xd9;
 sfr EP0CON      = 0xda;
 sfr EP1CON      = 0xdb;
 
 sfr ACC         = 0xe0;
 sfr PCOMS       = 0xE4;
 sfr PDRVS       = 0xE5;
 sfr TKMXF0      = 0xe9;
 sfr TKMXF1      = 0xea;
 sfr TKMNF0      = 0xec;
 sfr TKMNF1      = 0xed;
 
 sfr B           = 0xf0;
 sfr TKCON       = 0xf1;
 sfr TKCFG0      = 0xf2;
 sfr TKCFG1      = 0xf3;
 sfr TKNUM       = 0xf4;
 sfr TKFLG0      = 0xf5;
 sfr TKFLG1      = 0xf6;
 
 sfr PWCON       = 0xf9;
 sfr IT0CON      = 0xfa;
 sfr IT1CON      = 0xfb;
 sfr IDLF        = 0xfc;
 sfr STPF        = 0xfe;
 
 sfr OKER        = 0xff;
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 sbit P10 = P1^0;
 sbit P11 = P1^1;
 sbit P12 = P1^2;
 sbit P13 = P1^3;
 sbit P14 = P1^4;
 sbit P15 = P1^5;
 sbit P16 = P1^6;
 sbit P17 = P1^7;
 
 sbit P30 = P3^0;
 sbit P31 = P3^1;
 sbit P32 = P3^2;
 sbit P33 = P3^3;
 sbit P34 = P3^4;
 sbit P35 = P3^5;
 
 
 sbit PX4 = IP^6;		 
 sbit PX3 = IP^5;		 
 sbit PX2 = IP^4;		 
 sbit PT1 = IP^3;		 
 sbit PX1 = IP^2;		 
 sbit PT0 = IP^1;		 
 sbit PX0 = IP^0;		 
 
 
 sbit EA = 	 IE^7;		 
 sbit EINT3 = IE^6;		 
 sbit EINT2 = IE^5;		 
 sbit ES0 = IE^4;		 
 sbit ET1 = 	 IE^3;		 
 sbit EINT1 = IE^2;		 
 sbit ET0 = 	 IE^1;		 
 sbit EINT0 = IE^0;		 
 
 
 sbit SM00 = S0CON^7;	 
 sbit SM10 = S0CON^6;	 
 sbit SM20 = S0CON^5;	 
 sbit REN0 = S0CON^4;	 
 sbit TB80 = S0CON^3;	 
 sbit RB80 = S0CON^2;	 
 sbit TI0 = 	S0CON^1;	 
 sbit RI0 =  S0CON^0;	 
 
 
 sbit TF1 = TCON^7;		 
 sbit TR1 = TCON^6;		 
 sbit TF0 = TCON^5;		 
 sbit TR0 = TCON^4;		 
 sbit IE1 = TCON^3;		 
 sbit IT1 = TCON^2;		 
 sbit IE0 = TCON^1;		 
 sbit IT0 = TCON^0;		 
 
 
 sbit TF2 =   T2CON^7;		 
 sbit EXF2 =  T2CON^6;		 
 sbit RCLK =  T2CON^5;		 
 sbit TCLK =  T2CON^4;		 
 sbit EXEN2 = T2CON^3;		 
 sbit TR2 =   T2CON^2;		 
 sbit CT2 =   T2CON^1;		 
 sbit CPRL2 = T2CON^0;		 
 
 
 
 
 
#line 1 "InnerFlashCase.c" /0
 
  
#line 1 "InnerFlashCase.h" /0
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 void InnerFlashCodeErase(unsigned short SectorNum,unsigned short len);
 void InnerFlashDataErase(unsigned short SectorNum,unsigned short len);
 void InnerFLASHCodeByteWrite(unsigned char dByte, unsigned short WriteAddr);
 void InnerFLASHCodeBufferWrite(unsigned char* pBuffer, unsigned short WriteAddr, unsigned short NumByteToWrite);
 void InnerFLASHCodeBufferRead(unsigned char* pBuffer, unsigned short ReadAddr, unsigned short NumByteToRead);
 void InnerFLASHDataBufferWrite(unsigned char* pBuffer, unsigned short WriteAddr, unsigned short NumByteToWrite);
 void InnerFLASHDataBufferRead(unsigned char* pBuffer, unsigned short ReadAddr, unsigned short NumByteToRead);
 
 
#line 2 "InnerFlashCase.c" /0
 





 
 void InnerFlashCodeErase(unsigned short SectorNum,unsigned short len)
 { 
 unsigned int i=0;
 unsigned short StartAddr;
 
  (*(unsigned char volatile xdata *)0x8304)=0X12;
 
  (*(unsigned char volatile xdata *)0x8304)=0X34;
 
 StartAddr=128*SectorNum;
 for(i=0;i<len;++i)
 {
  (*(unsigned char volatile xdata *)0x8306)=((StartAddr+i*128)&0xff);
  (*(unsigned char volatile xdata *)0x8307)=(((StartAddr+i*128)>>8)&0xff);
 
  (*(unsigned char volatile xdata *)0x8301)=0X07;
 }
 
  (*(unsigned char volatile xdata *)0x8304)=0X43;
 
  (*(unsigned char volatile xdata *)0x8304)=0XFF;
 }
 





 
 void InnerFlashDataErase(unsigned short SectorNum,unsigned short len)
 {
 unsigned int i=0;
 unsigned short StartAddr;
 
  (*(unsigned char volatile xdata *)0x8304)=0X12;
 
  (*(unsigned char volatile xdata *)0x8304)=0X56;
 
 StartAddr=128*SectorNum;
 for(i=0;i<len;++i)
 {
  (*(unsigned char volatile xdata *)0x8306)=((StartAddr+i*128)&0xff);
  (*(unsigned char volatile xdata *)0x8307)=(((StartAddr+i*128)>>8)&0xff);
 
  (*(unsigned char volatile xdata *)0x8301)=0X03;
 }
 
  (*(unsigned char volatile xdata *)0x8304)=0X65;
 
  (*(unsigned char volatile xdata *)0x8304)=0XFF;
 }
 






 
 void InnerFLASHCodeBufferWrite(unsigned char* pBuffer, unsigned short WriteAddr, unsigned short NumByteToWrite)
 {
 unsigned int i=0;
 
  (*(unsigned char volatile xdata *)0x8304)=0X12;
 
  (*(unsigned char volatile xdata *)0x8304)=0X34;
 
  (*(unsigned char volatile xdata *)0x8301)=0X06;
 for(i=0;i<NumByteToWrite;++i)
 {
  (*(unsigned char volatile xdata *)0x8306)=((WriteAddr+i)&0xff);
  (*(unsigned char volatile xdata *)0x8307)=(((WriteAddr+i)>>8)&0xff);
 
  (*(unsigned char volatile xdata *)0x8303)=pBuffer[i];
 }
 
  (*(unsigned char volatile xdata *)0x8304)=0X43;
 
  (*(unsigned char volatile xdata *)0x8304)=0XFF;
 }
 






 
 void InnerFLASHCodeByteWrite(unsigned char dByte, unsigned short WriteAddr)
 {
 unsigned int i=0;
 
  (*(unsigned char volatile xdata *)0x8304)=0X12;
 
  (*(unsigned char volatile xdata *)0x8304)=0X34;
 
  (*(unsigned char volatile xdata *)0x8301)=0X06;
 
  (*(unsigned char volatile xdata *)0x8306)=(WriteAddr&0xff);
  (*(unsigned char volatile xdata *)0x8307)=((WriteAddr>>8)&0xff);
 
  (*(unsigned char volatile xdata *)0x8303)=dByte;
 
 
  (*(unsigned char volatile xdata *)0x8304)=0X43;
 
  (*(unsigned char volatile xdata *)0x8304)=0XFF;
 }
 






 
 void InnerFLASHCodeBufferRead(unsigned char* pBuffer, unsigned short ReadAddr, unsigned short NumByteToRead)
 {
 unsigned int i=0;
 
 
 
 
 
 
 
 
  (*(unsigned char volatile xdata *)0x8301)=0X05;
 for(i=0;i<NumByteToRead;++i)
 {
  (*(unsigned char volatile xdata *)0x8306)=((ReadAddr+i)&0xff);
  (*(unsigned char volatile xdata *)0x8307)=(((ReadAddr+i)>>8)&0xff);
 
 pBuffer[i]=(*(unsigned char volatile xdata *)0x8303);
 }
 
 
 
 
 }
 






 
 void InnerFLASHDataBufferWrite(unsigned char* pBuffer, unsigned short WriteAddr, unsigned short NumByteToWrite)
 {
 unsigned int i=0;
 
  (*(unsigned char volatile xdata *)0x8304)=0X12;
 
  (*(unsigned char volatile xdata *)0x8304)=0X56;
 
  (*(unsigned char volatile xdata *)0x8301)=0X02;
 for(i=0;i<NumByteToWrite;++i)
 {
  (*(unsigned char volatile xdata *)0x8306)=((WriteAddr+i)&0xff);
  (*(unsigned char volatile xdata *)0x8307)=(((WriteAddr+i)>>8)&0xff);
 
  (*(unsigned char volatile xdata *)0x8303)=pBuffer[i];
 }
 
  (*(unsigned char volatile xdata *)0x8304)=0X65;
 
  (*(unsigned char volatile xdata *)0x8304)=0XFF;
 }
 






 
 void InnerFLASHDataBufferRead(unsigned char* pBuffer, unsigned short ReadAddr, unsigned short NumByteToRead)
 {
 unsigned int i=0;
 
  (*(unsigned char volatile xdata *)0x8301)=0X01;
 for(i=0;i<NumByteToRead;++i)
 {
  (*(unsigned char volatile xdata *)0x8306)=((ReadAddr+i)&0xff);
  (*(unsigned char volatile xdata *)0x8307)=(((ReadAddr+i)>>8)&0xff);
 
 pBuffer[i]=(*(unsigned char volatile xdata *)0x8303);
 }
 
 }
 
 
 
 
