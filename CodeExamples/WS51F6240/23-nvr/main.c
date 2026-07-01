/*********************************************************
*Copyright (C), 2020-2030, 深圳前海维晟智能技术有限公司
*文件名:	nvr.c
*作  者:	
*版  本:	
*日  期:	
*描  述:	
*备  注:     
**********************************************************/

#include "WS51F6240.h"
#include <stdio.h>
#include "nvr.h"

static void delay_1ms(void)
{
	int j;
	for(j=0;j<1700;++j);
}
void delay_ms(unsigned int i)
{
	unsigned long j=0;
		for(j=0;j<(i*16/12);++j);
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

unsigned char rbuf[SECTOR_SIZE]={0};
unsigned char buf[SECTOR_SIZE]={0};

/*****************************************************
*函数名称：void NVRCaseTest(void)
*函数功能：NVR基本读写擦测试
*入口参数：void
*出口参数：void
*****************************************************/
void NVRCaseTest(void)
{
	int i;
	
	// NVR1 基本擦 写 读 (0~0x7f)
	EraseNVR(NVR1_START_ADDR);
	delay_ms(10);
	for(i=0;i<SECTOR_SIZE;i++)buf[i]=1;//i
        WriteDataNVR(buf,NVR1_START_ADDR,SECTOR_SIZE);
	for(i=0;i<SECTOR_SIZE;i++)rbuf[i]=0;
        readDatafromNVR(rbuf,NVR1_START_ADDR,SECTOR_SIZE);
	delay_ms(10);
	for(i=0;i<SECTOR_SIZE;i++)
		printf("i=%x,val=0X%BX\r\n",NVR1_START_ADDR+i,rbuf[i]);
	
	// NVR2 基本擦 写 读 (0x80~0xff)
	EraseNVR(NVR2_START_ADDR);
	delay_ms(10);
	for(i=0;i<SECTOR_SIZE;i++)buf[i]=2;//i+0x80
        WriteDataNVR(buf,NVR2_START_ADDR,SECTOR_SIZE);
	for(i=0;i<SECTOR_SIZE;i++)rbuf[i]=0;
        readDatafromNVR(rbuf,NVR2_START_ADDR,SECTOR_SIZE);
	delay_ms(10);
	for(i=0;i<SECTOR_SIZE;i++)
		printf("i=%x,val=0X%BX\r\n",NVR2_START_ADDR+i,rbuf[i]);
	
	// NVR3 基本擦 写 读 (0~0x7f)
	EraseNVR(NVR3_START_ADDR);
	delay_ms(10);
	for(i=0;i<SECTOR_SIZE;i++)buf[i]=3;//i
        WriteDataNVR(buf,NVR3_START_ADDR,SECTOR_SIZE);
	for(i=0;i<SECTOR_SIZE;i++)rbuf[i]=0;
        readDatafromNVR(rbuf,NVR3_START_ADDR,SECTOR_SIZE);
	delay_ms(10);
	for(i=0;i<SECTOR_SIZE;i++)
		printf("i=%x,val=0X%BX\r\n",NVR3_START_ADDR+i,rbuf[i]);
	
	// NVR4 基本擦 写 读 (0x80~0xff) 
	EraseNVR(NVR4_START_ADDR);
	delay_ms(10);
	for(i=0;i<SECTOR_SIZE;i++)buf[i]=4;
        WriteDataNVR(buf,NVR4_START_ADDR,SECTOR_SIZE);
	for(i=0;i<SECTOR_SIZE;i++)rbuf[i]=0;
        readDatafromNVR(rbuf,NVR4_START_ADDR,SECTOR_SIZE);
	delay_ms(10);
	for(i=0;i<SECTOR_SIZE;i++)
		printf("i=%x,val=0X%BX\r\n",NVR4_START_ADDR+i,rbuf[i]); 

	// NVR5 基本擦 写 读 (0x80~0xff) 
	EraseNVR(NVR5_START_ADDR);
	delay_ms(10);
	for(i=0;i<SECTOR_SIZE;i++)buf[i]=5;
        WriteDataNVR(buf,NVR5_START_ADDR,SECTOR_SIZE);
	for(i=0;i<SECTOR_SIZE;i++)rbuf[i]=0;
        readDatafromNVR(rbuf,NVR5_START_ADDR,SECTOR_SIZE);
	delay_ms(10);
	for(i=0;i<SECTOR_SIZE;i++)
		printf("i=%x,val=0X%BX\r\n",NVR5_START_ADDR+i,rbuf[i]);             
  
	// NVR6 基本擦 写 读 (0x80~0xff) 
	EraseNVR(NVR6_START_ADDR);
	delay_ms(10);
	for(i=0;i<SECTOR_SIZE;i++)buf[i]=6;
        WriteDataNVR(buf,NVR6_START_ADDR,SECTOR_SIZE);
	for(i=0;i<SECTOR_SIZE;i++)rbuf[i]=0;
        readDatafromNVR(rbuf,NVR6_START_ADDR,SECTOR_SIZE);
	delay_ms(10);
	for(i=0;i<SECTOR_SIZE;i++)
		printf("i=%x,val=0X%BX\r\n",NVR6_START_ADDR+i,rbuf[i]);            
 
	// NVR7 基本擦 写 读 (0x80~0xff) 
	EraseNVR(NVR7_START_ADDR);
	delay_ms(10);
	for(i=0;i<SECTOR_SIZE;i++)buf[i]=7;
        WriteDataNVR(buf,NVR7_START_ADDR,SECTOR_SIZE);
	for(i=0;i<SECTOR_SIZE;i++)rbuf[i]=0;
        readDatafromNVR(rbuf,NVR7_START_ADDR,SECTOR_SIZE);
	delay_ms(10);
	for(i=0;i<SECTOR_SIZE;i++)
		printf("i=%x,val=0X%BX\r\n",NVR7_START_ADDR+i,rbuf[i]);        

	// NVR8 基本擦 写 读 (0x80~0xff) 
	EraseNVR(NVR8_START_ADDR);
	delay_ms(10);
	for(i=0;i<SECTOR_SIZE;i++)buf[i]=8;
        WriteDataNVR(buf,NVR8_START_ADDR,SECTOR_SIZE);
	for(i=0;i<SECTOR_SIZE;i++)rbuf[i]=0;
        readDatafromNVR(rbuf,NVR8_START_ADDR,SECTOR_SIZE);
	delay_ms(10);
	for(i=0;i<SECTOR_SIZE;i++)
		printf("i=%x,val=0X%BX\r\n",NVR8_START_ADDR+i,rbuf[i]);         

	// NVR9 基本擦 写 读 (0x80~0xff) 
	EraseNVR(NVR9_START_ADDR);
	delay_ms(10);
	for(i=0;i<SECTOR_SIZE;i++)buf[i]=9;
        WriteDataNVR(buf,NVR9_START_ADDR,SECTOR_SIZE);
	for(i=0;i<SECTOR_SIZE;i++)rbuf[i]=0;
        readDatafromNVR(rbuf,NVR9_START_ADDR,SECTOR_SIZE);
	delay_ms(10);
	for(i=0;i<SECTOR_SIZE;i++)
		printf("i=%x,val=0X%BX\r\n",NVR9_START_ADDR+i,rbuf[i]);     

	// NVR10 基本擦 写 读 (0x80~0xff) 
	EraseNVR(NVR10_START_ADDR);
	delay_ms(10);
	for(i=0;i<SECTOR_SIZE;i++)buf[i]=10;
        WriteDataNVR(buf,NVR10_START_ADDR,SECTOR_SIZE);
	for(i=0;i<SECTOR_SIZE;i++)rbuf[i]=0;
        readDatafromNVR(rbuf,NVR10_START_ADDR,SECTOR_SIZE);
	delay_ms(10);
	for(i=0;i<SECTOR_SIZE;i++)
		printf("i=%x,val=0X%BX\r\n",NVR10_START_ADDR+i,rbuf[i]);       

	// NVR11 基本擦 写 读 (0x80~0xff) 
	EraseNVR(NVR11_START_ADDR);
	delay_ms(10);
	for(i=0;i<SECTOR_SIZE;i++)buf[i]=11;
        WriteDataNVR(buf,NVR11_START_ADDR,SECTOR_SIZE);
	for(i=0;i<SECTOR_SIZE;i++)rbuf[i]=0;
        readDatafromNVR(rbuf,NVR11_START_ADDR,SECTOR_SIZE);
	delay_ms(10);
	for(i=0;i<SECTOR_SIZE;i++)
		printf("i=%x,val=0X%BX\r\n",NVR11_START_ADDR+i,rbuf[i]);       

	// NVR12 基本擦 写 读 (0x80~0xff) 
	EraseNVR(NVR12_START_ADDR);
	delay_ms(10);
	for(i=0;i<SECTOR_SIZE;i++)buf[i]=12;
        WriteDataNVR(buf,NVR12_START_ADDR,SECTOR_SIZE);
	for(i=0;i<SECTOR_SIZE;i++)rbuf[i]=0;
        readDatafromNVR(rbuf,NVR12_START_ADDR,SECTOR_SIZE);
	delay_ms(10);
	for(i=0;i<SECTOR_SIZE;i++)
		printf("i=%x,val=0X%BX\r\n",NVR12_START_ADDR+i,rbuf[i]); 
} 

/*****************************************************
*函数名称：void nvrCkSumTest(void)
*函数功能：flash 的累加和寄存器测试 
*入口参数：void
*出口参数：void
*****************************************************/
void nvrCkSumTest(void)
{
	unsigned int i,k;
	unsigned char j;	
	for(i=0;i<16;++i)
	{
		FSDARL=((i*SECTOR_SIZE)&0xff);
		FSDARH=(((i*SECTOR_SIZE)>>8)&0xff);
		FSCMD=0x8c;
		printf("i= %d, %bx_%bx", i, CKSUMH,CKSUML);
		
		//读nvr区域
		for(k=0;k<SECTOR_SIZE;++k)rbuf[k]=0;
		readDatafromNVR(rbuf,(i*SECTOR_SIZE),SECTOR_SIZE);
		k=0;
		for(j=0;j<SECTOR_SIZE;++j)
		{
			k += rbuf[j];
		}
		
		j=k>>8;
		printf(" %bx",j);
		j=k&0xff;
		printf("_%bx",j);
		UART0_write('\r');
		UART0_write('\n');
	}
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
	
		NVRCaseTest();
		nvrCkSumTest();
	
	while(1)
	{
		P10=~P10;
		delay(1000);
	}
}