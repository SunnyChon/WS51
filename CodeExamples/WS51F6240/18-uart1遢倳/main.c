/*********************************************************
*Copyright (C), 2020-2030, 深圳前海维晟智能技术有限公司
*文件名:	uart1唤醒.c
*作  者:	
*版  本:	
*日  期:	
*描  述:	
*备  注:     
**********************************************************/
#include "WS51F6240.h"
#include "intrins.h"
#include <stdio.h>

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
/*****************************************************
*函数名称：void Uart1Mode0(void)
*函数功能：9600波特率
*入口参数：
*出口参数：
*****************************************************/
void Uart1Mode0(void)
{
	S1CON  = 0x80+0x10+0x40; 
	S1RELL = 972;
	S1RELH = 972>>8;
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
* 中断服务函数
*****************************************************/
void Uart1_Isr() interrupt 7
{
    if(RI1 == (S1CON&RI1))     //如果接收到计算机发的数据
    {
        S1CON &= ~RI1;     //清除标志位
		P11 = ~P11;
    }
}
/**************************************************************************
说明：UART0 模式1，芯片进入idle模式，可通过RX唤醒
			打印结果为 IDLFL=0,IDLFH=1,STPF=0
**************************************************************************/
void main()
{
    int i;
    SCCON = 0x00;//HRC
	HRCON |= 0X80;
		
	 /***********************管脚配置*********************/
	  P02F = 6;			//UART1_RX
	  P16F = 6;			//UART1_TX
	  P10F = 0x02;  //推挽输出，翻转IO
	  P11F = 0x02;  //推挽输出，中断翻转IO
	  P12F = 0x02;  //推挽输出，进入休眠IO翻转
	
	/********************** 串口选择*********************/
  	Uart1Mode0();
    printf("RUN------\r\n");
	EA = 1;
	/*********************** 关掉外设 ***********************/
		I2CCON = 0x00;
		PWMRUN=0;
		WDTCON = 0x00; 
    WKTCON = 0x00;	//WKT--off
    LVDCON = 0x00;	//LVD--off
    PWCON=0x00;     //LDO处于小功耗模式0
  while(1)
    {			
		i=20;
        while(i--)
        {
            P10=~P10;
        }		
		S1CON &= ~RI1;     //清除标志位
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
			PCON |= 1;		//芯片进入 idle 模式
//            PCON |= 0X02;    //芯片进入 STOP 模式
			_nop_();
			_nop_();
			_nop_();
			_nop_();
			//等待唤醒
			printf("IDLFL=%bx,IDLFH=%bx,STPF=%bx\r\n",IDLFL,IDLFH,STPF);
        }
		
    }
}

    
 
    
   
    




