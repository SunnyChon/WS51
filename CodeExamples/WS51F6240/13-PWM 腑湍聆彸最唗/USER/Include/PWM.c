#include "PWM.h"



void PWM_LED_Init(void)
{
//	P02F = 0x03;//IO口复用为PWM模式
	P01F = 0x03;//IO口复用为PWM模式
	
	PWMCLR = 0x00;//写1清零PWM计数器,写0无动作
	PWMUPD = 0x00;//写1载入PWM新的周期和占空比配置值,写0无动作
	PWMFLG0 = 0x00;//PWM计数器计数到0或最大值中断标志
	PWMFLG1 = 0x00;//PWM计数器计数到0或最大值中断标志
	/*PWMnCFG(n=0,2,4)  
	7:PWMnZIE PWMn计数器计数到0中断使能
	6:PWMnPIE 中心对齐模式下，PWMn计数器计数到最大值中断使能。
	5:PWMnMOD PWMn计数模式选择。0:边沿对齐 1:中心对齐
	4:PWMnTOG PWMn输出极性选择，为1时输出反向
	3:PWMnOM  互补PWM模式选择，为1时PWMn与PWM(n+1)的波形互换后输出。
	2-0:PWMn/PWM(n+1)时钟选择
	    000:系统时钟
	    001:LRC时钟32KHz
    	010:HRC时钟16MHz
			011:LOSC时钟32.768KHz
			100:HOSC时钟2-16MHz
			101:MRC时钟1-4MHz
  */
//	PWM0CFG = 0x01;
	/*PWMnCFG(n=1,3,5)
	7:PWMnZIE PWMn计数器计数到0中断使能
	4:PWMnTOG PWMn输出极性选择，为1时输出反向
	0:PWMnSN PWM独立输出使能
		0:PWM(n-1)和PWMn组成互补PWM输出
		1:PWM(n 1)和PWMn独立输出
	*/
//	PWM1CFG = 0x00;
	/*PWMnCFG(n=6,7)
	7:PWMnZIE PWM计数器计数到0中断使能
	6:PWMnLEN LED输出功能使能
	5:PWMnMOD LED输出模式选择 0:：写数据触发模式 1：持续发送模式
	4:PWMnTOG PWM输出极性选择，为1时输出取反
	3:PWMnPOL
		LED输出时有效电平选择
		0：高电平有效
		1：低电平有效
	2-0:PWMnCKS PWM6/7时钟选择
			0/5/6/7:系统时钟
	    001:LRC时钟32KHz
    	010:HRC时钟16MHz
			011:MRC时钟1-4MHz
			100:LOSC时钟32.768KHz
	*/
	PWM6CFG = 0xc0;//计数到0中断使能，LED输出功能使能，0写数据触发模式
//	PWM7CFG = 0xc0;//计数到0中断使能，LED输出功能使能，1持续发送模式
	
	PWM6PS = 0x01;//PWM6输出IO口选择P01
//	PWM7PS = 0x02;//PWM7输出IO口选择P02
	
	PWM6DIVL = 19%256;//PWM周期设置
	PWM6DIVH = 19/256;
	PWM6DUTL = 5%256;//PWM占空比设置
	PWM6DUTH = 5/256;
	
//	PWM7DIVL = 19%256;//PWM周期设置
//	PWM7DIVH = 19/256;
//	PWM7DUTL = 5%256;//PWM占空比设置
//	PWM7DUTH = 5/256;
	
//	LEDAT00 = 0x01;//PWM6对应的LED0输出数据
//	LEDAT01 = 0x02;
//	LEDAT02 = 0x03;
//		
//	LEDAT10= 0x01;//PWM7对应的LED1输出数据
//	LEDAT11 = 0x02;
//	LEDAT12 = 0x03;
	
	LEDCFG = 0xdc;//LED每次输出3字节数，输出数据无等待时间

	PWMRUN = 0x40;//PWM6,PWM7运行使能
	
	EINT2 = 1;//INT2 使能控制位,用于I2C/Timer2/PWM/LED/EP0中断
}
























































