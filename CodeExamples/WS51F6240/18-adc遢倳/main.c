/*********************************************************
*Copyright (C), 2020-2030, 深圳前海维晟智能技术有限公司
*文件名:	adc唤醒.c
*作  者:	
*版  本:	
*日  期:	
*描  述:	
*备  注:     
**********************************************************/

#include "WS51F6240.h"
#include <stdio.h>
#include "intrins.h"
unsigned int i ;
unsigned int adc_val = 0;

unsigned char Rx_flag=0,Tx_flag=0;

static void delay(int i)
{
	long j;
	for(j=0;j<10*i;++j);
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
/*****************************************************
*函数名称：void init_adc(void)
*函数功能：
*入口参数：
*出口参数：
*****************************************************/
void init_adc(void)
{
	  ADCON = 0X00 + 0X40;
		ADCFG = 0X73;
		ADCHS = 0X01;

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
/**************************************************************
说明：打印结果为 IDLFL=0,IDLFH=2,STPF=0
***************************************************************/
void main()
{
	
	SCCON = 0x00;//HRC 
    HRCON |= 0x80;
	
	  /***********************管脚配置*********************/
	  P16F = 6;	//TX
	  P10F = 5; //AIN1
	
  	/********************** 串口选择*********************/
  	Uart1Mode0();
    printf("RUN------\r\n");
	
    /********************** adc初始化*********************/
		init_adc();
	
	while(1)
		{
				ADCON |= 0X80; 		
			if((IDLFL == 0) && (IDLFH == 0))
//		if(STPF == 0)
        {
			printf("sleep\r\n");
			_nop_();
			_nop_();
			
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
					ADCON &=0XFE;
			}
		}
	}