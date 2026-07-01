
#include "WS51F0030.h"
#include <stdio.h>

unsigned char Rx_flag=0,Tx_flag=0;
void UART0_write(signed char dat)
{
    Tx_flag = 0;
    S0BUF = dat;            //Send data to UART buffer
    while(!Tx_flag);
}

///重定向c库函数printf到串口，重定向后可使用printf函数
char putchar(char ch)
{
    /* 发送一个字节数据到串口 */
    UART0_write((signed char) ch);
        
    return ch;
}

unsigned char dat0;
/*****************************************************
* 中断服务函数
*****************************************************/
void Uart_Isr() interrupt 4
{
    if(RI0 == 1)     
    {
        RI0 = 0;     //清除标志位
        dat0 = S0BUF;  
        Rx_flag = 1;
    }
    if(TI0 == 1)     
    {
        TI0 = 0;     //清除标志位
        Tx_flag = 1;
    }
}

/*****************************************************
*函数名称：void Uart0Mode1(void)
*函数功能：8 位异步模式，波特率：可调(T1/T2)
*入口参数：
*出口参数：
*****************************************************/
void Uart0Mode1(void)
{
    SM00 = 0;
    SM10 = 1;	//模式选择: 模式1
    REN0 = 0; 	//串行接收使能位
    RI0 = 0;  	//接收中断标志
    TI0 = 0;  	//发送中断标志
	
//    /* 默认定时器1作为时钟源(配置位8Bit自动重载模式不开中断程序) */
//    /* TL1 作为 8 位定时器/计数器， TH1 作为自动重载寄存器 */
//    TR1 = 0;    //先停T1
//    TMOD = 0x20;                // 定时器，时钟为系统时钟 12 分频
//    TH1 = 256-4;//波特率10417
//    TR1 = 1;	//开始运行//timer1 start running  	
    
	//TIMER2 作为uart0的波特率时钟源
    TR2 = 0;
    T2MOD = 0x00;/* 定时2中断不使能，不分频 */
    T2CL = 65536 - 52;
    T2CH = 65536 - 52 >> 8;//波特率：9600
    TL2 = T2CL;
    TH2 = T2CH;
    TR2 = 1;    //启动定时器2
    RCLK = 1;
    TCLK = 1;	
}

/*****************************************************
*函数名称：void vcan_sendware(u16 *wareaddr, unsigned int waresize)
*函数功能：虚拟示波器
*入口参数：
*出口参数：
*****************************************************/
void vcan_sendware(u16 *wareaddr, unsigned int waresize)
{
	int i;
	#define CMD_WARE     3
	unsigned char cmdf[2] = {CMD_WARE, ~CMD_WARE};    //yy_ÉãÏñÍ·´®¿Úµ÷ÊÔ Ê¹ÓÃµÄÃüÁî
	unsigned char cmdr[2] = {~CMD_WARE, CMD_WARE};    //yy_ÉãÏñÍ·´®¿Úµ÷ÊÔ Ê¹ÓÃµÄÃüÁî

	for(i=0;i<sizeof(cmdf);++i)
	{UART0_write(*(cmdf+i));//先发送命令
	}
	
	for(i=0;i<waresize;++i)
	{
		UART0_write(*(wareaddr+i));//再发送图像
		UART0_write((*(wareaddr+i))>>8);//再发送图像
	}
	
	for(i=0;i<sizeof(cmdr);++i)
	UART0_write(*(cmdr+i));//发送命令
}

void putBinary(unsigned int number)//将一个int型数据的二进制形式正序，倒叙打印输出
{
    unsigned int value;
    int i;
//    for (i = 31; i >= 0;i--)//正序
//    {
//        value = number >> i & 1;
//        printf("%d", value);
//    }
//    printf("\r\n");
    
    for (i = 12; i >= 0;i--)//正序
    {
        value = number >> i & 1;
        printf("%d", value);
    }
//    printf("\r\n");

//    for (i = 0; i <= 31; i++)//倒叙
//    {
//        value = number >> i & 1;
//        printf("%d", value);
//    }
//    printf("\r\n");
}  
