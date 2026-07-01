/*********************************************************
*Copyright (C), 2020-2030, 深圳前海维晟智能技术有限公司
*文件名:	PWM唤醒.c
*作  者:	
*版  本:	
*日  期:	
*描  述:	
*备  注:     
**********************************************************/
#include "WS51F6240.h"
#include "intrins.h"
#include <stdio.h>

static void delay_1ms(void)
{
	int j;
	for(j=0;j<1700;++j);
}

void UART0_write(signed char dat)
{
    S0BUF = dat;            //Send data to UART buffer
    while(!TI0);
    TI0 = 0;
}

///重定向c库函数printf到串口，重定向后可使用printf函数
char putchar(char ch)
{
    /* 发送一个字节数据到串口 */
    UART0_write((signed char) ch);
        
    return ch;
}


/*****************************************************
*函数名称：void Uart0Mode1(void)
*函数功能：9600波特率
*入口参数：
*出口参数：
*****************************************************/
void Uart0Mode1(void)
{
    /*************** UART0 模式1（波特率：9600）****************/
    SM00 = 0;
    SM10 = 1;
    REN0 = 0;    //串行接收使能位
    RI0 = 0;     //接收中断标志
    TI0 = 0;     //发送中断标志
    
	//TIMER2 作为uart0的波特率时钟源
    TR2 = 0;
    T2MOD = 0x00;/* 定时2中断不使能，不分频 */
    T2CL = 65536 - 52;
    T2CH = 65536 - 52 >> 8;
    TL2 = T2CL;
    TH2 = T2CH;
    TR2 = 1;    //启动定时器2
    RCLK = 1;
    TCLK = 1;	
}


/*****************************************************
* 中断服务函数
*****************************************************/
void pwm_isr (void) interrupt 5  
{
	P12 = ~P12;
	PWMFLG0 = 0;
}

//=============================== PWM配置寄存器 ================================
// 寄存器 PWMnCFG(n=0,2,4)		
#define PWM_OP	0x80	//bit7：PWMn 计数器计数到 0 中断使能
#define PWM_ON	0x40 	//bit6：中心对齐模式下，PWMn 计数器计数到最大值中断使能。
#define PWM_OM	0x20 	//bit5：（0：边沿对齐； 1：中心对齐）
#define PWM_SN	0x10 	//bit4：
				
#define PWM_CKS	0 		//bit2-0：时钟源选择
							        //0系统时钟
							        //1---HRC
							        //2---LRC
							        //3---LOSC
							        //4---MRC
							        //5---HOSC
											//其他保留

/**************************************************************
说明：打印结果为 IDLFL=20,IDLFH=0,STPF=0
***************************************************************/
void main()
{
    int i;
	
    SCCON = 0x00;//HRC
	HRCON |= 0X80;
	LRCON |= 0x80;
    delay_1ms();	
	
	
	 /***********************管脚配置*********************/
	  P06F = 6;	//TX
	  P11F = 0x02;	//休眠翻转
	  P12F = 0x02;	//中断翻转IO
	   
    /***********************串口的选择*********************/
    Uart0Mode1();	//
    printf("RUN------\r\n");
	
	
  //============================ PWM 管脚选择 ==================================

	PWM0PS = 0x08;      //选择IO口P00
	PWM1PS = 0x09;      //选择IO口P01
	PWM2PS = 0x0a;      //选择IO口P02
	PWM3PS = 0x0b;      //选择IO口P03
	PWM4PS = 0x0c;      //选择IO口P04
	PWM5PS = 0x0d;      //选择IO口P05
	PWM6PS = 0x0e;      //选择IO口P06
	PWM7PS = 0x0f;      //选择IO口P07
	
//=============================== PWM配置寄存器 ================================LRC: 32768Hz;
	/*	
	寄存器 PWMnCFG(n=0,2,4)		+PWM_OP	0x80	bit7：PWM0/2/4/6 输出极性选择，为 1 时输出取反
								+PWM_ON	0x40 	bit6：PWM1/3/5/7 输出极性选择，为 1 时输出取反
								+PWM_OM	0x20 	bit5：互补 PWM 模式选择，为 1 时 PWMn 与 PWM(n+1)的波形互换后输出。
								+PWM_SN	0x10 	bit4：
												
								+PWM_CKS	1 	bit2-0：时钟源选择：0系统时钟
		**/
	/****************** PWM0/1组 ********************/
	PWM0CFG=PWM_CKS+PWM_OP;			//独立输出
//	PWM0CFG=PWM_CKS+PWM_SN;		//互补输出

	/****************** PWM2/3组 ********************/
	PWM2CFG=PWM_CKS+PWM_OP;			//独立输出
//	PWM2CFG=PWM_CKS+PWM_SN;		//互补输出

	/****************** PWM4/5组 ********************/
	PWM4CFG=PWM_CKS+PWM_OP;			//独立输出
//	PWM4CFG=PWM_CKS+PWM_SN;		//互补输出

	/****************** PWM6/7组 ********************/
	PWM6CFG=PWM_CKS+PWM_OP;			//独立输出
//	PWM6CFG=PWM_CKS+PWM_SN;		//互补输出
	
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
	
	/********* PWM6周期占空比配置70% **********/
	PWM6DUTL=70;
	PWM6DUTH=0;
	PWM6DIVL=99;
	PWM6DIVH=0;	
	/********* PWM7周期占空比配置80% **********/
	PWM7DUTL=80;
	PWM7DUTH=0;
	PWM7DIVL=99;
	PWM7DIVH=0;
	
	PWMRUN=0xff;
	IE=0XA0;

    while(1)
    {	
		PWMFLG0 = 0;
		if((IDLFL == 0) && (IDLFH == 0))
//		if(STPF == 0)
        {
			printf("sleep\r\n");
            P11=~P11;
			_nop_();
			_nop_();
            P11=~P11;
			
			HRCON &= 0x7f;
			LRCON &= 0x7f;			
			MECON |= 0X80;	//IDLE/STOP 模式下，Flash 进入睡眠模式
			
			/*************** 芯片进入休眠 **************/
            PCON = 0X01;    //芯片进入 IDLE 模式
//            PCON = 0X02;    //芯片进入 STOP 模式
			_nop_();
			_nop_();
			_nop_();
			_nop_();
			//等待唤醒
			printf("IDLFL=%bx,IDLFH=%bx,STPF=%bx\r\n",IDLFL,IDLFH,STPF);
			
        }
		
    }
}

    
 
    
   
    




