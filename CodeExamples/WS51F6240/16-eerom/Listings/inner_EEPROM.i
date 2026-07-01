
#line 1 "inner_EEPROM.c" /0












 
 
  
#line 1 "inner_EEPROM.h" /0
 
 
 
 
 
 
 
 
 
 
 
 
 void writeData2EEPROM(unsigned char *buf,unsigned short SectorAddr,unsigned short len);
 void readDatafromEEPROM(unsigned char *buf,unsigned short SectorAddr,unsigned short len);
 
 
#line 15 "inner_EEPROM.c" /0
 
  
#line 1 "WS51F7030.h" /0
 
 
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
 sfr MRCON       = 0x8e;
 sfr MRCFG       = 0x8f;
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
 sfr P3          = 0xb0;
 sfr DACON       = 0xb1;
 sfr T3CON       = 0xb2;
 sfr T3MOD       = 0xb3;
 sfr T3RL        = 0xb4;
 sfr T3RH        = 0xb5;
 sfr T3CL        = 0xb6;
 sfr T3CH        = 0xb7;
 sfr IP          = 0xb8;
 sfr LVDCON      = 0xb9;
 sfr CPCON       = 0xba;
 sfr CPCFG       = 0xbb;
 sfr CPFLG       = 0xbc;
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
 sfr LXCON       = 0xe4;
 sfr LXCFG       = 0xe5;
 sfr LXDIVL      = 0xe6;
 sfr LXDIVH      = 0xe7;
 sfr EXIE        = 0xe8;
 sfr TKMXF0      = 0xe9;
 sfr TKMXF1      = 0xea;
 sfr TKMXF2      = 0xeb;
 sfr TKMNF0      = 0xec;
 sfr TKMNF1      = 0xed;
 sfr TKMNF2      = 0xee;
 sfr B           = 0xf0;
 sfr TKCON       = 0xf1;
 sfr TKCFG0      = 0xf2;
 sfr TKCFG1      = 0xf3;
 sfr TKNUM       = 0xf4;
 sfr TKFLG0      = 0xf5;
 sfr TKFLG1      = 0xf6;
 sfr TKFLG2      = 0xf7;
 sfr EXIP        = 0xf8;
 sfr PWCON       = 0xf9;
 sfr IT0CON      = 0xfa;
 sfr IT1CON      = 0xfb;
 sfr IDLFL       = 0xfc;
 sfr IDLFH       = 0xfd;
 sfr STPF        = 0xfe;
 
 extern xdata unsigned char P00F	   ;
 extern xdata unsigned char P01F	   ;
 extern xdata unsigned char P02F	   ;	  
 extern xdata unsigned char P03F	   ;	  
 extern xdata unsigned char P04F	   ;	  
 extern xdata unsigned char P05F	   ;	  
 extern xdata unsigned char P06F	   ;	  
 extern xdata unsigned char P07F	   ;	  
 
 extern xdata unsigned char P10F	   ;
 extern xdata unsigned char P11F	   ;
 extern xdata unsigned char P12F	   ;
 extern xdata unsigned char P13F	   ;
 extern xdata unsigned char P14F	   ;
 extern xdata unsigned char P15F	   ;
 extern xdata unsigned char P16F	   ;
 extern xdata unsigned char P17F	   ;
 extern xdata unsigned char P20F	   ;	  
 extern xdata unsigned char P21F	   ;	  
 extern xdata unsigned char P30F	   ;
 extern xdata unsigned char P31F	   ;
 extern xdata unsigned char P32F	   ;
 extern xdata unsigned char P33F	   ;
 extern xdata unsigned char P34F	   ;
 extern xdata unsigned char P35F	   ;
 extern xdata unsigned char P36F	   ;	 
 extern xdata unsigned char P37F	   ;	 
 
 extern xdata unsigned char PWMEN    ;
 extern xdata unsigned char PWMIE 	 ;
 extern xdata unsigned char PWMFLG	 ;
 
 extern xdata unsigned char PWM0CFG 	;
 extern xdata unsigned char PWM0PS	;	 
 extern xdata unsigned char PWM0DUTL	;
 extern xdata unsigned char PWM0DUTH	;
 extern xdata unsigned char PWM0DIVL	;
 extern xdata unsigned char PWM0DIVH	;
 extern xdata unsigned char PWM1PS	;	 
 extern xdata unsigned char PWM1DUTL	;
 extern xdata unsigned char PWM1DUTH	;
 extern xdata unsigned char PWM1DIVL	;
 extern xdata unsigned char PWM1DIVH	;
 
 extern xdata unsigned char PWM2CFG 	;
 extern xdata unsigned char PWM2PS	;	 
 extern xdata unsigned char PWM2DUTL	;
 extern xdata unsigned char PWM2DUTH	;
 extern xdata unsigned char PWM2DIVL	;
 extern xdata unsigned char PWM2DIVH	;
 extern xdata unsigned char PWM3PS	;	 
 extern xdata unsigned char PWM3DUTL	;
 extern xdata unsigned char PWM3DUTH	;
 extern xdata unsigned char PWM3DIVL	;
 extern xdata unsigned char PWM3DIVH	;
 
 extern xdata unsigned char PWM4CFG 	;
 extern xdata unsigned char PWM4PS	;	 
 extern xdata unsigned char PWM4DUTL	;
 extern xdata unsigned char PWM4DUTH	;
 extern xdata unsigned char PWM4DIVL	;
 extern xdata unsigned char PWM4DIVH	;
 extern xdata unsigned char PWM5PS	;	 
 extern xdata unsigned char PWM5DUTL	;
 extern xdata unsigned char PWM5DUTH	;
 extern xdata unsigned char PWM5DIVL	;
 extern xdata unsigned char PWM5DIVH	;
 
 
 extern xdata unsigned char PWM6CFG 	;	 
 extern xdata unsigned char PWM6PS	;	 
 extern xdata unsigned char PWM6DUTL	;	 
 extern xdata unsigned char PWM6DUTH	;	 
 extern xdata unsigned char PWM6DIVL	;	 
 extern xdata unsigned char PWM6DIVH	;	 
 extern xdata unsigned char PWM7PS	;	 
 extern xdata unsigned char PWM7DUTL	;	 
 extern xdata unsigned char PWM7DUTH ;	 
 extern xdata unsigned char PWM7DIVL ;	 
 extern xdata unsigned char PWM7DIVH ;	 
 
 extern xdata unsigned char PIMOD	;	 
 extern xdata unsigned char P0IMSK	;	 
 extern xdata unsigned char P1IMSK	;	 
 extern xdata unsigned char P2IMSK	;	 
 extern xdata unsigned char P3IMSK	;	 
 
 extern xdata unsigned char BZ0CON	;	 
 extern xdata unsigned char BZ0PSC	;	 
 extern xdata unsigned char BZ0DUT	;	 
 extern xdata unsigned char BZ0DIV	;	 
 
 
 extern xdata unsigned char BZ1CON	;	 
 extern xdata unsigned char BZ1PSC	;	 
 extern xdata unsigned char BZ1DUT	;	 
 extern xdata unsigned char BZ1DIV	;	 
 
 
 extern xdata unsigned char TKPCS0	 ;
 extern xdata unsigned char TKPCS1	 ;
 extern xdata unsigned char TKPCS2	 ;
 extern xdata unsigned char TKPCS3	 ;	 
 extern xdata unsigned char TKPCS4	 ;	 
 extern xdata unsigned char TKPCS5	 ;	 
 
 extern xdata unsigned char TK0MXL   ;
 extern xdata unsigned char TK0MXH   ;
 extern xdata unsigned char TK1MXL   ;
 extern xdata unsigned char TK1MXH   ;
 extern xdata unsigned char TK2MXL   ;
 extern xdata unsigned char TK2MXH   ;
 extern xdata unsigned char TK3MXL   ;
 extern xdata unsigned char TK3MXH   ;
 extern xdata unsigned char TK4MXL   ;
 extern xdata unsigned char TK4MXH   ;
 extern xdata unsigned char TK5MXL   ;
 extern xdata unsigned char TK5MXH   ;
 extern xdata unsigned char TK6MXL   ;
 extern xdata unsigned char TK6MXH   ;
 extern xdata unsigned char TK7MXL   ;
 extern xdata unsigned char TK7MXH   ;
 extern xdata unsigned char TK8MXL   ;
 extern xdata unsigned char TK8MXH   ;
 extern xdata unsigned char TK9MXL   ;
 extern xdata unsigned char TK9MXH   ;
 extern xdata unsigned char TK10MXL  ;
 extern xdata unsigned char TK10MXH  ;
 extern xdata unsigned char TK11MXL  ;
 extern xdata unsigned char TK11MXH  ;
 
 extern xdata unsigned char TK0MNL 	;
 extern xdata unsigned char TK0MNH 	;
 extern xdata unsigned char TK1MNL 	;
 extern xdata unsigned char TK1MNH 	;
 extern xdata unsigned char TK2MNL 	;
 extern xdata unsigned char TK2MNH 	;
 extern xdata unsigned char TK3MNL 	;
 extern xdata unsigned char TK3MNH 	;
 extern xdata unsigned char TK4MNL 	;
 extern xdata unsigned char TK4MNH 	;
 extern xdata unsigned char TK5MNL 	;
 extern xdata unsigned char TK5MNH 	;
 extern xdata unsigned char TK6MNL 	;
 extern xdata unsigned char TK6MNH 	;
 extern xdata unsigned char TK7MNL 	;
 extern xdata unsigned char TK7MNH 	;
 extern xdata unsigned char TK8MNL 	;
 extern xdata unsigned char TK8MNH 	;
 extern xdata unsigned char TK9MNL 	;
 extern xdata unsigned char TK9MNH 	;
 extern xdata unsigned char TK10MNL	;
 extern xdata unsigned char TK10MNH	;
 extern xdata unsigned char TK11MNL	;
 extern xdata unsigned char TK11MNH	;
 
 extern xdata unsigned char TK0MSL  ;
 extern xdata unsigned char TK0MSH  ;
 extern xdata unsigned char TK1MSL  ;
 extern xdata unsigned char TK1MSH  ;
 extern xdata unsigned char TK2MSL  ;
 extern xdata unsigned char TK2MSH  ;
 extern xdata unsigned char TK3MSL  ;
 extern xdata unsigned char TK3MSH  ;
 extern xdata unsigned char TK4MSL  ;
 extern xdata unsigned char TK4MSH  ;
 extern xdata unsigned char TK5MSL  ;
 extern xdata unsigned char TK5MSH  ;
 extern xdata unsigned char TK6MSL  ;
 extern xdata unsigned char TK6MSH  ;
 extern xdata unsigned char TK7MSL  ;
 extern xdata unsigned char TK7MSH  ;
 extern xdata unsigned char TK8MSL  ;
 extern xdata unsigned char TK8MSH  ;
 extern xdata unsigned char TK9MSL  ;
 extern xdata unsigned char TK9MSH  ;
 extern xdata unsigned char TK10MSL ;
 extern xdata unsigned char TK10MSH ;
 extern xdata unsigned char TK11MSL ;
 extern xdata unsigned char TK11MSH ;
 
 
 
 extern xdata unsigned char TK0PS	;	 
 extern xdata unsigned char TK1PS	;	 
 extern xdata unsigned char TK2PS	;	 
 extern xdata unsigned char TK3PS	;	 
 extern xdata unsigned char TK4PS	;	 
 extern xdata unsigned char TK5PS	;	 
 extern xdata unsigned char TK6PS	;	 
 extern xdata unsigned char TK7PS	;	 
 extern xdata unsigned char TK8PS	;	 
 extern xdata unsigned char TK9PS	;	 
 extern xdata unsigned char TK10PS	;	 
 extern xdata unsigned char TK11PS	;	 
 
 extern xdata unsigned char LXDAT00	;	 
 extern xdata unsigned char LXDAT01	;	 
 extern xdata unsigned char LXDAT02	;	 
 extern xdata unsigned char LXDAT03	;	 
 extern xdata unsigned char LXDAT04	;	 
 extern xdata unsigned char LXDAT05	;	 
 extern xdata unsigned char LXDAT06	;	 
 extern xdata unsigned char LXDAT07	;	 
 extern xdata unsigned char LXDAT08	;	 
 extern xdata unsigned char LXDAT09	;	 
 extern xdata unsigned char LXDAT10	;	 
 extern xdata unsigned char LXDAT11	;	 
 extern xdata unsigned char LXDAT12	;	 
 extern xdata unsigned char LXDAT13	;	 
 extern xdata unsigned char LXDAT14	;	 
 extern xdata unsigned char LXDAT15	;	 
 extern xdata unsigned char LXDAT16	;	 
 extern xdata unsigned char LXDAT17	;	 
 extern xdata unsigned char LXDAT18	;	 
 
 extern xdata unsigned char LSCON  	;
 extern xdata unsigned char LSCFG  	;
 extern xdata unsigned char LSDTM0 	;
 extern xdata unsigned char LSDTM1 	;
 extern xdata unsigned char LSPTM0 	;
 extern xdata unsigned char LSPTM1 	;
 extern xdata unsigned char LSCOM  	;
 
 extern xdata unsigned char LSPE0 	;
 extern xdata unsigned char LSPE1 	;
 extern xdata unsigned char LSPE2	;	 
 extern xdata unsigned char LSDAT0	;
 extern xdata unsigned char LSDAT1	;
 extern xdata unsigned char LSDAT2   ;	 
 
 extern xdata unsigned char MECON 	;
 extern xdata unsigned char FSCMD 	;
 extern xdata unsigned char BTMSK 	;
 extern xdata unsigned char FSDAT 	;
 extern xdata unsigned char FSFLG 	;
 extern xdata unsigned char PADR 	;
 extern xdata unsigned char FSADRL	;
 extern xdata unsigned char FSADRH	;
 
 extern xdata unsigned char CKSUML 	;
 extern xdata unsigned char CKSUMH 	;
 extern xdata unsigned char IDCODE0	;
 extern xdata unsigned char IDCODE1	;
 extern xdata unsigned char IDCODE2	;
 
 extern xdata unsigned char CHIPIDL	;
 extern xdata unsigned char CHIPIDH	;
 
 
 extern xdata unsigned char SPMAX	  ;	 
 
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
 sbit P36 = P3^6;	 
 sbit P37 = P3^7; 	 
 
 
 sbit PX3 = IP^6;		 
 sbit PX2 = IP^5;		 
 sbit PS0 = IP^4;		 
 sbit PT1 = IP^3;		 
 sbit PX1 = IP^2;		 
 sbit PT0 = IP^1;		 
 sbit PX0 = IP^0;		 
 
 
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
 
#line 16 "inner_EEPROM.c" /0
 
 







 
 void writeData2EEPROM(unsigned char *buf,unsigned short SectorAddr,unsigned short len)
 {
 unsigned char i=0;
 
 FSFLG=0X9A;
 
 FSCMD=0X42;
 for(i=0;i<len;++i)
 {
 
 FSADRL=(SectorAddr&0xff);
 FSADRH=((SectorAddr>>8)&0xff);
 SectorAddr++;
 
 FSDAT=buf[i];
 }
 
 FSFLG=0XA9;
 }
 
 







 
 void readDatafromEEPROM(unsigned char *buf,unsigned short SectorAddr,unsigned short len)
 {
 unsigned char i=0;
 
 
 FSCMD=0X45;
 for(i=0;i<len;++i)
 {
 
 FSADRL=(SectorAddr&0xff);
 FSADRH=((SectorAddr>>8)&0xff);
 SectorAddr++;
 
 buf[i]=FSDAT;
 }
 }
 
 
 
 
 
 
