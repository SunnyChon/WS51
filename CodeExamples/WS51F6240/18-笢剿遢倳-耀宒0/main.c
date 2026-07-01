/*********************************************************
*Copyright (C), 2020-2030, 深圳前海维晟智能技术有限公司
*文件名:	中断模式0唤醒.c
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
* 中断服务函数
*****************************************************/
void IT0_isr() interrupt 0
{
	P13=~P13;
}

void IT1_isr() interrupt 2
{
	P13=~P13;
}


void EP0_isr() interrupt 5
{
    if((EPIF&0x01) == 0x01)
    {
        EPIF &= 0xFE;
		P13=~P13;
    }
}

void EP1_isr() interrupt 6
{
    if((EPIF&0x02) == 0x02)
    {
        EPIF &= 0xFD;
		P13=~P13;
    }
}

void EP2_isr() interrupt 7
{
    if((EPIF&0x04) == 0x04)
    {
        EPIF &= 0xFB;
		P13=~P13;
    }
}

void EP3_isr() interrupt 8
{
    if((EPIF&0x08) == 0x08)
    {
        EPIF &= 0xF7;
		P13=~P13;
    }
}


/************ 中断管脚配置值 ***********/
#define IT_PIN_P00  0X00
#define IT_PIN_P01  0X01

#define IT_PIN_P10  0X08
#define IT_PIN_P11  0X09
#define IT_PIN_P12  0X0A
#define IT_PIN_P13  0X0b
#define IT_PIN_P14  0X0c
#define IT_PIN_P15  0X0d
#define IT_PIN_P16  0X0e
#define IT_PIN_P17  0X0f

#define IT_PIN_P30  0X18
#define IT_PIN_P31  0X19
#define IT_PIN_P32  0X1A
#define IT_PIN_P33  0X1b
#define IT_PIN_P34  0X1c
#define IT_PIN_P35  0X1D
#define IT_PIN_P36  0X1e
#define IT_PIN_P37  0X1f

#define INT_PIN IT_PIN_P11 //P00-P01;P10-P17;P30-P37


/*****************************************************
*函数名称：void Int0SetMode0(void)
*函数功能：INT0 中断模式0
*入口参数：
*出口参数：
*****************************************************/
void Int0SetMode0(void)
{
	/*********** INT0 中断模式0 **********/
//	IT0CON=0X00|INT_PIN;    //00 Pin---下降沿 ---低电平
//	IT0CON=0X40|INT_PIN;    //10 Pin---上沿   ---高电平
//	IT0CON=0X80|INT_PIN;    //01 Pin---双沿   ---保留（低电平）、
	IT0CON=0XC0|INT_PIN;    //01 Pin---双沿	  ---保留（低电平）、
//	TCON=3;//使能外部中断 0 在输入管脚下降沿时触发
	TCON=2;//使能外部中断 0 在输入管脚低电平时触发
}

/*****************************************************
*函数名称：void Int1SetMode0(void)
*函数功能：INT1 中断模式0
*入口参数：
*出口参数：
*****************************************************/
void Int1SetMode0(void)
{
	/*********** INT1 中断模式0 **********/
//	IT1CON=0X00|INT_PIN;    //00 Pin---下降沿---
//	IT1CON=0X40|INT_PIN;    //10 Pin---上沿  ---
//	IT1CON=0X80|INT_PIN;    //01 Pin---保留（低电平）、---双沿---
	IT1CON=0XC0|INT_PIN;    //01 Pin---保留（低电平）、---双沿---
//	TCON=0x0c;//外部中断 1 在输入管脚下降沿时触发
    TCON=0x08;//外部中断 1 在输入管脚低电平时触发
}


/*****************************************************
*函数名称：void Int2SetMode0(void)
*函数功能：INT2 中断模式0
*入口参数：
*出口参数：
*****************************************************/
void Int2SetMode0(void)
{
	/*********** INT2(EP0) 中断模式0 **********/
	EP0CON=0X00|INT_PIN;    //00 Pin---下降沿---
//	EP0CON=0X40|INT_PIN;    //10 Pin---上沿  ---
//	EP0CON=0X80|INT_PIN;    //01 Pin---双沿---
//	EP0CON=0XC0|INT_PIN;    //01 Pin---双沿---
}

/*****************************************************
*函数名称：void Int3SetMode0(void)
*函数功能：INT3 中断模式0
*入口参数：
*出口参数：
*****************************************************/
void Int3SetMode0(void)
{
	/*********** INT3(EP1) 中断模式0 **********/
	EP1CON=0X00|INT_PIN;    //00 Pin---下降沿---
//	EP1CON=0X40|INT_PIN;    //10 Pin---上沿  ---
//	EP1CON=0X80|INT_PIN;    //01 Pin---双沿---
//	EP1CON=0XC0|INT_PIN;    //01 Pin---双沿---
}

/*****************************************************
*函数名称：void Int4SetMode0(void)
*函数功能：INT4 中断模式0
*入口参数：
*出口参数：
*****************************************************/
void Int4SetMode0(void)
{
	/*********** INT4(EP2) 中断模式0 **********/
	EP2CON=0X00|INT_PIN;    //00 Pin---下降沿---
//	EP2CON=0X40|INT_PIN;    //10 Pin---上沿  ---
//	EP2CON=0X80|INT_PIN;    //01 Pin---双沿---
//	EP2CON=0XC0|INT_PIN;    //01 Pin---双沿---
}


/*****************************************************
*函数名称：void Int5SetMode0(void)
*函数功能：INT5 中断模式0
*入口参数：
*出口参数：
*****************************************************/
void Int5SetMode0(void)
{
	/*********** INT5(EP3) 中断模式0 **********/
	EP3CON=0X00|INT_PIN;    //00 Pin---下降沿---
//	EP3CON=0X40|INT_PIN;    //10 Pin---上沿  ---
//	EP3CON=0X80|INT_PIN;    //01 Pin---双沿---
//	EP3CON=0XC0|INT_PIN;    //01 Pin---双沿---
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

/**************************************************************
功能说明：
1、测试外部中断012345（模式0）
2、外部中断引脚和触发方式通过寄存器 (IT0CON/IT1CON/EPnCON) 选择
3、P10推挽输出，翻转电平；
4、接线：P10接外部中断引脚触发唤醒
***************************************************************/
void main()
{
    int i;  
    SCCON = 0x00;//HRC
	HRCON |= 0X80;
	LRCON |= 0X80;
	
 	  /*************************管脚配置**********************/
	  P11F = 0X81;
	  P10F = 0X02;		//推挽输出，翻转IO
	  P12F = 0X02;
	  P13F = 0X02;		//推挽输出，中断翻转IO
	  P06F = 6;	      //TX
	
    
    /************************* 串口选择**********************/
    Uart0Mode1();	//
    printf("RUN------\r\n");
	
	  /************************* 模式选择**********************/
    	
	  /********** 中断0模式0 **********/
	  Int0SetMode0();
	  /********** 中断1模式0 **********/
//	Int1SetMode0();
	  /********** 中断2(EP0)模式0 **********/
//	Int2SetMode0();
	  /********** 中断3(EP1)模式0 **********/
//	Int3SetMode0();
	  /********** 中断4(EP2)模式0 **********/
//	Int4SetMode0();
	  /********** 中断5(EP3)模式0 **********/
//	Int5SetMode0();
	  /*********** EP0~EP3 中断使能 ***********/
  EPIE = 0X0f;	//EP3~EP0: 3~0
		
	
	  EINT5 = 1;		/* EP3 中断使能控制位，用于 ADC/SPI/SCM/EP3 中断 */
	  EINT4 = 1;		/* EP2 使能控制位，用于 UART1/Timer3/EP2 中断 */
	  EINT3 = 1;		/* EP1 用于 Touch Key/WDT/LVD/WKT/EP1 中断 */
	  EINT2 = 1;		/* EP0 用于 IIC/Timer2/PWM/EP0 中断 */ 			
	  EINT1 = 1;		/* INT1 中断 1 使能控制位（中断 1 用于外部中断 1） */
	  EINT0 = 1;		/* INT0 使能控制位（中断 0 用于外部中断 0） */
	  IE|=0x80;//总中断使能


while(1)
    {	
		/*********************** 外部中断唤醒测试 ***********************/
		if((IDLFL == 0) && (IDLFH == 0))
//		if(STPF == 0)
        {
			printf("sleep\r\n");
            P12=~P12;
			_nop_();
			_nop_();
            P12=~P12;
			
			HRCON &= 0x7f;
			LRCON &= 0x7f;			
			MECON |= 0X80;	//IDLE/STOP 模式下，Flash 进入睡眠模式

			
			/*************** 芯片进入休眠 **************/
          PCON = 0X01;    //芯片进入 IDLE 模式
//          PCON = 0X02;    //芯片进入 STOP 模式
			_nop_();
			_nop_();
			_nop_();
			_nop_();
			_nop_();
			//等待唤醒
            printf("IDLFL=%bx,IDLFH=%bx,STPF=%bx\r\n",IDLFL,IDLFH,STPF);	
        }
    }
}

    
 
    
   
    




