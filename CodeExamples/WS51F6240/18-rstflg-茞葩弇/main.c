/*********************************************************
*Copyright (C), 2020-2030, 深圳前海维晟智能技术有限公司
*文件名:	软硬复位标志.c
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
//-----------------------------------------------
static void delay(int i)
{
	long j;
	for(j=0;j<10*i;++j);
}

//-----------------------------------------------
void main()
{
   
	  SCCON = 0x00;//HRC
	  HRCON |= 0x80;
	
	  /*************** 管脚配置 ****************/	  	
		P11F = 0x81;	//上拉10K，输入
		P02F = 6;			//UART1_RX
		P16F = 6;			//UART1_TX

	
    /*************** 串口选择****************/	
		Uart1Mode1();	
		printf("RUN------\r\n");
	
		/*************** 打印复位寄存器标志 ****************/
		printf("rstflg=%bx\r\n",RSTFLG); //刚上电rstflg打印0x05
		RSTFLG = 0XF8;                    
	
    while(1)
    {	
				/*************** 软件复位测试 **************/
				if(P11 == 0)
				{
					delay(137);
					if(P11 == 0)
					{
						while(P11==0);
						//软复位
						//MECON,默认flash启动				
							PCON |= 0x20;                 //P11按下软复位rstflg打印0x01
					}																	//   按下复位键rstflg打印0x02
				}
    }
}