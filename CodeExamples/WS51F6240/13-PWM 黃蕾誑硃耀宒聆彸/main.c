/*********************************************************
*Copyright (C), 2020-2030, 深圳前海维晟智能技术有限公司
*文件名:	pwm.c
*作  者:	
*版  本:	
*日  期:	
*描  述:	
*备  注:     
**********************************************************/
#include "WS51F6240.h"
#include "intrins.h"
#include <stdio.h>

static void delay(int i)
{
	long j;
	for(j=0;j<10*i;++j);
}
static void delay_1ms(void)
{
	int j;
	for(j=0;j<1700;++j);
}

void UART1_write(signed char dat)
{
    S1BUF = dat;            //Send data to UART buffer
    while(TI1 != (S1CON&TI1));
    //清TI1
    S1CON &= ~TI1;
}

///重定向c库函数printf到串口，重定向后可使用printf函数
char putchar(char ch)
{
    /* 发送一个字节数据到串口 */
    UART1_write((signed char) ch);
        
    return ch;
}


/*****************************************************
*函数名称：void Uart1Mode1(void)
*函数功能：9600 波特率
*入口参数：
*出口参数：
*****************************************************/
void Uart1Mode1(void)
{
    /*************** UART1 模式1（波特率：9600）****************/
	S1CON = 0x80;	///8位异步模式(1), +0x10/中断使能, +0x20/多机通信使能位, +0x40/串行接收使能位
	S1RELL = 972;
	S1RELH = 972>>8;	
}


/**********************************************************************************
**	WS51F0032 系列芯片最多可输出 8 路独立的 PWM 波形，
**	这 8 路 PWM 又可以两两结合，组成 4 组带 8 位死区控制的互补 PWM 输出。
**	PWM0~PWM5 这 6 通道 PWM 还具有刹车和掩模功能，可用于电机驱动。
***********************************************************************************/
// 寄存器 PWMFLG0 标志
#define P0PIF0	0x01		//bit0 PWM0 计数器计数到最大值中断标志，仅中心对齐模式下有效
#define P0ZIF0	0x02    //bit1 PWM0 计数器计数到 0 中断标志
#define P1ZIF0	0x08    //bit3 PWM1 计数器计数到 0 中断标志
#define P2PIF0	0x10    //bit4 PWM2 计数器计数到最大值中断标志，仅中心对齐模式下有效
#define P2ZIF0	0x20    //bit5 PWM2 计数器计数到 0 中断标志
#define P3ZIF0	0x80    //bit7 PWM3 计数器计数到 0 中断标志

// 寄存器 PWMFLG1 标志
#define P4PIF1	0x01		//bit0 PWM4 计数器计数到最大值中断标志，仅中心对齐模式下有效
#define P4ZIF1	0x02    //bit1 PWM4 计数器计数到 0 中断标志
#define P5ZIF1	0x08    //bit3 PWM5 计数器计数到 0 中断标志
#define P6ZIF1	0x20    //bit5 PWM6 计数器计数到 0 中断标志
#define P7ZIF1	0x80    //bit7 PWM7 计数器计数到 0 中断标志

// 寄存器 FBFLG 标志
#define FBPF	0x04		//P14 刹车引脚刹车信号引起刹车中断标志
#define FBAF	0x02		//ADC 比较结果刹车信号引起刹车中断标志
#define FBCF	0x01		//ADC 比较结果刹车信号引起刹车中断标志

void PWM_isr(void) interrupt 5
{
	P00 = ~P00;
	//PWMFLG0
//	printf("%bx\r", PWMFLG0);
	if(PWMFLG0 & P0PIF0)	//PWM0 计数器计数到最大值中断标志，仅中心对齐模式下有效
	{
//		P00 = 1;
		printf("P0X    \n\r");
		PWMFLG0 &= ~P0PIF0;	
	}
    if(PWMFLG0 & P0ZIF0)
	{	
//		P00 = 0;
		printf("0    \n\r");	//PWM0 计数器计数到 0 中断标志
		PWMFLG0 &= ~P0ZIF0;
	}
    if(PWMFLG0 & P1ZIF0)
	{	
		printf("1    \n\r");	//PWM1 计数器计数到 0 中断标志
		PWMFLG0 &= ~P1ZIF0;
	}
    if(PWMFLG0 & P2PIF0)
	{	
		printf("P2X    \n\r");	//PWM2 计数器计数到最大值中断标志，仅中心对齐模式下有效
		PWMFLG0 &= ~P2PIF0;
	}
    if(PWMFLG0 & P2ZIF0)
	{	
		printf("2    \n\r");	//PWM2 计数器计数到 0 中断标志
		PWMFLG0 &= ~P2ZIF0;
	}
    if(PWMFLG0 & P3ZIF0)
	{	
		printf("3    \n\r");	//PWM3 计数器计数到 0 中断标志
		PWMFLG0 &= ~P3ZIF0;
	}
	
//	printf("%bx\r", PWMFLG1);
	//PWMFLG1
	if(PWMFLG1 & P4PIF1)	//PWM4 计数器计数到最大值中断标志，仅中心对齐模式下有效
	{
		printf("P4X    \n\r");
		PWMFLG1 &= ~P4PIF1;	
	}
    if(PWMFLG1 & P4ZIF1)
	{	
		printf("4    \n\r");	//PWM4 计数器计数到 0 中断标志
		PWMFLG1 &= ~P4ZIF1;
	}
    if(PWMFLG1 & P5ZIF1)
	{	
		printf("5    \n\r");	//PWM5 计数器计数到 0 中断标志
		PWMFLG1 &= ~P5ZIF1;
	}

}	

void PWM_PS_isr(void) interrupt 7
{
	if(PMSCON & 0x2)	//读掩模标志
	{
		P00 = 1;
	}
	else
	{
		P00 = 0;
	}
	if(PMSCON & 0x1)
	{
		printf("PS\n");
		PMSCON &= ~0x1;	
	}
	printf("%bx\n",PMSCON);
}

void PWM_FB_isr(void) interrupt 6
{
	P00 = 1;
//	printf("%bx\n",FBFLG);
	if(FBFLG & FBPF)	
	{
		printf("FB\n");
		FBFLG &= ~FBPF;	
	}
	P00 = 0;
}

//=============================== PWM配置寄存器 ================================
// 寄存器 PWMnCFG(n=0,2,4)
#define PWM_ZIE	0x80	//PWMn 计数器计数到 0 中断使能
#define PWM_PIE	0x40	//中心对齐模式下，PWMn 计数器计数到最大值中断使能。
#define PWM_MOD	0x20	//（0：边沿对齐； 1：中心对齐）
#define PWM_TOG	0x10	//极性选择，为 1 时输出反向
#define PWM_OM	0x08	//互补输出：（1：波形互换）
#define PWM_CKS 0			//时钟源选择：0系统时钟
											//1 HRC
											//2 LRC
											//3 LOSC
// 寄存器 PWMnCFG(n=1,3,5)							
#define PWM_SN	0x0 	

// 寄存器 PWM6CFG
#define PWM7_ZIE	0x80	//PWMn 计数器计数到 0 中断使能
#define PWM6_ZIE	0x40	//PWMn 计数器计数到 0 中断使能
#define PWM7_TOG	0x20	//极性选择，为 1 时输出反向
#define PWM6_TOG	0x10	//极性选择，为 1 时输出反向	
#define PWM6_SN		0x08	


// 寄存器 PWMUPD  即刻新的周期和占空比配置值
#define PWMUPD0	0x01	//bit0 
#define PWMUPD1	0x02	//bit1
#define PWMUPD2	0x04	//bit2
#define PWMUPD3	0x08	//bit3
#define PWMUPD4	0x10	//bit4
#define PWMUPD5	0x20	//bit5	

// 寄存器 PWMCLR 写 1 清零 PWMn 计数器
#define PWM0CLR	0x01	//bit0 
#define PWM1CLR	0x02	//bit1
#define PWM2CLR	0x04	//bit2
#define PWM3CLR	0x08	//bit3
#define PWM4CLR	0x10	//bit4
#define PWM5CLR	0x20	//bit5
#define PWM6CLR	0x40	//bit6
#define PWM7CLR	0x80	//bit7		


//=============================== 刹车寄存器 ================================
// 寄存器 FBCON
#define FBPE	0x80	//P14 输入作为刹车信号使能位，1 有效
#define FBAE	0x40	//ADC 比较结果作为刹车信号使能位，1 有效
#define FBCE	0x20	//比较器结果作为刹车信号使能位，1 有效
#define FBIE	0x10	//刹车中断使能位
#define FPOL	0x08	//P14 输入刹车信号极性选择
#define FPFTR	7			//P14 刹车信号滤波配置，对 P53 进行 FPFTR 个系统时钟的滤波

// 寄存器 FBDAT
#define FDEN		0x80	//bit0-bit5
#define FBDAT0	0x01	//bit0
#define FBDAT1	0x02	//bit1
#define FBDAT2	0x04	//bit2
#define FBDAT3	0x08	//bit3
#define FBDAT4	0x10	//bit4
#define FBDAT5	0x20	//bit5

//=============================== 掩膜寄存器 ================================
// 寄存器 PMCON 	掩模数据输出功能使能位(非刹车状态时，在 PWMnRUN 为 0 或 PWMn 被掩模的情况下：)
#define PMEN0	0x01	//bit0 掩模数据输出功能使能(0:为高阻；1：为PMDAT决定)
#define PMEN1	0x02	//bit1
#define PMEN2	0x04	//bit2
#define PMEN3	0x08	//bit3
#define PMEN4	0x10	//bit4
#define PMEN5	0x20	//bit5
// 寄存器 PMDAT 	PWM 掩模数据	
#define PMDAT0	0x01	//bit0 掩模数据
#define PMDAT1	0x02	//bit1
#define PMDAT2	0x04	//bit2
#define PMDAT3	0x08	//bit3
#define PMDAT4	0x10	//bit4
#define PMDAT5	0x20	//bit5
	
// 寄存器 PMSCON 	掩膜控制寄存器
#define PSE		0x80	//bit7:		掩模功能使能，1 有效
#define PSIE	0x40	//bit6:		掩模中断使能，1 有效
#define PSMOD	0x20	//bit5:		掩模计数触发边沿
										//1：在选中的 PWM 上升沿触发计数
										//0：在选中的 PWM 下降沿触发计数
#define PSCHS	0x00	//bit4-2:	掩模 PWM 选择(可选0~5)
#define PMSK	0x80	//bit1:		掩模标志
										//1：选择的 PWM 输出处在掩模状态
										//0：选择的 PWM 输出处在有效输出状态（非掩模状态）
#define PSIF	0x01	//bit0:		掩模中断标志，PSIE 使能后，PSIF 在选中的 PWM 输出在掩模状态和有效输出状态切换时由硬件置一

	
//	PMSDAL = 0;	//掩模有效个数寄存器
//	PMSDAH = 0;	//掩模有效个数寄存器
//	PMSDBL = 0;	//PMSDML = 0;	//掩模掉个数寄存器
//	PMSDBH = 0;	//PMSDMH = 0;	//掩模掉个数寄存器


// 规格书错了
#define SYSCL_VAL	0x00			//0x00     //HRC 	0
                            //0x20	   //LRC 	1
                            //0x40     //LOSC 2
//void INT2_ISR(void) interrupt 5 //I2C/Timer2/PWM/LED/EP0
//{
//	if(PWMFLG0&0x01)  //PWM0
//	{			
//			PWMFLG0 =0;
//		  P07 = ~P07;			
//	}	
//		if(PWMFLG1&0x01)  //PWM0
//	{			
//			PWMFLG1 =0;
//		  P06 = ~P06;		
//	}
//}	
void main(void)
{
	/********************** 系统时钟测试 HRC ***8*******************/
	SCCON = 0x00;
	HRCON |= 0X80;
  delay_1ms();

	/****************** UART1 模式1（波特率：9600）******************/
	Uart1Mode1();	//9600
  printf("RUN------\r\n");

	/********************* 打印PWM寄存器初始值 **********************/
	printf("打印PWM寄存器初始值\r\n");
	printf("PWM0PS=%bx,\r\nPWM1PS=%bx,\r\nPWM2PS=%bx,\r\nPWM3PS=%bx,\r\nPWM4PS=%bx,\r\nPWM5PS=%bx,\r\nPWM6PS=%bx,\r\nPWM7PS=%bx,\r\n", PWM0PS, PWM1PS, PWM2PS, PWM3PS, PWM4PS, PWM5PS, PWM6PS, PWM7PS);
	printf("PWM0DUTL=%bx,\t PWM0DUTH=%bx,\t PWM0DIVL=%bx,\t PWM0DIVH=%bx\r\n", PWM0DUTL, PWM0DUTH, PWM0DIVL, PWM0DIVH);
	printf("PWMCLR=0x%bx,\t PWMUPD=0x%2bx,\t PWMFLG0=0x%2bx,\t PWMFLG1=0x%2bx\r\n", PWMCLR, PWMUPD, PWMFLG0, PWMFLG1);
	printf("FBCON=0x%2bx,\t FBDAT=0x%2bx,\t FBFLG=0x%2bx,\t\r\n", FBCON, FBDAT, FBFLG);
	printf("PMDAT=0x%2bx,\t PMSCON=0x%2bx,\t\r\n", PMDAT, PMSCON);

	PWM0PS = 0x00;      //P00
	PWM1PS = 0x01;      //P01
	PWM2PS = 0x02;      //P02
	PWM3PS = 0x03;      //P03
	PWM4PS = 0x04;      //P04
	PWM5PS = 0x05;      //P05
	
	/******************************管脚配置**************************/
	P00F = 0x03;
	P01F = 0x03;
	P02F = 0x03;
	P03F = 0x03;
	P04F = 0x03;
	P05F = 0x03;
	
	P06F = 0x02;
	P07F = 0x02;
	P10F = 0x81;	
//	P02F=6;//UART1_RX
	P16F=6;//UART1_TX---p2

	
//=============================== PWM配置寄存器 ================================LRC: 32768Hz;
	/*	
	寄存器 PWMnCFG(n=0,2,4)		+PWM_ZIE	0x80	bit7：PWMn 计数器计数到 0 中断使能
								+PWM_PIE	0x40 	bit6：中心对齐模式下，PWMn 计数器计数到最大值中断使能。
								+PWM_MOD	0x20 	bit5：（0：边沿对齐； 1：中心对齐）
								+PWM_TOG	0x10 	bit4：极性选择，为 1 时输出反向
								+PWM_OM		0x08	bit3：互补输出：（1：波形互换）
								+PWM_CKS		1 	bit2-0：时钟源选择：0系统时钟
	寄存器 PWMnCFG(n=1,3,5)		+PWM_ZIE	0x80	bit7：PWMn 计数器计数到 0 中断使能	
								+PWM_TOG	0x10 	bit4：极性选择，为 1 时输出反向
								+PWM_SN		0x01	bit0：(1独立输出，0互补输出)			芯片搞反了
	**/
	/****************** PWM0/1组 ********************/
	PWM0CFG=PWM_CKS;				//PWM0配置			
	PWM1CFG=PWM_SN;					//独立输出
	
	/****************** PWM2/3组 ********************/
	PWM2CFG=PWM_CKS;		//PWM2配置
	PWM3CFG=PWM_SN;					//独立输出
	
	/****************** PWM4/5组 ********************/
	PWM4CFG=PWM_CKS;		//PWM4配置
	PWM5CFG=PWM_SN;					//独立输出



//=============================== PWM 占空比配置 ================================	
	/********* PWM0周期占空比配置10% **********/
	PWM0DUTL=10;
	PWM0DUTH=0;
	PWM0DIVL=99;
	PWM0DIVH=0;
	
//	/********* PWM1周期占空比配置20% **********/
	PWM1DUTL=20;
	PWM1DUTH=0;
	PWM1DIVL=99;
	PWM1DIVH=0;
	
	/********* PWM2周期占空比配置30% **********/
	PWM2DUTL=30;
	PWM2DUTH=0;
	PWM2DIVL=99;
	PWM2DIVH=0;
	
	/********* PWM3周期占空比配置40% **********/
	PWM3DUTL=40;
	PWM3DUTH=0;
	PWM3DIVL=99;
	PWM3DIVH=0;
	
	/********* PWM4周期占空比配置50% **********/
	PWM4DUTL=50;
	PWM4DUTH=0;
	PWM4DIVL=99;
	PWM4DIVH=0;
	
	/********* PWM5周期占空比配置60% **********/
	PWM5DUTL=60;
	PWM5DUTH=0;
	PWM5DIVL=99;
	PWM5DIVH=0;
	

	PWMRUN=0xff;	//运行使能

//	EINT4 = 1;		//掩膜中断使能
//	EINT3 = 1;		//刹车中断使能
	EINT2 = 1;		//计数中断使能
	EA = 1;	
		
	
    while(1)
	{
//		P06 = ~P06;
//		delay(50);
		if(P10 == 0)
		{
			delay(100);
			if(P10 == 0)
			{
								
				while(P10 == 0)
//				printf("run - pwm\r\n");
				
				//即刻更新周期占空比测试
				PWM4DUTL += 5;
				PWM5DUTL += 5;
				PWM0DUTL += 5;
				PWM1DUTL += 5;
				PWM2DUTL += 5;
				PWM3DUTL += 5;		
				/*	
				寄存器 PWMUPD 	写 1 载入 PWM0-5 新的周期和占空比配置值
									+PWMUPD0	0x01	//bit0 
									+PWMUPD1	0x02	//bit1
									+PWMUPD2	0x04	//bit2
									+PWMUPD3	0x08	//bit3
									+PWMUPD4	0x10	//bit4
									+PWMUPD5	0x20	//bit5	
				**/
						
				PWMUPD = 0x3F;	//
			}				
		}	
	}
    
}