//Header file for W51F6240 based on datasheet and simiular MCUs.
//2026 By SunnyAI

//Register addresses (SFR)
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
sfr TL0         = 0x8A;
sfr TL1         = 0x8B;
sfr TH0         = 0x8C;
sfr TH1         = 0x8D;
//sfr MRCON     = 0x8E;
//sfr MRCFG     = 0x8F;

sfr P1          = 0x90;
sfr XSCON       = 0x95;
sfr HRCON       = 0x96;
sfr LRCON       = 0x97;

sfr S0CON       = 0x98;
sfr S0BUF       = 0x99;
sfr S0CFG       = 0x9A;
sfr S1CON       = 0x9B;
sfr S1BUF       = 0x9C;
sfr S1RELL      = 0x9D;
sfr S1RELH      = 0x9E;
sfr RSTFLG      = 0x9F;

sfr P2          = 0xA0;
sfr I2CCON      = 0xA1;
sfr I2CADR      = 0xA2;
sfr I2CFG0      = 0xA3;
sfr I2CFG1      = 0xA4;
sfr I2CTXD      = 0xA5;
sfr I2CRXD      = 0xA6;
sfr I2CFLG      = 0xA7;

sfr IE          = 0xA8;
sfr WDTCON      = 0xA9;
sfr WDTFLG      = 0xAA;
sfr TL3         = 0xAE;
sfr TH3         = 0xAF;

//sfr P3        = 0xB0;  //exist but not avaliable in this MCU.
//sfr DACON     = 0xB1;
sfr T3CON       = 0xB2;
sfr T3MOD       = 0xB3;
sfr T3RL        = 0xB4;
sfr T3RH        = 0xB5;
sfr T3CL        = 0xB6;
sfr T3CH        = 0xB7;

sfr IP          = 0xB8;
sfr LVDCON      = 0xB9;
//sfr CPCON     = 0xBA;
//sfr CPCFG0    = 0xBB;
//sfr CPCFG1    = 0xBC;
sfr ATGCON      = 0xBD;
sfr ATGDLY      = 0xBE;
sfr ADCBGP      = 0xBF;

sfr ADCON       = 0xC0;
sfr ADCFG       = 0xC1;
sfr ADCHS       = 0xC2;
sfr ADCDL       = 0xC3;
sfr ADCDH       = 0xC4;
sfr ADCPC       = 0xC5;
sfr ADCPDL      = 0xC6;
sfr ADCPDH      = 0xC7;

sfr T2CON       = 0xC8;
sfr T2MOD       = 0xC9;
sfr T2CL        = 0xCA;
sfr T2CH        = 0xCB;
sfr TL2         = 0xCC;
sfr TH2         = 0xCD;
sfr SCMCON      = 0xCE;
sfr SCMFLG      = 0xCF;

sfr PSW         = 0xD0;
sfr WKTCON      = 0xD1;
sfr WKTSS       = 0xD2;
sfr OPCON       = 0xD3;
sfr OPCFG       = 0xD4;

sfr EPIE        = 0xD8;
sfr EPIF        = 0xD9;
sfr EP0CON      = 0xDA;
sfr EP1CON      = 0xDB;
sfr EP2CON      = 0xDC;
sfr EP3CON      = 0xDD;

sfr ACC         = 0xE0;
sfr SPCON       = 0xE1;
sfr SPDAT       = 0xE2;
sfr SPFLG       = 0xE3;
//sfr LXCON     = 0xE4;
//sfr LXCFG     = 0xE5;
//sfr LXDIVL    = 0xE6;
//sfr LXDIVH    = 0xE7;

sfr EXIE        = 0xE8;
//sfr BZCON     = 0xE9;
//sfr BZPSC     = 0xEA;
//sfr BZDUT     = 0xEB;
//sfr BZDIV     = 0xEC;

sfr B           = 0xF0;
//sfr TKCON     = 0xF1;
//sfr TKCFG0    = 0xF2;
//sfr TKCFG1    = 0xF3;
//sfr TKCFG2    = 0xF4;
//sfr TKNUM     = 0XF5;
//sfr TKFLG0    = 0xF6;
//sfr TKFLG1    = 0xF7;

sfr EXIP        = 0xF8;
sfr PWCON       = 0xF9;
sfr IT0CON      = 0xFA;
sfr IT1CON      = 0xFB;
sfr IDLFL       = 0xFC;
sfr IDLFH       = 0xFD;
sfr STPF        = 0xFE;
//sfr OKER      = 0xFF;

//XSFR
#define P00F       (*(unsigned char volatile xdata *)0x8000)
#define P01F       (*(unsigned char volatile xdata *)0x8001)
#define P02F       (*(unsigned char volatile xdata *)0x8002)
#define P03F       (*(unsigned char volatile xdata *)0x8003)
#define P04F       (*(unsigned char volatile xdata *)0x8004)
#define P05F       (*(unsigned char volatile xdata *)0x8005)
#define P06F       (*(unsigned char volatile xdata *)0x8006)
#define P07F       (*(unsigned char volatile xdata *)0x8007)

#define P10F       (*(unsigned char volatile xdata *)0x8008)
#define P11F       (*(unsigned char volatile xdata *)0x8009)
#define P12F       (*(unsigned char volatile xdata *)0x800a)
#define P13F       (*(unsigned char volatile xdata *)0x800b)
#define P14F       (*(unsigned char volatile xdata *)0x800c)
#define P15F       (*(unsigned char volatile xdata *)0x800d)
#define P16F       (*(unsigned char volatile xdata *)0x800e)
#define P17F       (*(unsigned char volatile xdata *)0x800f)

#define P20F       (*(unsigned char volatile xdata *)0x8010)
#define P21F       (*(unsigned char volatile xdata *)0x8011)
//#define P22F     (*(unsigned char volatile xdata *)0x8012)
//#define P23F     (*(unsigned char volatile xdata *)0x8013)
//#define P24F     (*(unsigned char volatile xdata *)0x8014)
//#define P25F     (*(unsigned char volatile xdata *)0x8015)

//#define P30F     (*(unsigned char volatile xdata *)0x8018)
//#define P31F     (*(unsigned char volatile xdata *)0x8019)
//#define P32F     (*(unsigned char volatile xdata *)0x801a)
//#define P33F     (*(unsigned char volatile xdata *)0x801b)
//#define P34F     (*(unsigned char volatile xdata *)0x801c)
//#define P35F     (*(unsigned char volatile xdata *)0x801d)
//#define P36F     (*(unsigned char volatile xdata *)0x801e)
//#define P37F     (*(unsigned char volatile xdata *)0x801f)

#define PWMRUN     (*(unsigned char volatile xdata *)0x8040)
#define PWMCLR     (*(unsigned char volatile xdata *)0x8041)
//#define PWMIE    (*(unsigned char volatile xdata *)0x8042)
#define PWMUPD     (*(unsigned char volatile xdata *)0x8043)
#define PWMFLG0    (*(unsigned char volatile xdata *)0x8044)
#define PWMFLG1    (*(unsigned char volatile xdata *)0x8045)

#define PMEN       (*(unsigned char volatile xdata *)0x8048)
#define PMDAT      (*(unsigned char volatile xdata *)0x8049)
#define PMSCON     (*(unsigned char volatile xdata *)0x804A)
#define PMSDL      (*(unsigned char volatile xdata *)0x804B)
#define PMSDH      (*(unsigned char volatile xdata *)0x804C)
#define PMSML      (*(unsigned char volatile xdata *)0x804D)
#define PMSMH      (*(unsigned char volatile xdata *)0x804E)

#define PWM0CFG    (*(unsigned char volatile xdata *)0x8050)
#define PWM0PS     (*(unsigned char volatile xdata *)0x8051)
#define PWM0DUTL   (*(unsigned char volatile xdata *)0x8054)
#define PWM0DUTH   (*(unsigned char volatile xdata *)0x8055)
#define PWM0DIVL   (*(unsigned char volatile xdata *)0x8056)
#define PWM0DIVH   (*(unsigned char volatile xdata *)0x8057)

#define PWM1CFG    (*(unsigned char volatile xdata *)0x8058)
#define PWM1PS     (*(unsigned char volatile xdata *)0x8059)
#define PWM1DUTL   (*(unsigned char volatile xdata *)0x805c)
#define PWM1DUTH   (*(unsigned char volatile xdata *)0x805d)
#define PWM1DIVL   (*(unsigned char volatile xdata *)0x805e)
#define PWM1DIVH   (*(unsigned char volatile xdata *)0x805f)

#define PWM2CFG    (*(unsigned char volatile xdata *)0x8060)
#define PWM2PS     (*(unsigned char volatile xdata *)0x8061)
#define PWM2DUTL   (*(unsigned char volatile xdata *)0x8064)
#define PWM2DUTH   (*(unsigned char volatile xdata *)0x8065)
#define PWM2DIVL   (*(unsigned char volatile xdata *)0x8066)
#define PWM2DIVH   (*(unsigned char volatile xdata *)0x8067)

#define PWM3CFG    (*(unsigned char volatile xdata *)0x8068)
#define PWM3PS     (*(unsigned char volatile xdata *)0x8069)
#define PWM3DUTL   (*(unsigned char volatile xdata *)0x806c)
#define PWM3DUTH   (*(unsigned char volatile xdata *)0x806d)
#define PWM3DIVL   (*(unsigned char volatile xdata *)0x806e)
#define PWM3DIVH   (*(unsigned char volatile xdata *)0x806f)

#define PWM4CFG    (*(unsigned char volatile xdata *)0x8070)
#define PWM4PS     (*(unsigned char volatile xdata *)0x8071)
#define PWM4DUTL   (*(unsigned char volatile xdata *)0x8074)
#define PWM4DUTH   (*(unsigned char volatile xdata *)0x8075)
#define PWM4DIVL   (*(unsigned char volatile xdata *)0x8076)
#define PWM4DIVH   (*(unsigned char volatile xdata *)0x8077)

#define PWM5CFG    (*(unsigned char volatile xdata *)0x8078)
#define PWM5PS     (*(unsigned char volatile xdata *)0x8079)
#define PWM5DUTL   (*(unsigned char volatile xdata *)0x807c)
#define PWM5DUTH   (*(unsigned char volatile xdata *)0x807d)
#define PWM5DIVL   (*(unsigned char volatile xdata *)0x807e)
#define PWM5DIVH   (*(unsigned char volatile xdata *)0x807f)

#define PWM6CFG    (*(unsigned char volatile xdata *)0x8080)
#define PWM6PS     (*(unsigned char volatile xdata *)0x8081)
#define PWM6DUTL   (*(unsigned char volatile xdata *)0x8084)
#define PWM6DUTH   (*(unsigned char volatile xdata *)0x8085)
#define PWM6DIVL   (*(unsigned char volatile xdata *)0x8086)
#define PWM6DIVH   (*(unsigned char volatile xdata *)0x8087)

#define PWM7CFG    (*(unsigned char volatile xdata *)0x8088)
#define PWM7PS     (*(unsigned char volatile xdata *)0x8089)
#define PWM7DUTL   (*(unsigned char volatile xdata *)0x808c)
#define PWM7DUTH   (*(unsigned char volatile xdata *)0x808d)
#define PWM7DIVL   (*(unsigned char volatile xdata *)0x808e)
#define PWM7DIVH   (*(unsigned char volatile xdata *)0x808f)

#define LEDCFG     (*(unsigned char volatile xdata *)0x80D0)
#define LED0D0     (*(unsigned char volatile xdata *)0x80D2)
#define LED0D1     (*(unsigned char volatile xdata *)0x80D3)
#define LED0D2     (*(unsigned char volatile xdata *)0x80D4)

#define LED1D0     (*(unsigned char volatile xdata *)0x80DA)
#define LED1D1     (*(unsigned char volatile xdata *)0x80DB)
#define LED1D2     (*(unsigned char volatile xdata *)0x80DC)

#define FBCON      (*(unsigned char volatile xdata *)0x80E0)
#define FBDAT      (*(unsigned char volatile xdata *)0x80E1)
#define FBFLG      (*(unsigned char volatile xdata *)0x80E2)

#define PIMOD      (*(unsigned char volatile xdata *)0x80e8)
#define P0IMSK     (*(unsigned char volatile xdata *)0x80e9)
#define P1IMSK     (*(unsigned char volatile xdata *)0x80ea)
#define P2IMSK     (*(unsigned char volatile xdata *)0x80eb)
//#define P3IMSK   (*(unsigned char volatile xdata *)0x80ec)

#define BZCON      (*(unsigned char volatile xdata *)0x80F0)
#define BZPSC      (*(unsigned char volatile xdata *)0x80F1)
#define BZDUT      (*(unsigned char volatile xdata *)0x80F2)
#define BDDIV      (*(unsigned char volatile xdata *)0x80F3)

#define ACBCON     (*(unsigned char volatile xdata *)0x82b0)
#define AKDAT      (*(unsigned char volatile xdata *)0x82b2)
#define AMDAT      (*(unsigned char volatile xdata *)0x82b4)

#define MECON      (*(unsigned char volatile xdata *)0x8300)
#define FSCMD      (*(unsigned char volatile xdata *)0x8301)
#define BTMSK      (*(unsigned char volatile xdata *)0x8302)
#define FSDAT      (*(unsigned char volatile xdata *)0x8303)
#define FSFLG      (*(unsigned char volatile xdata *)0x8304)
#define FSMSK      (*(unsigned char volatile xdata *)0x8305)
#define FSDARL     (*(unsigned char volatile xdata *)0x8306)
#define FSDARH     (*(unsigned char volatile xdata *)0x8307)

#define CKSUML     (*(unsigned char volatile xdata *)0x8308)
#define CKSUMH     (*(unsigned char volatile xdata *)0x8309)
#define IDCODE0    (*(unsigned char volatile xdata *)0x830A)
#define IDCODE1    (*(unsigned char volatile xdata *)0x830B)
#define IDCODE2    (*(unsigned char volatile xdata *)0x830C)

#define SPMAX      (*(unsigned char volatile xdata *)0x8407)

sbit P00 = P0^0;	//6232
sbit P01 = P0^1; 	//6232
sbit P02 = P0^2;	//6552
sbit P03 = P0^3; 	//6552
sbit P04 = P0^4;	//6552
sbit P05 = P0^5; 	//6552
sbit P06 = P0^6;	//6552
sbit P07 = P0^7; 	//6552
  
sbit P20 = P2^0;	//6552
sbit P21 = P2^1; 	//6552
sbit P22 = P2^2;	//6552
sbit P23 = P2^3; 	//6552
sbit P24 = P2^4;	//6552
sbit P25 = P2^5;	//6552

sbit P10 = P1^0;
sbit P11 = P1^1;
sbit P12 = P1^2;
sbit P13 = P1^3;
sbit P14 = P1^4;
sbit P15 = P1^5;
sbit P16 = P1^6;
sbit P17 = P1^7;

//Interrupt priority register - IP (B8H)
sbit PX3 = IP^6;		//INT4 priority controlling bit , for Touch Key/WDT/LVD/WKT/EP1 interrupt
sbit PX2 = IP^5;		//INT3 priority controlling bit , for IIC/Timer2/PWM/EP0 interrupt
sbit PS0 = IP^4;		//INT2 priority controlling bit , for UART0 interrupt
sbit PT1 = IP^3;		//Timer 1 priority controlling bit
sbit PX1 = IP^2;		//INT1 priority controlling bit
sbit PT0 = IP^1;		//Timer 0 priority controlling bit
sbit PX0 = IP^0;		//INT0 priority controlling bit

//Interrupt priority register - EXIP (F8H)
sbit PX5 = EXIP^1;		//INT5 priority controlling bit , for ADC/SPI/Timer 4/SCM/EP3 interrupt
sbit PX4 = EXIP^0;		//INT4 priority controlling bit , for CMP/UART1/Timer 3/EP2 interrupt

//Interrupt enable register - IE (A8H)
sbit EA    = IE^7;		//Global interrupt enable controlling bit
sbit EINT3 = IE^6;		//for Touch Key/WDT/LVD/WKT/EP1 interrupt (Warning : mixed information in datasheet!)
sbit EINT2 = IE^5;		//for IIC/Timer2/PWM/EP0 interrupt        (Warning : mixed information in datasheet!)
sbit ES0   = IE^4;		//UART0 interrupt
sbit ET1   = IE^3;		//timer 1 interrupt enable controlling bit
sbit EINT1 = IE^2;		//interrupt 1  enable controlling bit (interrupt 1 for external interrupt 1) 
sbit ET0   = IE^1;		//timer 0 interrupt enable controlling bit
sbit EINT0 = IE^0;		//0  enable controlling bit (interrupt 0 for external interrupt 0) 

//Interrupt enable register - (E8H)
sbit EINT5 = EXIE^1;		//INT5 interrupt enable controlling bit , for ADC/SPI/SCM/EP3 interrupt
sbit EINT4 = EXIE^0;		//INT4 interrupt enable controlling bit , for UART1/Timer3/EP2 interrupt

//External interrupt enable register - EPIE (D8H)
sbit EP3IE = EPIE^3;		//EP3 Interrupt enable signal
sbit EP2IE = EPIE^2;		//EP2 Interrupt enable signal
sbit EP1IE = EPIE^1;		//EP1 Interrupt enable signal
sbit EP0IE = EPIE^0;		//EP0 Interrupt enable signal

// Serial UART0 register - S0CON (98H)
sbit SM00 = S0CON^7;	//Serial 0 mode selection bit ,
sbit SM10 = S0CON^6;	//Serial 0 mode selection bit ,
sbit SM20 = S0CON^5;	//Multi-machine communication enable bit ,  1 = enable
sbit REN0 = S0CON^4;	//Serial RX enable bit ,  1 = enable 
sbit TB80 = S0CON^3;	//The 9th bit of data sent
sbit RB80 = S0CON^2;	//The 9th bit of data received
sbit TI0  = S0CON^1;	//Send interrupt flag ,  1 = enable , write 0 to clear
sbit RI0  = S0CON^0;	//Receive interrupt flag ,  1 = enable , write 0 to clear

//TImer 0/1 - TCON (88H)
sbit TF1 = TCON^7;		//TH0 overflow/timer 1 overflow flag of timer 0 mode 3 , interrupt audomatically clear when triggered. 
sbit TR1 = TCON^6;		//timer 1 run controlling bit ,  1 = enable 
sbit TF0 = TCON^5;		//timer 0 overflow flag , interrupt audomatically clear when triggered
sbit TR0 = TCON^4;		//timer 0 run controlling bit ,  1 = enable 
sbit IE1 = TCON^3;		// external interrupt 1 enable bit ,  1 = enable 
sbit IT1 = TCON^2;		// external interrupt 1 trigger type controlling bit
sbit IE0 = TCON^1;		// external interrupt 0 enable bit ,  1 = enable 
sbit IT0 = TCON^0;		// external interrupt 0 trigger type controlling bit 

//Timer 2 - T2CON (C8H)
sbit TF2   = T2CON^7;		//Timer 2 overflow flag. When RCLK or TCLK = 1 ,  TF2 != 1 
sbit EXF2  = T2CON^6;		//T2EX trigger flag 
sbit RCLK  = T2CON^5;		//Use timer 1/2 as receiving baud rate clock when UART0 in mode 1 and 3
sbit TCLK  = T2CON^4;		//Use timer 1/2 as sending baud rate clock when UART0 in mode 1 and 3
sbit EXEN2 = T2CON^3;		//T2EX enable signal , when timer isn't used for UART0 clock , T2EX valid
sbit TR2   = T2CON^2;		//Timer 2 start signal ,  1 = enable 
sbit CT2   = T2CON^1;		//Timing function or counting function selection signal 
sbit CPRL2 = T2CON^0;		//Catch or reload function selection signal. When RCLK or TCLK = 1 , force timer to enter Timer 2 reload mode. 

//Standard data types definitions
typedef   unsigned char	  u8;
typedef   unsigned int	  u16;
typedef   unsigned long	  u32;
typedef   unsigned char   uint8_t;
typedef   unsigned int    uint16_t;
typedef   unsigned long   uint32_t;


typedef   signed char     int8_t;
typedef   signed int      int16_t;
typedef   signed long     int32_t;