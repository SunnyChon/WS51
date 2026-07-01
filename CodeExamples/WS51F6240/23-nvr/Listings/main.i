
#line 1 "main.c" /0








 
 
  
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
 
 
#line 11 "main.c" /0
 
  
#line 1 "C:\Keil_v5\C51\Inc\stdio.h" /0






 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 typedef unsigned int size_t;
 
 
 #pragma SAVE
 #pragma REGPARMS
 extern char _getkey (void);
 extern char getchar (void);
 extern char ungetchar (char);
 extern char putchar (char);
 extern int printf   (const char *, ...);
 extern int sprintf  (char *, const char *, ...);
 extern int vprintf  (const char *, char *);
 extern int vsprintf (char *, const char *, char *);
 extern char *gets (char *, int n);
 extern int scanf (const char *, ...);
 extern int sscanf (char *, const char *, ...);
 extern int puts (const char *);
 
 #pragma RESTORE
 
 
 
#line 12 "main.c" /0
 
  
#line 1 "nvr.h" /0
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 void EraseNVR(unsigned short SectorAddr);
 void WriteDataNVR(unsigned char *buf,unsigned short SectorAddr,unsigned short len);
 void readDatafromNVR(unsigned char *buf,unsigned short SectorAddr,unsigned short len);
 void FlashCodeErase(unsigned short SectorNum,unsigned short len);
 
 
 
#line 13 "main.c" /0
 
 
 static void delay_1ms(void)
 {
 int j;
 for(j=0;j<1700;++j);
 }
 void delay_ms(unsigned int i)
 {
 unsigned long j=0;
 for(j=0;j<(i*16/12);++j);
 }
 
 static void delay(int i)
 {
 long j;
 for(j=0;j<10*i;++j);
 }
 
 





 
 void UART0_write(signed char dat)
 {
 S0BUF = dat;             
 while(!TI0);
 TI0 = 0;
 }
 


 
 char putchar(char ch)
 {
 
 UART0_write((signed char) ch);
 
 return ch;
 }
 





 
 void writeHex(unsigned char num)
 {
 unsigned char i=0;
 i=num/16;
 if(i>9)UART0_write(i-10+'A');
 else UART0_write(i+'0');
 i=num%16;
 if(i>9)UART0_write(i-10+'A');
 else UART0_write(i+'0');
 UART0_write(' ');
 }





 
 void Uart0Mode1(void)
 {
 SM00 = 0;
 SM10 = 1;	 
 REN0 = 1; 	 
 RI0  = 0;  	 
 TI0  = 0;  	 
 
 
 
 
 
 
 
 
 
 TR2  = 0;
 T2MOD= 0x00; 
 T2CL = 65536 - 52;
 T2CH = 65536 - 52 >> 8; 
 TL2  = T2CL;
 TH2  = T2CH;
 TR2  = 1;     
 RCLK = 1;    
 TCLK = 1;		 
 }
 
 unsigned char rbuf[128]={0};
 unsigned char buf[128]={0};
 





 
 void NVRCaseTest(void)
 {
 int i;
 
 
 EraseNVR(0X00);
 delay_ms(10);
 for(i=0;i<128;i++)buf[i]=1; 
 WriteDataNVR(buf,0X00,128);
 for(i=0;i<128;i++)rbuf[i]=0;
 readDatafromNVR(rbuf,0X00,128);
 delay_ms(10);
 for(i=0;i<128;i++)
 printf("i=%x,val=0X%BX\r\n",0X00+i,rbuf[i]);
 
 
 EraseNVR(0X80);
 delay_ms(10);
 for(i=0;i<128;i++)buf[i]=2; 
 WriteDataNVR(buf,0X80,128);
 for(i=0;i<128;i++)rbuf[i]=0;
 readDatafromNVR(rbuf,0X80,128);
 delay_ms(10);
 for(i=0;i<128;i++)
 printf("i=%x,val=0X%BX\r\n",0X80+i,rbuf[i]);
 
 
 EraseNVR(0X100);
 delay_ms(10);
 for(i=0;i<128;i++)buf[i]=3; 
 WriteDataNVR(buf,0X100,128);
 for(i=0;i<128;i++)rbuf[i]=0;
 readDatafromNVR(rbuf,0X100,128);
 delay_ms(10);
 for(i=0;i<128;i++)
 printf("i=%x,val=0X%BX\r\n",0X100+i,rbuf[i]);
 
 
 EraseNVR(0X180);
 delay_ms(10);
 for(i=0;i<128;i++)buf[i]=4;
 WriteDataNVR(buf,0X180,128);
 for(i=0;i<128;i++)rbuf[i]=0;
 readDatafromNVR(rbuf,0X180,128);
 delay_ms(10);
 for(i=0;i<128;i++)
 printf("i=%x,val=0X%BX\r\n",0X180+i,rbuf[i]); 
 
 
 EraseNVR(0X200);
 delay_ms(10);
 for(i=0;i<128;i++)buf[i]=5;
 WriteDataNVR(buf,0X200,128);
 for(i=0;i<128;i++)rbuf[i]=0;
 readDatafromNVR(rbuf,0X200,128);
 delay_ms(10);
 for(i=0;i<128;i++)
 printf("i=%x,val=0X%BX\r\n",0X200+i,rbuf[i]);             
 
 
 EraseNVR(0X280);
 delay_ms(10);
 for(i=0;i<128;i++)buf[i]=6;
 WriteDataNVR(buf,0X280,128);
 for(i=0;i<128;i++)rbuf[i]=0;
 readDatafromNVR(rbuf,0X280,128);
 delay_ms(10);
 for(i=0;i<128;i++)
 printf("i=%x,val=0X%BX\r\n",0X280+i,rbuf[i]);            
 
 
 EraseNVR(0X300);
 delay_ms(10);
 for(i=0;i<128;i++)buf[i]=7;
 WriteDataNVR(buf,0X300,128);
 for(i=0;i<128;i++)rbuf[i]=0;
 readDatafromNVR(rbuf,0X300,128);
 delay_ms(10);
 for(i=0;i<128;i++)
 printf("i=%x,val=0X%BX\r\n",0X300+i,rbuf[i]);        
 
 
 EraseNVR(0X380);
 delay_ms(10);
 for(i=0;i<128;i++)buf[i]=8;
 WriteDataNVR(buf,0X380,128);
 for(i=0;i<128;i++)rbuf[i]=0;
 readDatafromNVR(rbuf,0X380,128);
 delay_ms(10);
 for(i=0;i<128;i++)
 printf("i=%x,val=0X%BX\r\n",0X380+i,rbuf[i]);         
 
 
 EraseNVR(0X400);
 delay_ms(10);
 for(i=0;i<128;i++)buf[i]=9;
 WriteDataNVR(buf,0X400,128);
 for(i=0;i<128;i++)rbuf[i]=0;
 readDatafromNVR(rbuf,0X400,128);
 delay_ms(10);
 for(i=0;i<128;i++)
 printf("i=%x,val=0X%BX\r\n",0X400+i,rbuf[i]);     
 
 
 EraseNVR(0X480);
 delay_ms(10);
 for(i=0;i<128;i++)buf[i]=10;
 WriteDataNVR(buf,0X480,128);
 for(i=0;i<128;i++)rbuf[i]=0;
 readDatafromNVR(rbuf,0X480,128);
 delay_ms(10);
 for(i=0;i<128;i++)
 printf("i=%x,val=0X%BX\r\n",0X480+i,rbuf[i]);       
 
 
 EraseNVR(0X500);
 delay_ms(10);
 for(i=0;i<128;i++)buf[i]=11;
 WriteDataNVR(buf,0X500,128);
 for(i=0;i<128;i++)rbuf[i]=0;
 readDatafromNVR(rbuf,0X500,128);
 delay_ms(10);
 for(i=0;i<128;i++)
 printf("i=%x,val=0X%BX\r\n",0X500+i,rbuf[i]);       
 
 
 EraseNVR(0X670);
 delay_ms(10);
 for(i=0;i<128;i++)buf[i]=12;
 WriteDataNVR(buf,0X670,128);
 for(i=0;i<128;i++)rbuf[i]=0;
 readDatafromNVR(rbuf,0X670,128);
 delay_ms(10);
 for(i=0;i<128;i++)
 printf("i=%x,val=0X%BX\r\n",0X670+i,rbuf[i]); 
 } 
 





 
 void nvrCkSumTest(void)
 {
 unsigned int i,k;
 unsigned char j;	
 for(i=0;i<16;++i)
 {
  (*(unsigned char volatile xdata *)0x8306)=((i*128)&0xff);
  (*(unsigned char volatile xdata *)0x8307)=(((i*128)>>8)&0xff);
  (*(unsigned char volatile xdata *)0x8301)=0x8c;
 printf("i= %d, %bx_%bx", i, (*(unsigned char volatile xdata *)0x8309),(*(unsigned char volatile xdata *)0x8308));
 
 
 for(k=0;k<128;++k)rbuf[k]=0;
 readDatafromNVR(rbuf,(i*128),128);
 k=0;
 for(j=0;j<128;++j)
 {
 k += rbuf[j];
 }
 
 j=k>>8;
 printf(" %bx",j);
 j=k&0xff;
 printf("_%bx",j);
 UART0_write('\r');
 UART0_write('\n');
 }
 }  
 
 void main(void)
 {   
 SCCON = 0x00; 
 HRCON |= 0x80;
 delay_1ms();
 
 
  (*(unsigned char volatile xdata *)0x8008) = 2;
  (*(unsigned char volatile xdata *)0x8007) = 7; 
  (*(unsigned char volatile xdata *)0x8006) = 7; 
 
 
 Uart0Mode1();
 printf("run====\r\n");  
 
 NVRCaseTest();
 nvrCkSumTest();
 
 while(1)
 {
 P10=~P10;
 delay(1000);
 }
 }
