/*********************************************************
*Copyright (C), 2020-2030, 深圳前海维晟智能技术有限公司
*文件名:	flash.c
*作  者:	
*版  本:
*日  期:
*描  述:	
*备  注:     
**********************************************************/
#include "WS51F6240.h"	
#include <stdio.h>
#include "flash.h"

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

unsigned char rbuf[SECTOR_SIZE]={0};
unsigned char buf[SECTOR_SIZE]={0};
/*****************************************************
*函数名称：void FlashCodeEraseTest(void)
*函数功能： Flash读写擦操作测试
*入口参数：void
*出口参数：void
*****************************************************/
#define SECTOR_TEST 0x30
void FlashCodeEraseTest(void)
{
	int i,j,k;	
  printf("MECON=0X%BX, PADR=0X%BX \r\n", MECON, PADR);
	for(k=0x30;k<0x40;k++)
	{
		PADR = k;
//		PADR = 0X80;
		printf("MECON=0X%BX, PADR=0X%BX \r\n", MECON, PADR);
		printf("code:\r\n");
		/* code区擦写读-扇区 */
		for(j=0x30;j<PADR;j++)
		{
			FlashCodeErase(j,1);		//每个扇区大小为 128 字节
            writeHex(j);
            printf("\r\n");
			for(i=0;i<SECTOR_SIZE;i++)buf[i]=j;
                FLASHCodeBufferWrite(buf,j*128,SECTOR_SIZE);
			for(i=0;i<SECTOR_SIZE;++i)rbuf[i]=0;
                FLASHCodeBufferRead(rbuf,j*128,SECTOR_SIZE);
			for(i=0;i<SECTOR_SIZE;++i)
				printf("%BX ",rbuf[i]);
            printf("\r\n");
		}
			
		printf("data:\r\n");
		/* data区擦写读-扇区 */		
		for(j=0;j<(0x40-PADR);j++)	//起始地址从 PADR*128 开始, 
		{
			FlashDataErase(j,1);
            writeHex(j);
            printf("\r\n");
			for(i=0;i<SECTOR_SIZE;i++)buf[i]=j;
                FLASHDataBufferWrite(buf,128*j,SECTOR_SIZE);
			for(i=0;i<SECTOR_SIZE;i++)rbuf[i]=0;
                FLASHDataBufferRead(rbuf,128*j,SECTOR_SIZE);
			for(i=0;i<SECTOR_SIZE;++i)
				printf("%BX ",rbuf[i]);
            printf("\r\n");
		}
	}	
}

/*****************************************************
*函数名称：void FlashCkSumTest(void)
*函数功能：flash 的累加和寄存器测试 
*入口参数：void
*出口参数：void
*****************************************************/
void FlashCkSumTestCode(void)
{
	unsigned int i,k;
	unsigned char j;	
  PADR=0x80;
  printf("MECON=0X%BX, PADR=0X%BX \r\n", MECON, PADR);
	printf("code 校验和\r\n");	
	for(i=0;i<PADR;++i)
	{
		FSDARL=((i*SECTOR_SIZE)&0xff);
		FSDARH=(((i*SECTOR_SIZE)>>8)&0xff);
		FSCMD=FLASH_CHECK_SUM_CODE;
		printf("i=%x, %bx%bx", i,CKSUMH,CKSUML);
		
//		FSADRL=((i*SECTOR_SIZE)&0xff);
//		FSADRH=(((i*SECTOR_SIZE)>>8)&0xff);
//		FSCMD=INNER_FLASH_CHECK_SUM_DATA;
//		printf(" %bx%bx", CKSUMH,CKSUML);

		
		//读出数据
		for(k=0;k<SECTOR_SIZE;++k)rbuf[k]=0;
            FLASHCodeBufferRead(rbuf,(i*SECTOR_SIZE),SECTOR_SIZE);
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
*函数名称：void FlashCkSumTest(void)
*函数功能：flash 的累加和寄存器测试 
*入口参数：void
*出口参数：void
*****************************************************/
void FlashCkSumTestData(void)
{
	unsigned int i,k;
	unsigned char j;	
    printf("MECON=0X%BX, PADR=0X%BX \r\n", MECON, PADR);
    PADR=0x30;
    printf("MECON=0X%BX, PADR=0X%BX \r\n", MECON, PADR);
	printf("data 校验和");		
//	for(i=0;i<((FlASH_SIZE/SECTOR_SIZE)-PADRD);++i)
	for(i=0;i<((0x80)-PADR);++i)
	{	
		FSDARL=(((i)*SECTOR_SIZE)&0xff);//+0x30
		FSDARH=((((i)*SECTOR_SIZE)>>8)&0xff);//+0x30
		FSCMD=FLASH_CHECK_SUM_DATA;
		printf("i=%x, %bx%bx", i, CKSUMH,CKSUML);

		
		//读出数据
		for(k=0;k<SECTOR_SIZE;++k)rbuf[k]=0;
        FLASHDataBufferRead(rbuf,(i*SECTOR_SIZE),SECTOR_SIZE);
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
	 	
    
	//TIMER2 作为uart0的波特率时钟源 配置波特率为9600
    TR2  = 0;
    T2MOD= 0x00;/* 定时2中断不使能，不分频 */
    T2CL = 65536 - 2;
    T2CH = 65536 - 2 >> 8;//波特率：9600
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

	
		//flash 的基本读写测试
		FlashCodeEraseTest();

		//flash 的累加和寄存器测试
		FlashCkSumTestCode();
		FlashCkSumTestData();
		
	while(1)
	{
		P10=~P10;
		delay(1000);
	}
}