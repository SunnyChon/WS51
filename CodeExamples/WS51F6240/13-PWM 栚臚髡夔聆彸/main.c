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

unsigned char Tx_flag=0;
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

void PWM_PS_isr(void) interrupt 7
{ 
//	if(PMSCON & 0x2)	// 读掩模标志
//	{
//		P10 = 1;
//	}
//	else
//	{
//		P10 = 0;
//	}
	if(PMSCON & 0x1)	// 掩膜中断标志位
	{
//		printf("\n\rPS\n\r");
		PMSCON &= ~0x1;	
		P11 = ~P11;
	}
//	printf("\n\rPMSCON=%bx\n\r",PMSCON);
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
#define PWM_SN	0x01	//(1独立输出，0互补输出)

// 寄存器 PWM6CFG
#define PWM7_ZIE	0x80	//PWMn 计数器计数到 0 中断使能
#define PWM6_ZIE	0x40	//PWMn 计数器计数到 0 中断使能
#define PWM7_TOG	0x20	//极性选择，为 1 时输出反向
#define PWM6_TOG	0x10	//极性选择，为 1 时输出反向	
#define PWM6_SN		0x08	//(1独立输出，0互补输出)


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
#define FPFTR	7			//P14 刹车信号滤波配置，对 P14 进行 FPFTR 个系统时钟的滤波

// 寄存器 FBDAT
#define FDEN		0x80	//bit0-bit5
#define FBDAT0	0x01	//bit0
#define FBDAT1	0x02	//bit1
#define FBDAT2	0x04	//bit2
#define FBDAT3	0x08	//bit3
#define FBDAT4	0x10	//bit4
#define FBDAT5	0x20	//bit5

//=============================== 掩膜寄存器 ================================
// 寄存器 PMEN 	掩模数据输出功能使能位(非刹车状态时，在 PWMnRUN 为 0 或 PWMn 被掩模的情况下：)
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




// 规格书错了
#define SYSCL_VAL	0x00	//0x00     //HRC 	0
                        //0x20	   //LRC 	1
                        //0x40     //LOSC 2
 
void main(void)
{
	/*******************  系统时钟测试 HRC************************/
	SCCON = 0x00;
  delay_1ms();

	PWM0PS = 0x00;      //P00
	PWM1PS = 0x01;      //P01
	PWM2PS = 0x02;      //P02
	PWM3PS = 0x03;      //P03
	PWM4PS = 0x04;      //P04
	PWM5PS = 0x05;      //P05

	
	/*****************************管脚配置************************/
	P00F = 0X03;
	P01F = 0X03;
	P02F = 0X03;  
	P03F = 0X03;  
	P04F = 0X03;
	P05F = 0X03;
	
	P10F = 0x02;
	P11F = 0x02;
	P12F = 0x81;

//	P02F=6;//UART1_RX
	P16F=6;//UART1_TX-----P2	



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
	PWM0CFG=PWM_CKS;		//PWM0配置
	PWM1CFG=0;				//独立输出
//	PWM1CFG=PWM_SN;			//互补输出		0：独立；1：互补
	
	/****************** PWM2/3组 ********************/
	PWM2CFG=PWM_CKS;		//PWM2配置
	PWM3CFG=0;				//独立输出
//	PWM3CFG=PWM_SN;			//互补输出
	
	/****************** PWM4/5组 ********************/
	PWM4CFG=PWM_CKS;		//PWM4配置
	PWM5CFG=0;		//独立输出
//	PWM5CFG=PWM_SN;			//互补输出

//=============================== 掩膜寄存器 ================================
	/*	掩模数据输出功能使能位(非刹车状态)
	
	注：功能修改为使能掩膜通道，不作为掩膜有效电平使能
	寄存器 PMEN 		+PMEN0	0x01	//bit0 掩模数据输出功能使能(0:为高阻；1：为PMDAT决定)
						+PMEN1	0x02	//bit1
						+PMEN2	0x04	//bit2
						+PMEN3	0x08	//bit3
						+PMEN4	0x10	//bit4
						+PMEN5	0x20	//bit5
	**/
//	PMEN = 0x00;
		PMEN = 0x3f;
	/*	
	寄存器 PMDAT 	PWM 掩模数据	
	
	注：掩膜有效电平可选高低，无高阻状态
						+PMDAT0	0x01	//bit0 掩模数据
						+PMDAT1	0x02	//bit1
						+PMDAT2	0x04	//bit2
						+PMDAT3	0x08	//bit3
						+PMDAT4	0x10	//bit4
						+PMDAT5	0x20	//bit5	
	**/

	PMDAT = 0x00;
//	PMDAT = 0;
	
	/* 寄存器 PMSCON 	掩膜控制寄存器
						+PSE		0x80	//bit7:		掩模功能使能，1 有效
						+PSIE		0x40	//bit6:		掩模中断使能，1 有效
						+PSMOD	0x20	//bit5:		掩模计数触发边沿
													//1：在选中的 PWM 上升沿触发计数
													//0：在选中的 PWM 下降沿触发计数
						+PSCHS	0x00	//bit4-2:	掩模 PWM 选择(可选0~5)
						+PMSK		0x80	//bit1:		掩模标志
													//1：选择的 PWM 输出处在掩模状态
													//0：选择的 PWM 输出处在有效输出状态（非掩模状态）
						+PSIF		0x01	//bit0:		掩模中断标志，PSIE 使能后，PSIF 在选中的 PWM 输出在掩模状态和有效输出状态切换时由硬件置一
	**/
	PMSCON = PSE+PSIE+0x04+PSMOD;//
	
	PMSDL = 3;	//掩模有效个数寄存器
	PMSDH = 0;	//掩模有效个数寄存器
	PMSML = 3;	//PMSML = 0;	//掩模掉个数寄存器
	PMSMH = 0;	//PMSMH = 0;	//掩模掉个数寄存器
	
	

//=============================== PWM 占空比配置 ================================	
	/********* PWM0周期占空比配置10% **********/
	PWM0DUTL=10;
	PWM0DUTH=0;
	PWM0DIVL=99;
	PWM0DIVH=0;
	
	/********* PWM1周期占空比配置20% **********/
	PWM1DUTL=20;
	PWM1DUTH=0;
	PWM1DIVL=99;
	PWM1DIVH=0;
	
	/********* PWM2周期占空比配置10% **********/
	PWM2DUTL=10;
	PWM2DUTH=0;
	PWM2DIVL=99;
	PWM2DIVH=0;
	
	/********* PWM3周期占空比配置20% **********/
	PWM3DUTL=20;
	PWM3DUTH=0;
	PWM3DIVL=99;
	PWM3DIVH=0;
	
	/********* PWM4周期占空比配置10% **********/
	PWM4DUTL=10;
	PWM4DUTH=0;
	PWM4DIVL=99;
	PWM4DIVH=0;
	
	/********* PWM5周期占空比配置20% **********/
	PWM5DUTL=20;
	PWM5DUTH=0;
	PWM5DIVL=99;
	PWM5DIVH=0;
	

	PWMRUN=0xff;	//运行使能

	/****************** UART1 模式1（波特率：9600）******************/
	Uart1Mode1();	//9600
	printf("RUN------\r\n");	
	
//	EINT3 = 1;		//刹车中断使能
//	EINT2 = 1;		//计数中断使能
//    ES0 = 1;	/* UART0 中断开 */
	
	EINT4 = 1;		//掩膜中断使能/UART1
//	EXIP |= 0x01;	//INT4 优先级控制位；中断可以嵌套1层
	PS0 = 1;
	EA = 1;
	P10F = 2;
	P11F = 2;
	P12F = 0x81;
    while(1)
	{	
//		if(PMSCON & 0x1)
//		{
//			P00 = ~P00;
//			printf("PSIF\n");
//			PMSCON &= ~0x1;	
//		}
		
//		if(PMSCON & 0x2)	//读掩模标志
//		{
//			P00 = 1;
//		}
//		else
//		{
//			P00 = 0;
//		}		
	}
    
}