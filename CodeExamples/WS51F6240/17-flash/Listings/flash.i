
#line 1 "flash.c" /0








 
  
#line 1 "..\headfile\WS51F6240.h" /0
 
 
 sfr OKER        = 0xff;
 
 sfr P0          = 0x80;
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
 sfr XSCON       = 0x95;
 sfr HRCON       = 0x96;
 sfr LRCON       = 0x97;
 sfr S0CON       = 0x98;
 sfr S0BUF       = 0x99;
 sfr S0CFG       = 0x9a;
 sfr S1CON       = 0x9b;
 sfr S1BUF       = 0x9c;
 sfr S1RELL      = 0x9d;
 sfr S1RELH      = 0x9e;
 sfr RSTFLG      = 0x9f;
 sfr P2          = 0xa0;
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
 sfr TL3         = 0xae;
 sfr TH3         = 0xaf;
 sfr T3CON       = 0xb2;
 sfr T3MOD       = 0xb3;
 sfr T3RL        = 0xb4;
 sfr T3RH        = 0xb5;
 sfr T3CL        = 0xb6;
 sfr T3CH        = 0xb7;
 sfr IP          = 0xb8;
 sfr LVDCON      = 0xb9;
 sfr ADCBGP      = 0xbf;
 sfr ADCON       = 0xc0;
 sfr ADCFG       = 0xc1;
 sfr ADCHS       = 0xc2;
 sfr ADCDL       = 0xc3;
 sfr ADCDH       = 0xc4;
 sfr ADCPC       = 0xc5;
 sfr ADCPDL      = 0xc6;
 sfr ADCPDH      = 0xc7;
 sfr T2CON       = 0xc8;
 sfr T2MOD       = 0xc9;
 sfr T2CL        = 0xca;
 sfr T2CH        = 0xcb;
 sfr TL2         = 0xcc;
 sfr TH2         = 0xcd;
 sfr SCMCON      = 0xce;
 sfr SCMFLG      = 0xcf;
 sfr PSW         = 0xd0;
 sfr WKTCON      = 0xd1;
 sfr WKTSS       = 0xd2;
 sfr OPCON       = 0xd3;
 sfr OPCFG       = 0xd4;
 sfr EPIE        = 0xd8;
 sfr EPIF        = 0xd9;
 sfr EP0CON      = 0xda;
 sfr EP1CON      = 0xdb;
 sfr EP2CON      = 0xdc;
 sfr EP3CON      = 0xdd;
 sfr ACC         = 0xe0;
 sfr SPCON       = 0xe1;
 sfr SPDAT       = 0xe2;
 sfr SPFLG       = 0xe3;
 sfr PCOMS       = 0xe4;
 sfr PDRVS       = 0xe5;
 sfr EXIE        = 0xe8;
 sfr B           = 0xf0;
 sfr TKCON       = 0xf1;
 sfr EXIP        = 0xf8;
 sfr PWCON       = 0xf9;
 sfr IT0CON      = 0xfa;
 sfr IT1CON      = 0xfb;
 sfr IDLFL       = 0xfc;
 sfr IDLFH       = 0xfd;
 sfr STPF        = 0xfe;
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 sbit P00 = P0^0;	 
 sbit P01 = P0^1; 	 
 sbit P02 = P0^2;	 
 sbit P03 = P0^3; 	 
 sbit P04 = P0^4;	 
 sbit P05 = P0^5; 	 
 sbit P06 = P0^6;	 
 sbit P07 = P0^7; 	 
 
 sbit P20 = P2^0;	 
 sbit P21 = P2^1; 	 
 sbit P22 = P2^2;	 
 sbit P23 = P2^3; 	 
 sbit P24 = P2^4;	 
 sbit P25 = P2^5; 	 
 sbit P26 = P2^6;	 
 sbit P27 = P2^7; 	 
 
 sbit P10 = P1^0;
 sbit P11 = P1^1;
 sbit P12 = P1^2;
 sbit P13 = P1^3;
 sbit P14 = P1^4;
 sbit P15 = P1^5;
 sbit P16 = P1^6;
 sbit P17 = P1^7;
 
 
 
 
 
 
 
 
 
 
 
 sbit PX3 = IP^6;		 
 sbit PX2 = IP^5;		 
 sbit PS0 = IP^4;		 
 sbit PT1 = IP^3;		 
 sbit PX1 = IP^2;		 
 sbit PT0 = IP^1;		 
 sbit PX0 = IP^0;		 
 
 
 sbit PX6 = EXIP^2;		 
 sbit PX5 = EXIP^1;		 
 sbit PX4 = EXIP^0;		 
 
 
 sbit EA = 	 IE^7;		 
 sbit EINT3 = IE^6;		 
 sbit EINT2 = IE^5;		 
 sbit ES0 = IE^4;		 
 sbit ET1 = 	 IE^3;		 
 sbit EINT1 = IE^2;		 
 sbit ET0 = 	 IE^1;		 
 sbit EINT0 = IE^0;		 
 
 
 sbit EINT6 = EXIE^2;		 
 sbit EINT5 = EXIE^1;		 
 sbit EINT4 = EXIE^0;		 
 
 
 sbit EP3IE = EPIE^3;		 
 sbit EP2IE = EPIE^2;		 
 sbit EP1IE = EPIE^1;		 
 sbit EP0IE = EPIE^0;		 
 
 
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
 
 
 sbit ADST =  ADCON^7;		 
 sbit ADIE =  ADCON^6;		 
 sbit ADCF =  ADCON^0;		 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 typedef 	unsigned char	u8;
 typedef 	unsigned int	u16;
 typedef 	unsigned long	u32;
 typedef     unsigned char   uint8_t;
 typedef     unsigned int    uint16_t;
 typedef     unsigned long   uint32_t;
 
 typedef     signed char     int8_t;
 typedef     signed int      int16_t;
 typedef     signed long     int32_t;
 
 
#line 10 "flash.c" /0
 
  
#line 1 "flash.h" /0
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 void FlashCodeErase(unsigned short SectorNum,unsigned short len);
 void FlashDataErase(unsigned short SectorNum,unsigned short len);
 void FLASHCodeByteWrite(unsigned char dByte, unsigned short WriteAddr);
 void FLASHCodeBufferWrite(unsigned char* pBuffer, unsigned short WriteAddr, unsigned short NumByteToWrite);
 void FLASHCodeBufferRead(unsigned char* pBuffer, unsigned short ReadAddr, unsigned short NumByteToRead);
 void FLASHDataBufferWrite(unsigned char* pBuffer, unsigned short WriteAddr, unsigned short NumByteToWrite);
 void FLASHDataBufferRead(unsigned char* pBuffer, unsigned short ReadAddr, unsigned short NumByteToRead);
 
 
#line 11 "flash.c" /0
 





 
 void FlashCodeErase(unsigned short SectorNum,unsigned short len)
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
 





 
 void FlashDataErase(unsigned short SectorNum,unsigned short len)
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
 






 
 void FLASHCodeBufferWrite(unsigned char* pBuffer, unsigned short WriteAddr, unsigned short NumByteToWrite)
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
 






 
 void FLASHCodeByteWrite(unsigned char dByte, unsigned short WriteAddr)
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
 






 
 void FLASHCodeBufferRead(unsigned char* pBuffer, unsigned short ReadAddr, unsigned short NumByteToRead)
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
 






 
 void FLASHDataBufferWrite(unsigned char* pBuffer, unsigned short WriteAddr, unsigned short NumByteToWrite)
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
 






 
 void FLASHDataBufferRead(unsigned char* pBuffer, unsigned short ReadAddr, unsigned short NumByteToRead)
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
 
 
 
 
