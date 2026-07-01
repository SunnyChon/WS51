/*********************************************************
*Copyright (C), 2020-2030, 深圳前海维晟智能技术有限公司
*文件名:	exint0.c
*作  者:	
*版  本:	
*日  期:	
*描  述:	
*备  注:     
**********************************************************/
#include "WS51F6240.h"

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

/************ 中断管脚配置值 ***********/
#define IT_PIN_P00  0X00
#define IT_PIN_P01  0X01
#define IT_PIN_P02  0X02
#define IT_PIN_P03  0X03
#define IT_PIN_P04  0X04
#define IT_PIN_P05  0X05
#define IT_PIN_P06  0X06
#define IT_PIN_P07  0X07

#define IT_PIN_P10  0X08
#define IT_PIN_P11  0X09
#define IT_PIN_P12  0X0a
#define IT_PIN_P13  0X0b
#define IT_PIN_P14  0X0c
#define IT_PIN_P15  0X0d
#define IT_PIN_P16  0X0e
#define IT_PIN_P17  0X0f

#define IT_PIN_P20  0X10
#define IT_PIN_P21  0X11


#define INT_PIN IT_PIN_P11 //P00-P01;P10-P17;P30-P37


/*****************************************************
* 中断服务函数
*****************************************************/
void IT0_isr() interrupt 0
{
	P12=~P12;
}

void IT1_isr() interrupt 2
{
	P12=~P12;
}


void EP0_isr() interrupt 5
{
    if((EPIF&0x01) == 0x01)
    {
        EPIF &= 0xFE;
		P12=~P12;
    }
}

void EP1_isr() interrupt 6
{
    if((EPIF&0x02) == 0x02)
    {
        EPIF &= 0xFD;
		P12=~P12;
    }
}

void EP2_isr() interrupt 7
{
    if((EPIF&0x04) == 0x04)
    {
        EPIF &= 0xFB;
		P12=~P12;
    }
}

void EP3_isr() interrupt 8
{
    if((EPIF&0x08) == 0x08)
    {
        EPIF &= 0xF7;
		P12=~P12;
    }
}

/*****************************************************
*函数名称：void Int0SetMode0(void)
*函数功能：INT0 中断模式0
*入口参数：
*出口参数：
*****************************************************/
void Int0SetMode0(void)
{
	/*********** INT0 中断模式0 **********/
	IT0CON=0X00|INT_PIN;    //00 Pin---下降沿 ---低电平
//	IT0CON=0X40|INT_PIN;    //10 Pin---上沿   ---高电平
//	IT0CON=0X80|INT_PIN;    //01 Pin---双沿   ---保留（低电平）、
//	IT0CON=0XC0|INT_PIN;    //01 Pin---双沿	  ---保留（低电平）、
	TCON=3;//使能外部中断 0 在输入管脚下降沿时触发
//	TCON=2;//使能外部中断 0 在输入管脚低电平时触发
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
	IT1CON=0X00|INT_PIN;    //00 Pin---下降沿---
//	IT1CON=0X40|INT_PIN;    //10 Pin---上沿  ---
//	IT1CON=0X80|INT_PIN;    //01 Pin---保留（低电平）、---双沿---
//	IT1CON=0XC0|INT_PIN;    //01 Pin---保留（低电平）、---双沿---
	TCON=0x0c;//外部中断 1 在输入管脚下降沿时触发
//	TCON=0x08;//外部中断 1 在输入管脚低电平时触发
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
//	EP3CON=0X80|INT_PIN;    //00 Pin---下降沿---
	EP3CON=0X40|INT_PIN;    //10 Pin---上沿  ---
//	EP3CON=0X80|INT_PIN;    //01 Pin---双沿---
//	EP3CON=0XC0|INT_PIN;    //01 Pin---双沿---
}

/**************************************************************
功能说明：
1、测试外部中断012345（模式0）
2、外部中断引脚和触发方式通过寄存器 (IT0CON/IT1CON/EPnCON) 选择
3、P10推挽输出，翻转电平；
4、接线：P10接外部中断引脚P11
5、结果：看P12翻转
***************************************************************/
void main()
{
    int i;
    SCCON = 0x00;//HRC
		HRCON |= 0X80;		
					 
		P11F = 0x81;   //上拉输入
		P10F = 0x02;	 //推挽输出
		P12F = 0x02;	 //推挽输出

	
	
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
//   EPIE = 0X08;	//EP3~EP0: 3~0
		
		EINT5 = 1;		/* EP3 中断使能控制位，用于 ADC/SPI/SCM/EP3 中断 */
		EINT4 = 1;		/* EP2 使能控制位，用于 UART1/Timer3/EP2 中断 */
		EINT3 = 1;		/* EP1 用于 Touch Key/WDT/LVD/WKT/EP1 中断 */
		EINT2 = 1;		/* EP0 用于 IIC/Timer2/PWM/EP0 中断 */ 			
		EINT1 = 1;		/* INT1 中断 1 使能控制位（中断 1 用于外部中断 1） */
		EINT0 = 1;		/* INT0 使能控制位（中断 0 用于外部中断 0） */
		IE |= 0x80;   //总中断使能

    while(1)
    {		
		//双沿测试 
        P10 = 0;
        P10 = 1; 
        delay(100);
        delay(100);
        delay(100);
        P10 = 0;
        delay(100);
        delay(100);
        delay(100);
        P10 = 1;
        delay(100); 
        delay(100);
        delay(100);       
        P10 = 0;    
        i= 5;while(i--)delay(100);
    }
}
