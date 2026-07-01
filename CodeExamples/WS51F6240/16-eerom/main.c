/*********************************************************
*Copyright (C), 2020-2030, 深圳前海维晟智能技术有限公司
*文件名:	eeprom-test.c
*作  者:	
*版  本:	
*日  期:	
*描  述:	
*备  注:     
**********************************************************/
#include "WS51F6240.h"	
#include <stdio.h>
#include "eeprom.h"

static void delay_1ms(void)
{
	int j;
	for(j=0;j<1700;++j);
}

static void delay(int i)
{
	long j;
	for(j=0;j<10*i;++j);
}

//=========================================================
/*****************************************************
*函数名称：void UART0_write(signed char dat)
*函数功能：UART0_write
*入口参数：void
*出口参数：void
*****************************************************/
void UART0_write(signed char dat)
{
    S0BUF = dat;            //Send data to UART buffer
    while(!TI0);
    TI0 = 0;
}

/*****************************************************
*函数功能：重定向c库函数printf到串口，重定向后可使用printf函数
*****************************************************/
char putchar(char ch)
{
    /* 发送一个字节数据到串口 */
    UART0_write((signed char) ch);
        
    return ch;
}

/*****************************************************
*函数名称：void writeHex(unsigned char num)
*函数功能：writeHex打印16进制num
*入口参数：num
*出口参数：void
*****************************************************/
void writeHex(unsigned char num)
{
	unsigned char i=0;
	i=num/16;
	if(i>9)UART0_write(i-10+'A');
	else UART0_write(i+'0');
	i=num%16;
	if(i>9)UART0_write(i-10+'A');
	else UART0_write(i+'0');
	UART0_write(' ');
}

#define SECTOR_SIZE 128
unsigned char rbuf[SECTOR_SIZE]={0};
unsigned char buf[SECTOR_SIZE]={0};

/*****************************************************
*函数名称：void EEPROMCaseTest(void)
*函数功能：EEPROM基本读写擦测试
*入口参数：void
*出口参数：void
*****************************************************/
void EEPROMCaseTest(void)
{
	int i;
	
	for(i=0;i<SECTOR_SIZE;++i)buf[i]=i+0X80;
	writeData2EEPROM(buf,0,SECTOR_SIZE);
	for(i=0;i<SECTOR_SIZE;++i)rbuf[i]=0;
	readDatafromEEPROM(rbuf,0,SECTOR_SIZE);
	for(i=0;i<SECTOR_SIZE;i++)
	{
		printf("%bx ", rbuf[i]);
	}
} 



/*****************************************************
*函数名称：void FlashCkSumTest(void)
*函数功能：flash 的累加和寄存器测试 
*入口参数：void
*出口参数：void
*****************************************************/
void eeromCkSumTest(void)
{
	unsigned int i,k;
	unsigned char j;	
	for(i=0;i<128/SECTOR_SIZE;++i)
	{
		FSDARL=((i*SECTOR_SIZE)&0xff);
		FSDARH=(((i*SECTOR_SIZE)>>8)&0xff);
		FSCMD=0x4c;
		printf("\r\n%bx%bx", CKSUMH,CKSUML);
		
		//读出数据
		for(k=0;k<SECTOR_SIZE;++k)rbuf[k]=0;
		readDatafromEEPROM(rbuf,(i*SECTOR_SIZE),SECTOR_SIZE);
		k=0;
		for(j=0;j<SECTOR_SIZE;++j)
		{
			k += rbuf[j];
		}
		
		j=k>>8;
		printf(" %bx",j);
		j=k&0xff;
		printf("%bx",j);
		UART0_write('\r');
		UART0_write('\n');
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
    REN0 = 1; 	//串行接收使能位
    RI0  = 0;  	//接收中断标志
    TI0  = 0;  	//发送中断标志
	
    /* 默认定时器1作为时钟源(配置位8Bit自动重载模式不开中断程序) */
    /* TL1 作为 8 位定时器/计数器， TH1 作为自动重载寄存器 */
//    TR1  = 0;    //先停T1
//    TMOD = 0x20;                // 定时器，时钟为系统时钟 12 分频
//    TH1  = 256-4;//波特率10417
//    TR1  = 1;	//开始运行//timer1 start running  	
    
	//TIMER2 作为uart0的波特率时钟源 配置波特率为9600
    TR2  = 0;
    T2MOD= 0x00;/* 定时2中断不使能，不分频 */
    T2CL = 65536 - 52;
    T2CH = 65536 - 52 >> 8;//波特率：9600
    TL2  = T2CL;
    TH2  = T2CH;
    TR2  = 1;    //启动定时器2
    RCLK = 1;   //UART0在模式1和3时使用定时器1/2作为接收波特率时钟
    TCLK = 1;		//UART0在模式1和3时使用定时器1/2作为接收波特率时钟
}

void main(void)
{   
    SCCON = 0x00;//HRC   
    HRCON |= 0x80; 
    delay_1ms();
	
		/*************************管脚配置**********************/ 
	  P10F = 2;
	  P07F = 7;//RX
    P06F = 7;//TX
	
    /****** UART0 模式1（波特率：9600 可调）**************/
    Uart0Mode1();
	  printf("run====\r\n"); 
	

		EEPROMCaseTest();
		eeromCkSumTest();	
while(1)
	{
		P10=~P10;
		delay(1000);
	}
}