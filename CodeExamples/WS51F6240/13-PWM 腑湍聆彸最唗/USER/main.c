/*********************************************************
*Copyright (C), 2020-2030, 深圳前海维晟智能技术有限公司
*文件名:	pwm.c
*作  者:	
*版  本:	
*日  期:	
*描  述:	
*备  注:     
**********************************************************/
#include "WS51F6240.h"	
#include <stdio.h>
#include "Init.h"
#include "PWM.h"
#include "INT.h"
#include "CODE.h"

#define Reverse_io_Pin(pin)     pin = ~pin

#define KEY0 P02
#define KEY1 P03
#define KEY2 P04
#define KEY0_PRES 	1	//KEY0按下
#define KEY1_PRES	  2	//KEY1按下
#define KEY2_PRES	  3	//KEY2按下
rgb_param rgb_s_param;

unsigned char dat0;
unsigned char Rx_flag=0;
unsigned char color = 0;
unsigned char over = 0;
u16 time_ms;
static void delay_1ms(void)
{
	int j;
	for(j=0;j<1700;++j);
}
void delay_ms(u16 nms)//1.5ms
{
	time_ms = nms;
	TR1 = 1;
	while(time_ms);
	TR1 = 0;
}
///重定向c库函数printf到串口，重定向后可使用printf函数
char putchar(int8_t ch)
{
    /* 发送一个字节数据到串口 */
    UART0_write((int8_t) ch);        
    return ch;
}
void Time1_ISR() interrupt 3
{
	 time_ms--;
	 TH1 = (65536-2000)/256;//1.5ms
	 TL1 = (65536-2000)%256;
}
void Uart_ISR() interrupt 4
{
    if(RI0 == 1)     //如果接收到计算机发的数据
    {
        RI0 = 0;     //清除标志位
        dat0 = S0BUF;  
        Rx_flag = 1;
    }
		
}
void INT2_ISR(void) interrupt 5 //I2C/Timer2/PWM/LED/EP0
{

//	 if((EPIF&0x01) == 0x01)
//   {
//      EPIF &= 0xFE;			
//   }
	if(PWMFLG1&0x20)  //PWM6
	{			
			PWMFLG1 =0;
			over = 1;
			Reverse_io_Pin(P10);
	}
	if(PWMFLG1&0x80)//PWM7
	{
			PWMFLG1 &= ~0x80;
			over = 1;
			Reverse_io_Pin(P11);
	}
}
//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//0，没有任何按键按下
//1，KEY0按下
//2，KEY1按下
//3，KEY2按下 
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&(KEY0==0||KEY1==0||KEY2==0))
	{
		delay_ms(10);//去抖动15ms 
		key_up=0;
		if(KEY0==0)return KEY0_PRES;
		else if(KEY1==0)return KEY1_PRES;
		else if(KEY2==0)return KEY2_PRES;
	}else if(KEY0==1&&KEY1==1&&KEY2==1)key_up=1; 	    
 	return 0;// 无按键按下
}

void RGB_Light(u8 light,u8 Lcolour)
{
    u8 num;
    for(num=0;num<64;num++)
    {
        if(num == light)
        {
            LED0D0 = led_b[Lcolour];//PWM6对应的LED0输出数据
            LED0D1 = led_r[Lcolour];
            LED0D2 = led_g[Lcolour];				
        }
        else
        {
            LED0D0 = led_b[11];//PWM6对应的LED0输出数据
            LED0D1 = led_r[11];
            LED0D2 = led_g[11];
        }
        while(!over);
        over = 0;
    }
}

void main()
{   
    u8 key;
    int num;
    u8 led_sbit;
    u8 lx;
    SCCON = 0x00;//HRC
    HRCON |= 0x80; //HRC使能
	
		/**************************管脚配置**********************/
    P05F = 1;		//EP0
    P04F = 1;		//INT1
    P03F = 1;		//INT0
    P02F = 1;		
    P10F = 2;		//OUTPUT
    P11F = 2;		//OUTPUT
			
    P07F = 6;		//RX
    P06F = 6;		//TX	
		/*************************函数初始化**********************/
    Uart0Mode1_Init();
    PWM_LED_Init();	
    Timer1_Init();
		
		printf("STR---%s\r\n", __TIME__);
		
    EINT2 = 1;//EP0
    EA = 1;
	
    while(1)
    {
        key = KEY_Scan(0);
        if(Rx_flag == 1)
        {
            Rx_flag = 0;
            UART0_write(dat0);
        }	
        if(key == 1)
        {
            lx=0;
            for(num=0;num<64;num++)
            {
                LED0D0 = led_b[color];//PWM6对应的LED0输出数据
                LED0D1 = led_r[color];
                LED0D2 = led_g[color];
                while(!over);
                over = 0;
            }
            color++;
            if(color >= 12)
                color = 0;
            printf("color=%bu\r\n",color);
        }		
        if(key == 2) lx = 1;
        if(lx)
        {
            for(num=0;num<64;num++)
            {
                LED0D0 = led_b[color];//PWM6对应的LED0输出数据
                LED0D1 = led_r[color];
                LED0D2 = led_g[color];
                while(!over);
                over = 0;
            }
            color++;
            if(color >= 12)
                color = 0;
            delay_ms(100);
        }
        if(key == 3)
        {
            lx=0;
            for(led_sbit = 0;led_sbit < 64;led_sbit++)
            {
                RGB_Light(led_sbit,color);
                delay_ms(6);//1.5ms
            }
            color++;
            if(color >= 11)
              color = 0;
        }
    }
}

    
 
    
   
    




