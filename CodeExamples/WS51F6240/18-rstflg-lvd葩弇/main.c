/*********************************************************
*Copyright (C), 2020-2030, 深圳前海维晟智能技术有限公司
*文件名:	lvd复位标志.c
*作  者:	
*版  本:	
*日  期:	
*描  述:	
*备  注:     
**********************************************************/

#include "WS51F6240.h"
#include "intrins.h"
#include <stdio.h>

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
	S1CON = 0x80;
	S1RELL = 972;
	S1RELH = 972>>8;	
}

void main()
{
	  SCCON = 0x00;//HRC
	  HRCON |= 0x80;
  
    /*************** 管脚配置 ****************/	
	  P02F = 6;//UART1_RX
	  P16F = 6;//UART1_TX
	
	 /*************** 串口选择 ****************/
	  Uart1Mode1();	
	  printf("RUN------\r\n");

   /*************** 打印复位寄存器标志 ****************/
	  printf("rstflg=%bx\r\n",RSTFLG);  //rstflg打印0x10
	  LVDCON = 0X88; 										//打开LVD复位功能
	  RSTFLG &= 0X00;										//清标志
 while(1);
 }










