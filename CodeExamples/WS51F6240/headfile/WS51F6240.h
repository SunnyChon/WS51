#ifndef __WS51F6240_H
#define __WS51F6240_H
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
#define PWMRUN     (*(unsigned char volatile xdata *)0x8040)
#define PWMCLR     (*(unsigned char volatile xdata *)0x8041)
#define PWMUPD     (*(unsigned char volatile xdata *)0x8043)
#define PWMFLG0    (*(unsigned char volatile xdata *)0x8044)
#define PWMFLG1    (*(unsigned char volatile xdata *)0x8045)
#define PMEN      (*(unsigned char volatile xdata *)0x8048)
#define PMDAT      (*(unsigned char volatile xdata *)0x8049)
#define PMSCON     (*(unsigned char volatile xdata *)0x804a)
#define PMSDL     (*(unsigned char volatile xdata *)0x804b)
#define PMSDH     (*(unsigned char volatile xdata *)0x804c)
#define PMSML     (*(unsigned char volatile xdata *)0x804d)
#define PMSMH     (*(unsigned char volatile xdata *)0x804e)
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
#define LEDCFG     (*(unsigned char volatile xdata *)0x80d0)
#define LED0D0    (*(unsigned char volatile xdata *)0x80d2)
#define LED0D1    (*(unsigned char volatile xdata *)0x80d3)
#define LED0D2    (*(unsigned char volatile xdata *)0x80d4)
#define LED1D0    (*(unsigned char volatile xdata *)0x80da)
#define LED1D1    (*(unsigned char volatile xdata *)0x80db)
#define LED1D2    (*(unsigned char volatile xdata *)0x80dc)
#define FBCON      (*(unsigned char volatile xdata *)0x80e0)
#define FBDAT      (*(unsigned char volatile xdata *)0x80e1)
#define FBFLG      (*(unsigned char volatile xdata *)0x80e2)
#define PIMOD      (*(unsigned char volatile xdata *)0x80e8)
#define P0IMSK     (*(unsigned char volatile xdata *)0x80e9)
#define P1IMSK     (*(unsigned char volatile xdata *)0x80ea)
#define P2IMSK     (*(unsigned char volatile xdata *)0x80eb)
#define BZCON      (*(unsigned char volatile xdata *)0x80f0)
#define BZPSC      (*(unsigned char volatile xdata *)0x80f1)
#define BZDUT      (*(unsigned char volatile xdata *)0x80f2)
#define BZDIV      (*(unsigned char volatile xdata *)0x80f3)
		
#define ACBCON	  (*(unsigned char volatile xdata *)0x82b0)
#define AKDAT     (*(unsigned char volatile xdata *)0x82b2)
#define AMDAT     (*(unsigned char volatile xdata *)0x82b4)

#define MECON      (*(unsigned char volatile xdata *)0x8300)
#define FSCMD      (*(unsigned char volatile xdata *)0x8301)
#define BTMSK      (*(unsigned char volatile xdata *)0x8302)
#define FSDAT      (*(unsigned char volatile xdata *)0x8303)
#define FSFLG       (*(unsigned char volatile xdata *)0x8304)
#define PADR        (*(unsigned char volatile xdata *)0x8305)
#define FSDARL       (*(unsigned char volatile xdata *)0x8306)
#define FSDARH       (*(unsigned char volatile xdata *)0x8307)
#define CKSUML     (*(unsigned char volatile xdata *)0x8308)
#define CKSUMH     (*(unsigned char volatile xdata *)0x8309)
#define IDCODE0    (*(unsigned char volatile xdata *)0x830a)
#define IDCODE1    (*(unsigned char volatile xdata *)0x830b)
#define IDCODE2    (*(unsigned char volatile xdata *)0x830c)
#define SPMAX      (*(unsigned char volatile xdata *)0x8407)



#define idata01     (*(unsigned char volatile idata *)0x01) 
#define idata55     (*(unsigned char volatile idata *)0x55) 
#define idata7f     (*(unsigned char volatile idata *)0x7f) 
#define idata80     (*(unsigned char volatile idata *)0x80) 
#define idatad5     (*(unsigned char volatile idata *)0xd5) 
#define idataff     (*(unsigned char volatile idata *)0xff) 
#define data80      (*(unsigned char volatile data *)0x80)  
#define datad5      (*(unsigned char volatile data *)0xd5)  
#define dataff      (*(unsigned char volatile data *)0xff)  
#define pdata00     (*(unsigned char volatile pdata *)0x00) 
#define pdata55     (*(unsigned char volatile pdata *)0x55) 
#define pdataff     (*(unsigned char volatile pdata *)0xff) 
#define xdata100    (*(unsigned char volatile xdata *)0x100)
#define xdata155    (*(unsigned char volatile xdata *)0x155)
#define xdata1ff    (*(unsigned char volatile xdata *)0x1ff)

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
sbit P22 = P2^2;	//6652
sbit P23 = P2^3; 	//6652
sbit P24 = P2^4;	//6652
sbit P25 = P2^5; 	//6652
sbit P26 = P2^6;	//6652
sbit P27 = P2^7; 	//6652

sbit P10 = P1^0;
sbit P11 = P1^1;
sbit P12 = P1^2;
sbit P13 = P1^3;
sbit P14 = P1^4;
sbit P15 = P1^5;
sbit P16 = P1^6;
sbit P17 = P1^7;

//sbit P30 = P3^0;
//sbit P31 = P3^1;
//sbit P32 = P3^2;
//sbit P33 = P3^3;
//sbit P34 = P3^4;
//sbit P35 = P3^5;
//sbit P36 = P3^6;	//6232
//sbit P37 = P3^7; 	//6232

/* 中断优先级寄存器 IP (B8H) */
sbit PX3 = IP^6;		/* INT4 优先级控制位，用于 Touch Key/WDT/LVD/WKT/EP1 中断 */
sbit PX2 = IP^5;		/* INT3 优先级控制位， 用于 IIC/Timer2/PWM/EP0 中断 */
sbit PS0 = IP^4;		/* INT2 优先级控制位，用于 UART0 中断 */
sbit PT1 = IP^3;		/* Timer 1 优先级控制位 */
sbit PX1 = IP^2;		/* INT1 优先级控制位 */
sbit PT0 = IP^1;		/* Timer 0 优先级控制位 */
sbit PX0 = IP^0;		/* INT0 优先级控制位 */

/* 中断优先级寄存器 EXIP (F8H) */
sbit PX6 = EXIP^2;		/* INT6 优先级控制位，用于 RTC/UART2/Timer 4/EP4 中断 */
sbit PX5 = EXIP^1;		/* INT5 优先级控制位，用于 ADC/SPI/Timer 4/SCM/EP3 中断 */
sbit PX4 = EXIP^0;		/* INT4 优先级控制位，用于 CMP/UART1/Timer 3/EP2 中断 */

/* 中断使能寄存器 IE (A8H) */
sbit EA = 	 IE^7;		/* 全局中断使能控制位 */
sbit EINT3 = IE^6;		/* 用于 Touch Key/WDT/LVD/WKT/EP1 中断 */
sbit EINT2 = IE^5;		/* 用于 IIC/Timer2/PWM/EP0 中断 */
sbit ES0 = IE^4;		/* UART0 中断 */
sbit ET1 = 	 IE^3;		/* 定时器 1 中断使能控制位 */
sbit EINT1 = IE^2;		/* 中断 1 使能控制位（中断 1 用于外部中断 1） */
sbit ET0 = 	 IE^1;		/* 定时器 0 中断使能控制位 */
sbit EINT0 = IE^0;		/* 0 使能控制位（中断 0 用于外部中断 0） */

/* 中断使能寄存器 EXIE (E8H) */
sbit EINT6 = EXIE^2;		/* INT7 中断使能控制位，用于 RTC/UART2/Timer 4/EP4 中断 */	//6652
sbit EINT5 = EXIE^1;		/* INT5 中断使能控制位，用于 ADC/SPI/SCM/EP3 中断 */
sbit EINT4 = EXIE^0;		/* INT4 使能控制位，用于 UART1/Timer3/EP2 中断 */

/* 外部中断使能寄存器 EPIE (D8H) */
sbit EP3IE = EPIE^3;		/* EP3 中断使能信号 */
sbit EP2IE = EPIE^2;		/* EP2 中断使能信号 */
sbit EP1IE = EPIE^1;		/* EP1 中断使能信号 */
sbit EP0IE = EPIE^0;		/* EP0 中断使能信号 */

/* 串口UART0寄存器 S0CON (98H) */
sbit SM00 = S0CON^7;	/* 串口 0 模式选择位， */
sbit SM10 = S0CON^6;	/* 串口 0 模式选择位， */
sbit SM20 = S0CON^5;	/* 多机通信使能位， 1 有效 */
sbit REN0 = S0CON^4;	/* 串行接收使能位， 1 有效 */
sbit TB80 = S0CON^3;	/* 发送的第 9 位数据 */
sbit RB80 = S0CON^2;	/* 接收的第 9 位数据 */
sbit TI0 = 	S0CON^1;	/* 发送中断标志， 1 有效，写 0 清除 */
sbit RI0 =  S0CON^0;	/* 接收中断标志， 1 有效，写 0 清除 */

/* 定时器0/1 TCON (88H) */
sbit TF1 = TCON^7;		/* 定时器 0 模式 3 的 TH0 溢出/定时器 1 溢出标志位，中断被响应后自动清 0. */
sbit TR1 = TCON^6;		/* 定时器 1 运行控制位， 1 有效 */
sbit TF0 = TCON^5;		/* 定时器 0 溢出标志位，中断被响应后自动清 0 */
sbit TR0 = TCON^4;		/* 定时器 0 运行控制位， 1 有效 */
sbit IE1 = TCON^3;		/* 外部中断 1 使能位， 1 有效 */
sbit IT1 = TCON^2;		/* 外部中断 1 触发类型控制位 */
sbit IE0 = TCON^1;		/* 外部中断 0 使能位， 1 有效 */
sbit IT0 = TCON^0;		/* 外部中断 0 触发类型控制位 */

/* 定时器2 T2CON (C8H) */
sbit TF2 =   T2CON^7;		/* 定时器 2 溢出标志位。 当 RCLK 或 TCLK 为 1， TF2 不会被置 1 */
sbit EXF2 =  T2CON^6;		/* T2EX 触发标志。 */
sbit RCLK =  T2CON^5;		/* UART0 在模式 1 和 3 时使用定时器 1/2 作为接收波特率时钟 */
sbit TCLK =  T2CON^4;		/* UART0 在模式 1 和 3 时使用定时器 1/2 作为发送波特率时钟 */
sbit EXEN2 = T2CON^3;		/* T2EX 使能信号，在定时器没有作为 UART0 时钟时 T2EX 有效 */
sbit TR2 =   T2CON^2;		/* 定时器 2 启动信号， 1 有效 */
sbit CT2 =   T2CON^1;		/* 定时功能或计数功能选择信号 */
sbit CPRL2 = T2CON^0;		/* 抓取或重载功能选择信号。当 RCLK 或 TCLK 为 1 时，定时器强制进入 Timer 2 重载模式 */

/* 模数转换器 ADCON (C0H) */
sbit ADST =  ADCON^7;		/* ADC 转换开始控制位，写 1 启动转换，转换后硬件自动清 0 */
sbit ADIE =  ADCON^6;		/* ADC 中断使能位 */
sbit ADCF =  ADCON^0;		/* ADC 采样完成标志 */


/* 串口UART1 寄存器S1CON (9BH) 不可位寻址 */
#define SM11    0x80		/* 工作模式选择 */
#define IE1     0x40		/* 中断使能， 1 有效 */
#define SM21    0x20		/* 多机通信使能位， 1 有效 */
#define REN1    0x10		/* 串行接收使能位， 1 有效 */
#define TB81    0x08		/* 发送的第 9 位数据 */
#define RB81    0x04		/* 接收的第 9 位数据 */
#define TI1     0x02		/* 发送中断标志， 1 有效，写 0 清除 */
#define RI1     0x01		/* 接收中断标志， 1 有效，写 0 清除 */

#define ROR_8BIT(X,Y) ((X<<(8-Y))|(X>>Y))
#define ROL_8BIT(X,Y) ((X>>(8-Y))|(X<<Y)) 

typedef 	unsigned char	u8;
typedef 	unsigned int	u16;
typedef 	unsigned long	u32;
typedef     unsigned char   uint8_t;
typedef     unsigned int    uint16_t;
typedef     unsigned long   uint32_t;

typedef     signed char     int8_t;
typedef     signed int      int16_t;
typedef     signed long     int32_t;
#endif

