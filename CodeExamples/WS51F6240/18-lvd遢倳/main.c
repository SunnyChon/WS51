
/*********************************************************
*Copyright (C), 2020-2030, 深圳前海维晟智能技术有限公司
*文件名:	lvd唤醒.c
*作  者:	
*版  本:	V1.00
*日  期:	20200418
*描  述:	
*备  注:     
**********************************************************/
#include "WS51F6240.h"
#include <stdio.h>
#include "intrins.h"

unsigned int i;

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

static void delay_10ms(void)
{
	int j;
	for(j=0;j<17700;++j);
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
*函数名称：void init_lvd(void)
*函数功能：
*入口参数：
*出口参数：
*****************************************************/
void init_lvd(void)
{
	LVDCON = 0x48; 		//低压时产生中断, 低压阈值设置3.0V
	
	//LVDCON = 0x80; 		//低压时产生复位, 低压阈值设置1.8V
	
//	LVDCON = 0xC0; 		//低压时产生中断不产生中断和复位, 低压阈值设置1.8V
}

/*****************************************************
* 中断服务函数
*****************************************************/
void lvd_isr() interrupt 6 
{
	if((LVDCON&0x01) == 0x01)
	{
//		LVDCON  &= 0xFE;
		// todo...
		P11 = ~P11;
	}
}


/******************************************************************
说明：打印结果为 IDLFL=0,IDLFH=40,STPF=8
*******************************************************************/
void main()
{
	  //系统时钟配置
    SCCON = 0x00;//HRC
	HRCON |= 0x80;
	
	  /*********************串口选择******************/
    Uart0Mode1();	
    printf("RUN------\r\n");
	 
    /****************** 管脚配置 ********************/
	  P06F = 6;	//TX
	  P10F = 2; 
	  P11F = 2; 
	  P00F = 2;

    /***************** lvd初始化配置 *****************/
	  init_lvd();
	  IE = 0xC0;			//使能LVD中断开	

	while(1)
	{
		delay_1ms;
		LVDCON  &= 0xFE;
		if((IDLFL == 0) && (IDLFH == 0))
//		if(STPF == 0)
        {
			printf("sleep\r\n");
            P10=~P10;
			_nop_();
			_nop_();
            P10=~P10;
			
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


