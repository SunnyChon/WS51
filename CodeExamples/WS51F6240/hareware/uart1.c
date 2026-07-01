/*********************************************************
*Copyright (C), 2020-2030, 深圳前海维晟智能技术有限公司
*文件名:	uart1.c
*作  者:	
*版  本:
*日  期:	
*描  述:	
*备  注:     
**********************************************************/
#include "WS51F6240.h"	
#include <stdio.h>
#include "uart1.h"

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

unsigned char dat0;
unsigned char Rx_flag=0,Tx_flag=0;

void Uart1_Isr() interrupt 7
{
    if(RI1 == (S1CON&RI1))     //如果接收到计算机发的数据
    {
        S1CON &= ~RI1;     //清除标志位
		dat0 = S1BUF;
		Rx_flag = 1;
    }
    if(TI1 == (S1CON&TI1))     
    {
        S1CON &= ~TI1;     //清除标志位      
        Tx_flag = 1;
    }
}

void UART1_write(signed char dat)
{
    Tx_flag=0;
    S1BUF = dat;            //Send data to UART buffer
    while(!Tx_flag);
}

///重定向c库函数printf到串口，重定向后可使用printf函数
char putchar(char ch)
{
    /* 发送一个字节数据到串口 */
    UART1_write((signed char) ch);
        
    return ch;
}

//-----------------------------------------------
void Uart1Mode1(void)
{ 
	S1CON = SM11+IE1+REN1;	
	///8位异步模式(1), /中断使能, +SM21/多机通信使能位, /串行接收使能位, +TB81/第9位数据, +RB81/

	S1RELL = 972;
	S1RELH = 972>>8;	//9600
}

    
 
    
   
    




