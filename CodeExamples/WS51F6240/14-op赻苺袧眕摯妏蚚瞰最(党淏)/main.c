/*********************************************************
*Copyright (C), 2020-2030, 深圳前海维晟智能技术有限公司
*文件名:	op.c
*作  者:	
*版  本:	
*日  期:	
*描  述:	
*备  注:     
**********************************************************/
#include "WS51F6240.h"
#include "intrins.h"
#include <stdio.h>

unsigned int i ;
unsigned char dat0;
unsigned char Rx_flag=0;
static void delay_1ms(void)
{
	int j;
	for(j=0;j<1700;++j);
}

static void delay_10ms(void)
{
	int j;
	for(j=0;j<17700;++j);
}

void Uart1_Isr() interrupt 7
{
    if(RI1 == (S1CON&RI1))     //如果接收到计算机发的数据
    {
        S1CON &= ~RI1;     //清除标志位
		dat0 = S1BUF;
		Rx_flag = 1;
    }
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

#define SECTOR_SIZE 128

#define NVR12_START_ADDR 0X580	//扇区首地址
#define NVR13_START_ADDR 0X600	
#define NVR14_START_ADDR 0X680	
#define NVR15_START_ADDR 0X700	
#define NVR16_START_ADDR 0X780	

//OP修调参数地址
//已经锁了的芯片，后期OP校准
#define OP_ENABLE_ADDR_NVR13	 	 0x637 //往此地址写0xaa标志以下两个值有效
#define OP_NMOS_VAL_ADDR_NVR13     0x638 //OP_NMOS的校正值
#define OP_PMOS_VAL_ADDR_NVR13     0x639 //OP_PMOS的校正值
//成测厂OP校准的地址
#define OP_ENABLE_ADDR_NVR15	 	 0x70F //往此地址写0xaa标志以下两个值有效
#define OP_NMOS_VAL_ADDR_NVR15     0x710 //OP_NMOS的校正值
#define OP_PMOS_VAL_ADDR_NVR15     0x711 //OP_PMOS的校正值

//修调值写入 OPNPS为0时写入NMOS修调值，为1时写入PMOS修调值



#define NVR_UNLOCK 0X78
//#define NVR_WRITE 0X86
#define NVR_WRITE 0X82
//#define NVR_ERASE 0X87
#define NVR_ERASE 0X83
#define FLASH_ERASE_UN-MASK 0X04
//#define BANDGAP_TRIMMING_ENABLE 0x100
//#define BANDGAP_TRIMMING_AUTOLOAD_VALUE 0x101
#define NVR_LOCK 0X87
#define NVR_READ 0X81
//#define NVR_READ 0X85


unsigned char idata rbuf[SECTOR_SIZE]={0};

/*****************************************************
*函数名称：void EraseNVR(unsigned short SectorAddr))
*函数功能：NVR扇区擦除 
*入口参数：SectorAddr_扇区首地址(NVR1/2/3/4_START_ADDR)
*出口参数：void
*****************************************************/
void EraseNVR(unsigned short SectorAddr)
{
	//1  Flash unlock
	FSFLG=NVR_UNLOCK;

	//2  write address
	FSDARL=(SectorAddr&0xff);
	FSDARH=((SectorAddr>>8)&0xff);
	//3  Flash erase cmd
	FSCMD=NVR_ERASE;
	//4 NVR lock
	FSFLG=NVR_LOCK;
}
void readDatafromNVR(unsigned char *buf,unsigned short SectorAddr,unsigned short len)
{
	unsigned char i=0;
	
	FSFLG = NVR_UNLOCK;
	//1  read cmd
	FSCMD=NVR_READ;
	for(i=0;i<len;++i)
	{
		//2  write address		
		FSDARL=(SectorAddr&0xff);
		FSDARH=((SectorAddr>>8)&0xff);
		++SectorAddr;
		//3 read data
		buf[i]=FSDAT;
	}
}

void WriteDataNVR(unsigned char *buf,unsigned short SectorAddr,unsigned short len)
{
	unsigned char i=0;
	//1  Flash unlock
	FSFLG=NVR_UNLOCK;
	//2  Flash  write cmd
	FSCMD=NVR_WRITE;	
	for(i=0;i<len;++i)
	{
		//3  write address		
		FSDARL=(SectorAddr&0xff);
		FSDARH=((SectorAddr>>8)&0xff);
		SectorAddr++;
		//4 write data
		FSDAT=buf[i];
	}
	//4 NVR lock
	FSFLG=NVR_LOCK;
}

//uint8_t readDatafromNVR(uint16_t reg)
//{
//	uint8_t dat;
//	
//	FSFLG = NVR_UNLOCK;
//	//1  read cmds
//	FSCMD=NVR_READ;
//		//2  write address		
//		FSDARL=(reg&0xff);
//		FSDARH=((reg>>8)&0xff);		
//		//3 read data
//		dat=FSDAT;
//	
//		return dat;
//}


/*****************************************************
*函数名称：cal_op(void)
*函数功能：op校准
*入口参数：
*出口参数：
*****************************************************/
void cal_op(void)
{
				u8 nmos_val = 0;
				u8 pmos_val = 0;
				int i,roll = 0;
	
				OPCON = 0XA0;
				OPCFG = 0XC0;
				OPCFG = 0X80;
				printf("OPCON=%bx\r\n", OPCON);  //打印OPCON的初值
				while(0x10 !=(OPCON&0X10)) 
				{
					OPCFG ++;
					delay_10ms();	
				}
				printf("PMOS:OPCFG=%bx\r\n", OPCFG);
				pmos_val = OPCFG;
				OPCON = 0XA0; 
				OPCFG &= 0X7f;
				OPCFG = 0;
				delay_10ms();
				while(0x10 !=(OPCON&0X10)) 
				{
					OPCFG ++;
					delay_10ms();	
				}
				printf("NMOS:OPCFG=%bx\r\n", OPCFG);	
				nmos_val = OPCFG;
						
				readDatafromNVR(rbuf,NVR13_START_ADDR,SECTOR_SIZE);	
				
				printf("before:\r\n");
				roll = 0;
				for(i=0; i<SECTOR_SIZE; i++)
				{
						printf("%b02x  ",rbuf[i]);
						roll++;
						if(roll % 16 == 0)
						printf("\r\n");
				}
				roll = 0;
				
				rbuf[OP_ENABLE_ADDR_NVR13-NVR13_START_ADDR]=0xaa;
				//内部
				rbuf[OP_NMOS_VAL_ADDR_NVR13-NVR13_START_ADDR]=nmos_val;
				rbuf[OP_PMOS_VAL_ADDR_NVR13-NVR13_START_ADDR]=pmos_val;
				
				EraseNVR(NVR13_START_ADDR);
				delay_10ms();
				
				WriteDataNVR(rbuf,NVR13_START_ADDR,SECTOR_SIZE);
				delay_1ms();	

				printf("after:\r\n");
				readDatafromNVR(rbuf,NVR13_START_ADDR,SECTOR_SIZE);
				roll = 0;
				for(i=0; i<SECTOR_SIZE; i++)
				{
						printf("%b02x  ",rbuf[i]);
						roll++;
						if(roll % 16 == 0)
						printf("\r\n");
				}
				roll = 0;
}

/*****************************************************
*函数名称：init_op(void)
*函数功能：初始化
*入口参数：
*出口参数：
*****************************************************/
u8 init_op(void)
{
	u8 opflag = 0;
	u8 nmos_val = 0;
	u8 pmos_val = 0;
	int i,roll = 0;
	OPCON = 0XA0; //使能NMOS
		
	//先读NVR15是否保存有OP修调数据
	readDatafromNVR(rbuf,NVR15_START_ADDR,SECTOR_SIZE);
	if(rbuf[OP_ENABLE_ADDR_NVR15-NVR15_START_ADDR] == 0xaa)//数据保存在NVR15
	{
		opflag=0;
		nmos_val = rbuf[OP_NMOS_VAL_ADDR_NVR15-NVR15_START_ADDR];
		pmos_val = rbuf[OP_PMOS_VAL_ADDR_NVR15-NVR15_START_ADDR];
		printf("NVR15:nmos_val=%bx\r\n", nmos_val);  //打印OPCON的初值
		printf("NVR15:pmos_val=%bx\r\n", pmos_val);  //打印OPCON的初值
		for(i=0; i<SECTOR_SIZE; i++)
		{
				printf("%b02x  ",rbuf[i]);
				roll++;
				if(roll % 16 == 0)
				printf("\r\n");
		}		
	
	}
	else //数据没有保存NVR15，读NVR13
	{
				readDatafromNVR(rbuf,NVR13_START_ADDR,SECTOR_SIZE);
				roll = 0;
				for(i=0; i<SECTOR_SIZE; i++)
				{
						printf("%b02x  ",rbuf[i]);
						roll++;
						if(roll % 16 == 0)
						printf("\r\n");
				}
				roll = 0;				
				if(rbuf[OP_ENABLE_ADDR_NVR13-NVR13_START_ADDR] == 0xaa)
				{
					opflag=0;
					nmos_val = rbuf[OP_NMOS_VAL_ADDR_NVR13-NVR13_START_ADDR];
					pmos_val = rbuf[OP_PMOS_VAL_ADDR_NVR13-NVR13_START_ADDR];
					printf("NVR13:nmos_val=%bx\r\n", nmos_val);  //打印OPCON的初值
					printf("NVR13:pmos_val=%bx\r\n", pmos_val);  //打印OPCON的初值
				}
				else
				{
					opflag=1;
					printf("not cal op\r\n", pmos_val);  //没有校准OP				
				}
				
	}
				
//	if(!opflag)
//	{
		OPCON = 0XA0; //使能NMOS
		OPCFG = 0XC0;
		OPCFG = pmos_val;
		OPCFG &= 0X7f;
		OPCFG = nmos_val;
		
		delay_10ms();	
		OPCON = 0xc1;	// 增益选择 0为外部电阻网络   0x01~0x0f对应x1 ~ x128
//	}
		

	return opflag;
}


/**************************************************************
说明：

OP修调值存储地址:
OP_ENABLE_ADDR	 	 0x637 //往此地址写0xaa标志以下两个值有效
OP_NMOS_VAL_ADDR     0x638 //OP_NMOS的校正值
OP_PMOS_VAL_ADDR     0x640 //OP_PMOS的校正值

void cal_op(void) 此函数进行OP的自校准并保存校准值，自校准的时候OPOUT与OPN、OPP之间不能连接不能有反馈电路。校准值存储到NVR用户可使用的区域，现在是存储到了NVR13。

void cal_op(void) 此函数为使用OP时，从NVR13读取校准值并写入OPCFG寄存器。

***************************************************************/
void main()
{  		
		u8 OP_flag = 0,i=0;
		SCCON = 0x00;//HRC
		HRCON |= 0x80;
		delay_1ms();

		/****************** 管脚配置 ********************/ 	
		P07F = 0X05; //OPOUT
		P05F = 0X05; //OPP
		P06F = 0X05; //0PN
		P02F = 6;    //UART1_RX
	
		P16F = 6;    //UART1_TX //如果用了P16引脚串口打印，可能与盒子烧录器SDA冲突导致不能下载，要用烧录器上位机擦除程序 
		P10F = 2; //
		
	
	/***************  op、串口初始化  ****************/
		Uart1Mode1();	
		//cal_op();	//校准op的时候跑一遍这个函数，OPP/OPN/OPOUT不要接反馈
		OP_flag=init_op(); //使用op的时候用这个函数，不要跑上面的校准函数,OP_flag为0说明OP已经校准，1代表没有校准
		printf("RUN--OP_flag=%bd\r\n",OP_flag);
		
		while(1)
		{
			if(OP_flag)
			{
				P10=~P10;
				for(i=0;i<50;i++)
					delay_10ms();				
			}
		
			
		}
			
}

