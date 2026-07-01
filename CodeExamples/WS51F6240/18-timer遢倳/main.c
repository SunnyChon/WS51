/*********************************************************
*Copyright (C), 2020-2030, 深圳前海维晟智能技术有限公司
*文件名:	timer唤醒.c
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

static void delay(int i)
{
	long j;
	for(j=0;j<10*i;++j);
}
//=========================================================
/* S1CON串口1控制寄存器 */
#define SM11    0x80            /* 工作模式选择 */
#define IE1     0x40            /* 中断使能， 1 有效 */
#define SM21    0x20            /* 多机通信使能位， 1 有效 */
#define REN1    0x10            /* 串行接收使能位， 1 有效 */
#define TB81    0x08            /* 发送的第 9 位数据 */
#define RB81    0x04            /* 接收的第 9 位数据 */
#define TI1     0x02            /* 发送中断标志， 1 有效，写 0 清除 */
#define RI1     0x01            /* 接收中断标志， 1 有效，写 0 清除 */

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
* 中断服务函数
*****************************************************/
void Timer0_isr (void) interrupt 1  
{
//    P17=~P17; 
    /* set timer0 as mode0 (13-bit) */
    TL0 = (65536-1334) & 0x1F;       //initial timer0 low byte
    TH0 = (65536-1334) >> 5;         //initial timer0 high byte 
	  P11=~P11;
}
void Timer1_isr (void) interrupt 3  
{
	  TL1 = (65536-1334) & 0x1F;              //initial timer0 low byte
    TH1 = (65536-1334) >> 5;         //initial timer0 high byte
	  P11=~P11;
}

void Timer2_isr (void) interrupt 5  
{
    /* 请标志 */
    T2CON &= 0x7f;
	  P11=~P11;
}


#define TF3     0X80		/* 定时器 3 溢出中断  标志 */
void timer3_isr (void) interrupt 7
{ 
    if(TF3 == (T3CON&TF3))	//溢出中断标志
    {
        //淸中断
        T3CON &= ~TF3;
        P11 = ~P11;
    }
}


/*****************************************************
*函数名称：void Timer0Mode(void)
*函数功能：Timer0初始化配置
*入口参数：
*出口参数：
*****************************************************/
void Timer0Mode(void)
{
	//工作模式0：13 位定时器，计满6.144ms(13bit)
    TL0 = (8192-1334) & 0x1F;       //low 5bit
    TH0 = (8192-1334) >> 5;         //high 8bit
    TMOD = 0x00;  //模式0，+0x04计数定时选择，+0x08门控选择
}

/*****************************************************
*函数名称：void Timer1Mode(void)
*函数功能：Timer1初始化配置
*入口参数：
*出口参数：
*****************************************************/
void Timer1Mode(void)
{
	//工作模式0：13 位定时器，计满6.144ms(13bit)
    TL1 = (8192-1334) & 0x1F;       //low 5bit
    TH1 = (8192-1334) >> 5;         //high 8bit
    TMOD = 0x00;  //模式，+0x40计数定时选择，+0x80门控选择
}
/*****************************************************
*函数名称：void Timer2Mode0(void)
*函数功能：重载模式0: 可选 T2EX 边沿触发重载
*入口参数：
*出口参数：
*****************************************************/
void Timer2Mode0(void)
{
	/* 定时器2：重载模式0 */
	//（重载模式A）只有计溢出才能触发重载,计满4.096ms(16bit)
	//（重载模式A1）T2EX 边沿和计溢出时将触发重载,计满4.096ms(16bit)
    T2CH = 0x0;
    T2CL = 0x0;
    TL2 = T2CL;
    TH2 = T2CH;
    
    T2MOD = 0+0x80;//重载模式0,开中断使能,+0x4/T2边沿选择,+0x08/T2EX边沿选择
    T2CON = 0x04;//启动模块,+0x08/T2EX使能,+0x02/计数定时选择,+0x1/抓取功能, 	
}
/*****************************************************
*函数名称：void Timer3OverloadMode0(void)
*函数功能：定时器3模式0：自动重载模式
*入口参数：
*出口参数：
*****************************************************/
void Timer3OverloadMode0(void)
{
	/* 定时器3模式2：重载模式 */	
	TL3 = 0;
	TH3 = 0;
	T3RL = 0;	//重载值  ---测试  ok
	T3RH = 0;	
					
	T3MOD = 0x00+0x80+0x40+0x04;	
	//T3EX重载模式, /开中断使能ok,/T3EX触发中断使能,+0x20/抓取比较中断使能,
	///T3EX边沿选择, +0x02/T3I边沿选择, +0x01/时钟输出使能
	T3CON = 0+0x04;	
	//+0x00,+0x08,+0x10,+0x18/时钟源选择ok, /启动模块, +0x02/抓取功能使能, +0x01/抓取|比较选择
}
/*****************************************************
*函数名称：void Uart1Mode0(void)
*函数功能：9600波特率
*入口参数：
*出口参数：
*****************************************************/
void Uart1Mode0(void)
{
	S1CON  = 0x80; 
	S1RELL = 972;
	S1RELH = 972>>8;
}
/******************************************************************
说明：打印结果为 IDLFL=0,IDLFH=?,STPF=0
*******************************************************************/
void main()
{
    
     SCCON = 0x00;//HRC
	 HRCON |= 0x80;
	
	
	    /*********************管脚配置 *********************/
	   P10F=2;
	   P11F=2;
	   P12F=2;   
	   P02F = 6;//UART1_RX
	   P16F = 6;//UART1_TX
	
		/********************** 串口选择*********************/
  	 Uart1Mode0();
     printf("RUN------\r\n");
	
    /********************* Timer0配置函数************************/
//	  Timer0Mode();
//    ET0 = 1;	//允许中断
//    TR0 = 1;	//开始运行//timer0 start running 
	
    /********************* Timer1配置函数************************/  
//	  Timer1Mode();
//    ET1 = 1;	//允许中断
//    TR1 = 1;	//开始运行//timer0 start running 
	
    /********************* Timer2配置函数************************/  
//	  Timer2Mode0();
//    EINT2 = 1;	/* 用于 IIC/Timer2/PWM/EP0 中断 */
	
    /********************* Timer3配置函数************************/  
	   Timer3OverloadMode0();
	 EINT4 = 1;	/* INT4 使能控制位，用于 UART1/Timer3/EP2 中断 */	

  while(1)
    {	
		T2CON &= 0x7f;
		TF0 = 0;
		TF1 = 0;
		T3CON &= ~TF3;	//清标志
		
		if((IDLFL == 0) && (IDLFH == 0))
//		if(STPF == 0)
        {
            P12=~P12;
			_nop_();
			_nop_();
            P12=~P12;
			printf("sleep\r\n");

			HRCON &= 0x7f;
			LRCON &= 0x7f;			
			MECON |= 0X80;	//IDLE/STOP 模式下，Flash 进入睡眠模式
			
			/*************** 芯片进入休眠 **************/
			PCON |= 1;//idle
//        PCON |= 0X02;    //芯片进入 STOP 模式
			_nop_();
			_nop_();
			_nop_();
			_nop_();
			//等待唤醒
			printf("IDLFL=%bx,IDLFH=%bx,STPF=%bx\r\n",IDLFL,IDLFH,STPF);
			
        }
		
    }
}

    
 
    
   
    




