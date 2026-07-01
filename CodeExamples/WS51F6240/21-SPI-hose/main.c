

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
*函数功能：9600波特率
*入口参数：
*出口参数：
*****************************************************/
void Uart1Mode1(void)
{
	S1CON = 0x80;	///8位异步模式(1), +0x10/中断使能, +0x20/多机通信使能位, +0x40/串行接收使能位
	S1RELL = 972;
	S1RELH = 972>>8;
}

//=========================================================
/* SPI接口 寄存器SPCON (A5H) 不可位寻址 */
#define SPEN    0x80       /* SPI 模块使能位 */
#define LSBF    0x40       /* 高低位优先	  0: 高位先发 */
#define SSIG    0x20       /* SPI_CS 引脚无效控制位，默认为 0，此时 SPI_CS 信号有效 */
#define MSTR    0x10       /* 主机/从机选择位 0：从机 */
#define CPOL    0x08       /* 时钟极性选择位  0: 默认情况下时钟为低 */
#define CPHA    0x04       /* 时钟相位选择位  0: 第一个边沿 */
#define CKOS    0x02       /* SPI 输出时钟选择位(0123) 
                            * 0_4M    1_666.6k    2_6.67K    3_80k   
                            */
//-----------------------------------------------
#define	SPI_CS_LOW()	P15 = 0;
#define	SPI_CS_HIGH()	P15 = 1;
#define KEY_IO	P11

/*****************************************************
*函数名称：void SPI_Init(void)
*函数功能：SPI_FLASH初始化 作为主机
*入口参数：
*出口参数：
*****************************************************/
void SPI_Init(void)
{
	/* 停止信号 FLASH: CS引脚高电平*/
    SPI_CS_HIGH();  //P13 = 1
	
	/* SPI 模式配置 */
	// FLASH芯片 支持SPI模式0及模式3，据此设置CPOL CPHA
    SPCON=SPEN+MSTR+CPOL+CKOS;//
	// 使能、+LSBF/高低位优先、+SSIG/SPI_CS、从主模式、/极性、+CPHA/相位、/输出时钟
		SPFLG = 0;	//+0x80/中断使能位, +0x40/单数据线模式选择位
}

/**
* @brief  使用SPI发送一个字节的数据
* @param  byte：要发送的数据
* @retval 返回接收到的数据
*/
u8 SPI_SendByte(u8 byte)
{
	u8 rDat;
  
	/* 写入数据寄存器，把要写入的数据写入发送缓冲区 */
    while((SPFLG & 0x04) == 0x04);//写入冲突标志位
    SPDAT = byte;

    //transfer finish
    while((SPFLG & 0x01) == 0);	
    SPFLG &= 0xfe;
    
	/* 读取数据寄存器，获取接收缓冲区数据 */
    rDat = SPDAT;
	return rDat;
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

/*****************************************************
* 中断服务函数
*****************************************************/
void spi_irs(void) interrupt 8
{
//	// 数据传输完成标志位
//	if(0x01 == (SPFLG & 0x01))
//	{
//		SPFLG &= 0xfe;
//	}
	
//	// 故障模式标志位
//	if(0x02 == (SPFLG & 0x02))
//	{
//		SPFLG &= 0xfd;
//	}
//	P10 = ~P10;
}

void WS51_TestSlave(u8 Temp[10])
{	 
	u8 i=0;	
	SPI_CS_LOW();		/* 通讯开始：CS低 */
	for(i=0;i<10;++i)	
	{	
		
		SPI_CS_LOW();		/* 通讯开始：CS低 */
		Temp[i] = SPI_SendByte(i);	//只发送1个字节	
		SPI_CS_HIGH();	/* 通讯结束：CS高 */
		delay_1ms();	
	}	
	SPI_CS_HIGH();	/* 通讯结束：CS高 */
}   

/**************************************************************
说明：主机发送；操作-按按键P11，发送一次SPI数据
***************************************************************/
void main()
{
    unsigned char i,rDat[10]={0};
    SCCON = 0x00;//HRC   
		HRCON |= 0x80;
		delay_1ms();
	
	
    /*************** UART1 模式1（波特率：9600）****************/
//		P02F=6;//UART1_RX
		P16F=6;//UART1_TX
		Uart1Mode1();	
    printf("RUN------\r\n");

		// 定时器1溢出率，可用于配置spi----时钟
		TH1=256-100;	//spi----6.67K
    TMOD = 0x20;  	//模式，+0x40计数定时选择，+0x80门控选择
    TR1 = 1;		//开始运行//timer1 start running 

		// 定时器2溢出率，可用于配置spi----时钟
    T2CH = (65536-100)>>8;
    T2CL = (65536-100);	//spi---80k
    TL2 = T2CL;
    TH2 = T2CH;    
    T2MOD = 0;		//重载模式0,+0x80开中断使能,+0x4/T2边沿选择,+0x08/T2EX边沿选择
    T2CON = 0x04;	//启动模块,+0x08/T2EX使能,+0x02/计数定时选择,+0x1/抓取功能,	

    /*********************** 管脚配置 *************************/		
		P15F = 0x02;  //CS----R2
		P00F = 0x05;  //MOSI--Y1
		P01F = 0x05;  //MISO--W1
		P10F = 0x05;  //SCK---Y2	
		
		P13	=1;
    /********************* SPI_FLASH_Init *********************/	
		SPI_Init();

    /********************** 中断使能 **************************/
//	EINT5 = 1;		/* INT5 中断使能控制位，用于 ADC/SPI/SCM/EP3 中断 */
//	EA=1;
	
//	P10F = 2;		//用于查看中断标志，翻转IO
	P11F = 0x81;	//上拉输入 按键
	while(1)
	{
//		if(KEY_IO==0)
//		{
//			delay(137);	//延时10ms
//			if(KEY_IO==0)
//			{	
//				while(KEY_IO==0);
				//send+recive
				WS51_TestSlave(rDat);
				
				for(i=0;i<10;i++)
				printf("%2bx ",rDat[i]);     
				printf("\r\n");
				delay(1000);
//			}
//		}
	}

}

    
 
    
   
    




