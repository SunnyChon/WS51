
#include "WS51F6240.h"
#include <stdio.h>

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

/*****************************************************
*函数名称：void Uart1Mode1(void)
*函数功能：9600波特率
*入口参数：波特率公式: Fsys/(32*(1024-S1REL))
*出口参数：
*****************************************************/
void Uart1Mode1(void)
{
	S1CON = 0x80;	///8位异步模式(1), +0x10/中断使能, +0x20/多机通信使能位, +0x40/串行接收使能位
	S1RELL = 972;
	S1RELH = 972>>8;	//9600
//	S1RELL = 1020;
//	S1RELH = 1020>>8;	//115200
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

//=========================================================
/* SPI接口 寄存器SPCON (A5H) 不可位寻址 */
#define SPEN    0x80       /* SPI 模块使能位 */
#define LSBF    0x40       /* 高低位优先	  0: 高位先发 */
#define SSIG    0x20       /* SPI_CS 引脚无效控制位，默认为 0，此时 SPI_CS 信号有效 */
#define MSTR    0x10       /* 主机/从机选择位 0：从机 */
#define CPOL    0x08       /* 时钟极性选择位  0: 默认情况下时钟为低 */
#define CPHA    0x04       /* 时钟相位选择位  0: 第一个边沿 */
#define CKOS    0x00       /* SPI 输出时钟选择位(0123) */

/*****************************************************
*函数名称：void SPI_Init(void)
*函数功能：SPI_FLASH初始化 作为从机
*入口参数：
*出口参数：
*****************************************************/
void SPI_Init(void)
{	
	/* SPI 模式配置 */
	// FLASH芯片 支持SPI模式0及模式3，据此设置CPOL CPHA
    SPCON=SPEN+CPOL+CKOS+SSIG;//
	// 使能、+LSBF/高低位优先、/SPI_CS、+MSTR从主模式、/极性、+CPHA/相位、/输出时钟
		SPFLG = 0+0x80;	///中断使能位, +0x40/单数据线模式选择位
}

/**
* @brief  使用SPI发送一个字节的数据
* @param  byte：要发送的数据
* @retval 返回接收到的数据
*/
u8 SPI_SendByte(u8 byte)
{
		u8 rDat0;
  
	/* 写入数据寄存器，把要写入的数据写入发送缓冲区 */
    while((SPFLG & 0x04) == 0x04);//写入冲突标志位
    SPDAT = byte;

    //transfer finish
    while((SPFLG & 0x01) == 0);	
    SPFLG &= 0xfe;
    
	/* 读取数据寄存器，获取接收缓冲区数据 */
    rDat0 = SPDAT;
		return rDat0;
}

/**
* @brief  使用SPI读取一个字节的数据
* @param  无
* @retval 返回接收到的数据
*/
u8 SPI_ReadByte(void)
{
  return (SPI_SendByte(0xFF));
}



#define SLAVE_RX_NUM 10
u8 rDat[SLAVE_RX_NUM], rx_ok=0;
void spi_irs(void) interrupt 8
{
	static u8 sDat=0,i=0;
	
//	P17 = ~P17;
	
	// 数据传输完成标志位
	if(0x01 == (SPFLG & 0x01))
	{
		SPFLG &= 0xfe;
		
		/* 读取数据寄存器，获取接收缓冲区数据 */
		rDat[i] = SPDAT;
		i++;
		if(i>=SLAVE_RX_NUM)
		{
			i=0;
			rx_ok=1;
		}
		
		/**************** 填写准备发送数据 ******************/
		sDat++;
		SPDAT = sDat;
		/* 写入数据寄存器，把要写入的数据写入发送缓冲区 */
		while((SPFLG & 0x04) == 0x04);//写入冲突标志位
		
	}
}

/**************************************************************
说明：从机接收到 3 , 发送数据 i
***************************************************************/
void main()
{
    unsigned char i;
    SCCON = 0x00;//HRC
		HRCON |= 0x80;
		delay_1ms();
	
	
    /*************** UART1 模式1（波特率：9600）****************/

		Uart1Mode1();	
    printf("RUN------\r\n");

    
    /*********************** 管脚配置 *************************/	
		P15F = 0x05;  //CS----R2
		P00F = 0x05;  //MOSI--Y1
		P01F = 0x05;  //MISO--W1
		P10F = 0x05;  //SCK---Y2
	
//		P17F = 2;				//用于查看中断标志，翻转IO
	
//  	P02F=6;//UART1_RX
		P16F=6;//UART1_TX

    /********************* SPI_FLASH_Init *********************/	
		SPI_Init();
	
    /********************** 中断使能 **************************/
		EINT5 = 1;		/* INT5 中断使能控制位，用于 ADC/SPI/SCM/EP3 中断 */
		EA=1;

		for(i=0;i<SLAVE_RX_NUM;i++)
		{
			rDat[i]=0;	//清数组
		}	
	
	while(1)
	{	
		if(rx_ok == 1)
		{
			rx_ok = 0;
			printf("\r\nslaver r: ");
			for(i=0;i<SLAVE_RX_NUM;i++)
			{
				printf("%2bx ",rDat[i]);
			}
		}
		
	}

}

    
 
    
   
    




