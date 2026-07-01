#include "WS51F6240.h"
#include <stdio.h>

//I2CFLG标志位
#define BUSIDLE 	0x80
#define RXNAK 		0x40
#define IF_LSTARB 0x20
#define IF_RXSTA 	0x10
#define IF_RXSTP 	0x08
#define IF_TXDAT 	0x04
#define IF_RXDAT 	0x02
#define IF_RXADR 	0x01
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
unsigned char dat0;
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
    REN0 = 1; 	//串行接收使能位
    RI0 = 0;  	//接收中断标志
    TI0 = 0;  	//发送中断标志
//	
//    /* 默认定时器1作为时钟源(配置位8Bit自动重载模式不开中断程序) */
//    /* TL1 作为 8 位定时器/计数器， TH1 作为自动重载寄存器 */
//    TR1 = 0;    //先停T1
//    TMOD = 0x20;                // 定时器，时钟为系统时钟 12 分频
//    TH1 = 256-4;//波特率10417
//    TR1 = 1;	//开始运行//timer1 start running  	
    
	//TIMER2 作为uart0的波特率时钟源 配置波特率为9600
    TR2 = 0;
    T2MOD = 0x00;/* 定时2中断不使能，不分频 */
    T2CL = 65536 - 52;
    T2CH = 65536 - 52 >> 8;//波特率：9600
    TL2 = T2CL;
    TH2 = T2CH;
    TR2 = 1;    //启动定时器2
    RCLK = 1;   //UART0在模式1和3时使用定时器1/2作为接收波特率时钟
    TCLK = 1;		//UART0在模式1和3时使用定时器1/2作为接收波特率时钟
}
/*****************************************************
* 中断服务函数
*****************************************************/
void Uart_Isr() interrupt 4
{
    if(RI0 == 1)     //如果接收到计算机发的数据
    {
        RI0 = 0;     //清除标志位
        dat0 = S0BUF;  
    }		
}
static void delay_us(int i)
{
	long j;
    while(i--)
        j++;
}
static void delay(int i)
{
		long j;
		for(j=0;j<10*i;++j);
}
#define SLAVE_SEND_NUM    	 10
#define SLAVE_RECEIVE_NUM    10//最大接收缓存
uint8_t reveice_cnt=0,rx_flag=0,send_cnt=0, datS[SLAVE_SEND_NUM];//17 = {"0123456789ABCDEF"}

unsigned char datR[SLAVE_RECEIVE_NUM];
void i2c_trdata(void) interrupt 5
{
    if(IF_RXADR == (I2CFLG&IF_RXADR))   //adr
    {
        if(I2CRXD&0x01 == 0x01) //host----read
        {
			send_cnt = 0;
			I2CTXD = datS[send_cnt];    //0~SEND_NUM-1
			send_cnt++;
        }
		reveice_cnt = 0;	//清空接收数据计数
        I2CFLG &= ~IF_RXADR;    //
    }
     
    else if(IF_RXDAT == (I2CFLG&IF_RXDAT))   //rx_flag   slave-----RX
    {
//        delay_us(3);
		if(reveice_cnt>=SLAVE_RECEIVE_NUM)    //接收数据超过缓存
        {
            reveice_cnt=0;
        }
		datR[reveice_cnt] = I2CRXD;
		reveice_cnt++;
        I2CFLG &= ~IF_RXDAT;
    }
    
    else if(IF_TXDAT == (I2CFLG&IF_TXDAT))   //tx_flag   slave-----TX
    {
        I2CTXD = datS[send_cnt];    //0~SEND_NUM-1
		if(++send_cnt>=SLAVE_SEND_NUM)    //实际发送SEND_NUM+1
        {
            send_cnt=0;
        }
        I2CFLG &= ~IF_TXDAT;
    }	
    else if(IF_RXSTP == (I2CFLG&IF_RXSTP))   //stop
		{
			if(reveice_cnt!=0)
			rx_flag = 1;
			I2CFLG &= ~IF_RXSTP;
		}
	
}
/*****************************************************
*函数名称：void I2CSlaveCfg(void)
*函数功能：IIC从机配置
*入口参数：
*出口参数：
*****************************************************/
void I2CSlaveCfg(void)
{
//    I2CADR = 0x80;  //识别广播地址0
		I2CADR = 0xA0>>1;  //从机地址 0xA0
	
//		I2CFG0 = 0x80+0x7e;	//从机地址接收掩膜功能 111 1111
    
    I2CCON = 0x00;//Fi2c_CLK====== 16M/8
//    I2CFG1 = 0x00;  //Fi2c/(I2CFG1<6:0>+8)
    
    I2CFG0  |= (0x1<<7);//HOSE  on
//    I2CFG0  &= ~(0x1<<7);//HOSE  not
    
//    I2CCON  &= ~(0x1<<7);    //mode en
    I2CCON  |= (0x1<<7);    //mode en
    I2CCON  |= (0x1<<6);	//Int en

    I2CTXD  = 0x0;          //0x00
//    I2CCON  |= (0x1<<5);  //START INT EN
    I2CCON  |= (0x1<<4);  //STOP INT EN
}
//-----------------------------------------------
void main()
{
    int i;
    unsigned char adc_val = 0,tk_val = 0,j=0;
    
    SCCON  = 0x00;//HRC
		HRCON |= 0x80;
    i=50;while(i--)delay(200);
    
	/****************   管脚配置    ***************/
    P13F = 0;//
    P14F = 0;//
    P02F = 0x25;//IIC SCL
    P16F = 0x25;//IIC SDA
	
 
    /****** UART0 模式1（波特率：9600 可调）**************/
    P07F = 6;//RX
    P06F = 6;//TX
		P10F = 2;
		P11F = 2;
//		P13F = 0x81;
	
	/***************** 从机配置********************/
	I2CSlaveCfg();	//IIC从机配置	
    
    /******** UART0 模式1（波特率：9600）********/
	Uart0Mode1();	//P06--TX
    printf("RUN------\r\n");
		
//	ES0 = 1;	/* UART0 中断开 */
    EINT2 = 1;
    EA = 1; 
		
		for(i=0;i<SLAVE_SEND_NUM;i++)
		{
			datS[i] = i+0x55;//ABCD...
		}
		
		for(i=0;i<SLAVE_RECEIVE_NUM;i++)
		{
			datR[i]=0;	//清数组
		}
			
  while(1)
    {
        if(rx_flag == 1)
        {
            rx_flag = 0; 
			printf("rx：%s", datR);
            printf("\r\n");			
        }
    }
}