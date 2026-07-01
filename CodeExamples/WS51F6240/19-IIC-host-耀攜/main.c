
#include "WS51F6240.h"
#include <stdio.h>

static void delay(int i)
{
	long j;
	for(j=0;j<10*i;++j);
}

static void delay_us(int i)
{
	long j;
    while(i--)
        j++;
}
 
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

#define  IIC_SCL	P10
#define  IIC_SDA	P11
#define  READ_OUT	P11F=0Xa2
#define  READ_IN	P11F=0Xa2
#define  READ_SDA	P11
#define  IIC_CLK_ADJ 1

//总线初始化
void IIC_Init(void)
{
	IIC_SDA=1;
	IIC_SCL=1;
	delay_us(2);
}

//产生IIC起始信号
void IIC_Start(void)
{
	IIC_SDA=1;//释放SDA总线
	delay_us(2);	  	  
	IIC_SCL=1;
	delay_us(2);	
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(2);	
	IIC_SCL=0;//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC停止信号
void IIC_Stop(void)
{
	IIC_SCL=0;
	delay_us(2);
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high 	
	delay_us(2);
	IIC_SCL=1; 
	delay_us(2);
	IIC_SDA=1;//发送I2C总线结束信号
	delay_us(2);							   	
}

//IIC发送一个字节  
void IIC_Send_Byte(unsigned char txd)
{                        
	unsigned char t;  
	IIC_SCL=0;//拉低时钟开始数据传输	
	for(t=0;t<8;t++)
	{              
		if (txd & 0x80)
				IIC_SDA = 1;
		else
				IIC_SDA = 0;
				txd<<=1; 	  
				delay_us(IIC_CLK_ADJ);	
				IIC_SCL=1;
				delay_us(IIC_CLK_ADJ);	
				IIC_SCL=0;	
	}			
} 	    

//读1个字节  
uint8_t IIC_Read_Byte(void)
{
	unsigned char i,receive=0;
	
	IIC_SDA = 1;		//od pin 输出1表示“读pin”
	READ_IN;
	for(i=0;i<8;i++ )
	{
		IIC_SCL=0; 
		delay_us(IIC_CLK_ADJ);
		
		IIC_SCL=1;
		receive<<=1;
		
		if (READ_SDA)
				receive |= 0x01;
				delay_us(IIC_CLK_ADJ); 
	}
	
	IIC_SCL = 0;
	IIC_SDA=1;
	READ_OUT;
	return receive;
}

//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
uint8_t IIC_Wait_Ack(void)
{
	uint16_t ucErrTime=0;
	IIC_SDA=1;
	READ_IN;	
	delay_us(IIC_CLK_ADJ);
	delay_us(IIC_CLK_ADJ);	//等待从机回复ack   
	IIC_SCL=1;
	delay_us(IIC_CLK_ADJ);
	
	while(READ_SDA==1)
	{
		ucErrTime++;
		if(ucErrTime>2500)//20200313
		{
			IIC_SCL = 0;
			IIC_SDA=1;
			READ_OUT;
			IIC_Stop(); //20200313
			return 1;
			//break;
		}
	}
	IIC_SCL=0;//时钟输出0 
	IIC_SDA=1;
	READ_OUT;	   
	return 0;  
} 


//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
uint8_t IIC_Wait_NAck(void)
{
	uint16_t ucErrTime=0;
	IIC_SDA=1;	
	READ_IN;
	delay_us(IIC_CLK_ADJ);
	delay_us(IIC_CLK_ADJ);	//等待从机回复ack   
	IIC_SCL=1;
	delay_us(IIC_CLK_ADJ);
	delay_us(IIC_CLK_ADJ);
	
//	while(READ_SDA)
//	{
//		ucErrTime++;
//		if(ucErrTime>2500)//20200313
//		{
//			IIC_SCL = 0;
//			IIC_Stop(); //20200313
//			return 1;
//			//break;
//		}
//	}
	IIC_SCL=0;//时钟输出0 
	IIC_SDA=1;
	READ_OUT;	   
	return 0;  
} 

//产生ACK应答
void IIC_Ack(void)
{
	IIC_SCL=0;
	IIC_SDA=0;
	delay_us(IIC_CLK_ADJ);
	IIC_SCL=1;
	
	delay_us(IIC_CLK_ADJ);
	IIC_SCL=0;

}

//不产生ACK应答		    
void IIC_NAck(void)
{
	IIC_SCL=0;
	IIC_SDA=1;
	delay_us(IIC_CLK_ADJ);
	IIC_SCL=1;
	
	delay_us(IIC_CLK_ADJ);
	IIC_SCL=0;
}


/***********************************************************************************************
*函数名称：void I2C_ReadByteNum(uint8_t addr,uint8_t device_addr, uint8_t *pdataR, uint8_t lengthR)
*函数功能：IIC读数据
*入口参数：
			device_addr：设备地址
			addr：寄存器地址
			pdataR： 存放读缓存数组
			lengthR：读取字节个数
*出口参数：
***********************************************************************************************/
uint8_t I2C_ReadByteNum(uint8_t addr,uint8_t device_addr, uint8_t *pdataR, uint8_t lengthR)
{	
		uint8_t ack=0; 
		uint8_t ret;
		uint8_t i=0;
    
    IIC_Start(); 
	
    IIC_Send_Byte(device_addr);
		ack = IIC_Wait_Ack();	
		if (ack != 0)
		{
				ret=ack;
				printf("stop0\r\n");
				return ret;
		}
	
		IIC_Send_Byte(addr);
		ack = IIC_Wait_Ack();	
		if (ack != 0)
		{
				ret=ack;
				return ret;
		}	
		IIC_Stop();
		
		delay_us(150);
		IIC_Start();
	
    IIC_Send_Byte(device_addr+1);
		ack = IIC_Wait_Ack();	
		if (ack != 0)
		{
				ret=ack;
				return ret;
		}
		
		for(i=0;i<lengthR-1;i++)				// 数组长度
		{
				delay_us(10);
				pdataR[i]=IIC_Read_Byte();
				delay_us(5);
				IIC_Ack(); //发送ACK  
		}
		delay_us(10);
		pdataR[i] = IIC_Read_Byte();
		delay_us(5);
		IIC_NAck();							// 最后一个字节以nack应答
	
		delay_us(5);
		IIC_Stop();//产生一个停止条件
		return ret;
	
}

/***********************************************************************************************
*函数名称：void I2C_WriteByteNum(uint8_t device_addr, uint8_t *dat, uint8_t length)
*函数功能：IIC写数据
*入口参数：
			device_addr：设备地址
			dat 存放写缓存数组
			length：写取字节个数
*出口参数：
***********************************************************************************************/
uint8_t I2C_WriteByteNum(uint8_t device_addr, uint8_t *dat, uint8_t length)
{	
		uint8_t ack=0, i=0, ret; 
	
    IIC_Start(); 
	
    IIC_Send_Byte(device_addr);
		ack = IIC_Wait_Ack();	
		if (ack != 0)
		{
				ret=ack;
				return ret;
		}
		delay_us(10);
		
		for(i=0; i<length; i++)
		{
				IIC_Send_Byte(dat[i]);     // 发送字节							   
				ack = IIC_Wait_Ack(); 
				delay_us(10);
		}
		IIC_Stop();						// 产生一个停止条件 
		return ret;	
}	


/***********************************************************************************************
*函数名称：void I2C_WriteByteNum(uint8_t device_addr, uint8_t *dat, uint8_t length)
*函数功能：IIC读一个数据
*入口参数：
			device_addr：设备地址
			addr：寄存器地址
*出口参数：返回IIC读取 buffer
***********************************************************************************************/
uint8_t I2C_ReadOneByte(uint8_t addr,uint8_t device_addr)
{	
		uint8_t ack=0; 
		uint8_t ret;
		uint8_t i=0,buffer;
	
//	
//    IIC_SDA=1;//释放SDA总线
//	
//	IIC_SCL=1;
//	delay_us(100);	  	  

	
		//第一阶段
    IIC_Start();	
    IIC_Send_Byte(device_addr);//设备地址
		ack = IIC_Wait_Ack();	
		if (ack != 0)
		{
			ret=ack;
			return ret;
		}
		IIC_Send_Byte(addr);		//寄存器地址
		ack = IIC_Wait_Ack();	
		if (ack != 0)
		{
				ret=ack;
				return ret;
		}	
		IIC_Stop();
	
		
		//第二阶段
		delay_us(100);
		IIC_Start();
		
		IIC_Send_Byte(device_addr+1);//设备地址+1    
		ack = IIC_Wait_Ack();	
		if (ack != 0)
		{
				ret=ack;
				return ret;
		}
		
		delay_us(10);
		buffer=IIC_Read_Byte();	//读数据
		delay_us(5);
		IIC_NAck(); //发送ACK  
		delay_us(5);
	
		IIC_Stop();//产生一个停止条件
		return buffer;	
}
/***********************************************************************************************
*函数名称：void I2C_WriteOneByte(uint8_t device_addr, uint8_t WriteAddr, uint8_t WriteData)
*函数功能：IIC写一个数据
*入口参数：
			device_addr：设备地址
			WriteAddr：寄存器地址
			WriteData：要写的数据
*出口参数：
***********************************************************************************************/
uint8_t I2C_WriteOneByte(uint8_t device_addr, uint8_t WriteAddr, uint8_t WriteData)
{	
		uint8_t ack=0, i=0, ret; 
	
    IIC_Start(); 
	
    IIC_Send_Byte(device_addr);	// 设备地址
		ack = IIC_Wait_Ack();	
		if (ack != 0)
		{
				ret=ack;
				return ret;
		}
		delay_us(10);
	
		IIC_Send_Byte(WriteAddr);     // 寄存器地址							   
		ack = IIC_Wait_Ack();
		delay_us(10); 
	
	
		IIC_Send_Byte(WriteData);     // 发送字节							   
		ack = IIC_Wait_Ack(); 
		delay_us(10);
	
		IIC_Stop();						// 产生一个停止条件 
	
		return ret;	
}


/*****************************************************
*函数名称：void Uart0Mode1(void)
*函数功能：9600波特率
*入口参数：
*出口参数：
*****************************************************/
void Uart0Mode1(void)
{
    /*************** UART0 模式1（波特率：9600）****************/
    SM00 = 0;
    SM10 = 1;
    REN0 = 0;    //串行接收使能位
    RI0 = 0;     //接收中断标志
    TI0 = 0;     //发送中断标志
    
	//TIMER2 作为uart0的波特率时钟源
    TR2 = 0;
    T2MOD = 0x00;/* 定时2中断不使能，不分频 */
    T2CL = 65536 - 52;
    T2CH = 65536 - 52 >> 8;
    TL2 = T2CL;
    TH2 = T2CH;
    TR2 = 1;    //启动定时器2
    RCLK = 1;
    TCLK = 1;	
}

//-----------------------------------------------
void main()
{
    int i, io_flag=0;
    unsigned char dev_val = 0,tk_val = 0,j=0;
    uint8_t dat[0x20]={0};
 
    SCCON = 0x00;//HRC
    HRCON |= 0x80;
    i=10;while(i--)delay(200);
	
    /**************** 模拟IIC管脚配置 ***************/
		P10	 = 1;
		P11	 = 1;
    P10F = 0Xa2;//IIC SCL  
    P11F = 0Xa2;//IIC SDA
		P06F = 7;	//TX
		
		 /****** UART0 模式1（波特率：9600）*******/
    Uart0Mode1();	//P06--TX
    printf("RUN------\r\n");
		
		
		 /****************   初始化配置   ***************/
    IIC_Init();
        
    //test CODE
		dev_val = 0xA0;	//主机发送地址0xA0
        
    while(1)
    {
//		I2C_WriteByteNum(dev_val,dat,10);
//		I2C_WriteOneByte(dev_val, 0x21, 0);
//		dat[0] = I2C_ReadOneByte(0x21, dev_val);
		
//		I2C_ReadByteNum(0x00,dev_val,dat,0x20);
//		printf("\r\n%s999", dat);
		
		dat[0]=I2C_ReadOneByte(0x00,dev_val);
//		printf("\r\nrx：%bx", dat[0]);	
		P12 = ~P12;
//		printf("\r\nrx：%s", dat);		
//		for(i=0;i<10;i++)
//		{
//			dat[i] = 5;
//		}
//		delay(500);
		
//		delay(500);
//		delay(500);
		delay(500);
         
    }
}
