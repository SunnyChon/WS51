/*********************************************************
*Copyright (C), 2020-2030, 深圳前海维晟智能技术有限公司
*文件名:	IIC.c
*作  者:	
*版  本:	
*日  期:	
*描  述:	
*备  注:     
**********************************************************/
#include "WS51F6240.h"
#include <stdio.h>

//I2CFLG标志位
#define BUSIDLE 0x80
#define RXNAK 0x40
#define IF_LSTARB 0x20
#define IF_RXSTA 0x10
#define IF_RXSTP 0x08
#define IF_TXDAT 0x04
#define IF_RXDAT 0x02
#define IF_RXADR 0x01

unsigned char ic_num=0,ic_dat[6]={0x37,0x01},iic_val=0,stop_flag=0;

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
unsigned char dat0;
unsigned char Rx_flag=0;
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
        Rx_flag = 1;
    }		
}
void i2c_trdata(void) interrupt 5
{
    EA = 0;
    if(IF_RXSTA == (I2CFLG&IF_RXSTA))   //start
    {
        I2CFLG &= ~IF_RXSTA;
        if(ic_num == 0)
        {
            I2CTXD  = 0x37;   //0x37
            I2CFLG &= (~IF_TXDAT);
            ic_num=1;
        }
    }
    
    if(IF_TXDAT == (I2CFLG&IF_TXDAT))
    {
        I2CFLG &= (~IF_TXDAT);
        if(ic_num == 1)
        {
            ic_num = 2;
            I2CFLG  = 0x0;
            
            
            I2CCON  |= 0x1<<2;  //STOP  IIC
        }
        
    }
//    if(IF_RXSTP == (I2CFLG&IF_RXSTP))   //stop
//    {
//        I2CFLG &= ~IF_RXSTP;
//        
//        if(ic_num == 2)
//        {
//            stop_flag = 1;
//            delay(1);
//            
//            I2CTXD  = 0x01;  
//            I2CCON  |= (0x1<<3);    //start tx 
//        }
//    }
//     
//    if(IF_RXDAT == (I2CFLG&IF_RXDAT))   //rx_flag
//    {
//        iic_val = I2CRXD;
//        I2CCON  |= 0x1<<2;  //STOP  IIC
//        
//        I2CFLG &= ~IF_RXDAT;
//        
////        I2CCON  |= 0x1<<2;  //STOP  IIC
//        ic_num = 3;
//    }
    
    
    EA = 1;
}

uint8_t I2C_ReadByteNum(uint8_t addr,uint8_t device_addr, uint8_t *dat, uint8_t num)
{	
	uint8_t ack=0,step=0,ret=0; 
    uint16_t tim=0;
    
    
    I2CFLG = 0; //请标志
    //IIC_Send_Byte(device_addr);	
    I2CTXD  = device_addr;          //0x00 填写设备(device_addr);	
    I2CCON  |= (0x1<<3);    //IIC_Start(); 
    
    while(1)
    {         
        if(IF_TXDAT == (I2CFLG&IF_TXDAT))
        {            
            if(step == 0)
            {
                I2CTXD  = addr;   //0x37
                I2CCON  |= 0x1<<2;  //STOP  IIC
				step=1;
            }
            
            I2CFLG &= (~IF_TXDAT);			
			
			//超时/出错退出
			if(RXNAK == (I2CFLG&RXNAK))
			{
				ret=2;
				I2CCON  |= 0x1<<2;  //STOP  IIC
				I2CFLG = 0;
				return ret;
			}
        }
        
        if(IF_RXSTP == (I2CFLG&IF_RXSTP))   //stop
        {
            if(step==1)
            {    
//                delay_us(348);//STOP发送后,需要加一点延时,才能发送
                delay_us(40);
                I2CTXD  = device_addr+1; 
                I2CCON  |= (0x1<<3);    //start tx 
            }
            I2CFLG &= ~IF_RXSTP;
        }
        
        if(IF_RXDAT == (I2CFLG&IF_RXDAT))   //rx_flag
        {
            *dat = I2CRXD;
            
            if((--num) == 0)
            {   
                I2CCON  |= 0x1<<2;  //STOP  IIC
				I2CFLG &= ~IF_RXDAT;
                return 0;
            }
            dat++;
            I2CFLG &= ~IF_RXDAT;
        }
                //仲载丢失
        if(IF_LSTARB == (I2CFLG&IF_LSTARB))
        {
			ret = 1;
            I2CFLG &= ~IF_LSTARB;       
            return ret;	//1
        } 
        
	}
}


uint8_t I2C_ReadByteNumRestr(uint8_t addr,uint8_t device_addr, uint8_t *dat, uint8_t num)
{	
	uint8_t ack=0, step=0, ret=0; 
    uint16_t tim=0;
    
    
    I2CFLG = 0; //请标志
    //IIC_Send_Byte(device_addr);	
    I2CTXD  = device_addr;          //0x00 填写设备(device_addr);	
    I2CCON  |= (0x1<<3);    //IIC_Start(); 
    
    while(1)
    {
//        if(IF_RXSTA == (I2CFLG&IF_RXSTA))   //start
//        {
//            I2CFLG &= ~IF_RXSTA;
//        }
         
//		//send: start + device_addr + regAdd + restart + (device_addr+1) + rx_dat + stop
//        if(IF_TXDAT == (I2CFLG&IF_TXDAT))
//        {            
//			if(step==0)
//			{
//				I2CTXD  = addr;   //0x37
//                I2CCON  |= (0x1<<3);    //start tx 
//			}
//			else if(step==1)
//			{
//				delay_us(40);
//                I2CTXD  = device_addr+1; 
//			}
//			
//			step++;
//			I2CFLG &= (~IF_TXDAT);

//			//超时/出错退出
//			if(RXNAK == (I2CFLG&RXNAK))
//			{
//				ret=2;
//				I2CCON  |= 0x1<<2;  //STOP  IIC
//				I2CFLG = 0;
//				return ret;
//			}
//            
//        }
        
		//send: start + device_addr + TxDat0123_regAdd + restart + (device_addr+1) + rx_dat + stop
        if(IF_TXDAT == (I2CFLG&IF_TXDAT))
        {            
			if(step==0)
			{
				I2CTXD  = addr;   //0x37
			}
			else if(step==1)
			{
				I2CTXD  = addr+1;   //0x37
			}
			else if(step==2)
			{
				I2CTXD  = addr+2;   //0x37
			}
			else if(step==3)
			{
				I2CTXD  = addr+3;   //0x37
                I2CCON  |= (0x1<<3);    //start tx 
			}
			else if(step==4)
			{
				delay_us(40);
                I2CTXD  = device_addr+1; 
			}
			
			step++;
			I2CFLG &= (~IF_TXDAT);
			
			
			//超时/出错退出
			if(RXNAK == (I2CFLG&RXNAK))
			{
				ret=2;
				I2CCON  |= 0x1<<2;  //STOP  IIC
				I2CFLG = 0;
				return ret;
			}
            
        }
        
        if(IF_RXDAT == (I2CFLG&IF_RXDAT))   //rx_flag
        {
            *dat = I2CRXD;
            
            if((--num) == 0)
            {   
                I2CCON  |= 0x1<<2;  //STOP  IIC
				I2CFLG &= ~IF_RXDAT;
                return 0;
            }
            dat++;
            I2CFLG &= ~IF_RXDAT;
        }
                //仲载丢失
        if(IF_LSTARB == (I2CFLG&IF_LSTARB))
        {
			ret=1;
            I2CFLG &= ~IF_LSTARB;         
            return ret;
        } 
        
	}
}

uint8_t I2C_WriteByteNum(uint8_t device_addr, uint8_t *dat, uint8_t length)
{	
	uint8_t ret=0, cnt=0; 
    uint16_t tim=0;
    
    I2CFLG = 0; //请标志	
    I2CTXD  = device_addr;          //0x00 填写设备(device_addr);	
    I2CCON  |= (0x1<<3);    //IIC_Start(); 
//    P10 = 1;
	P11=1;
    while(1)
    {
        if(IF_RXSTA == (I2CFLG&IF_RXSTA))   //start
        {
            I2CFLG &= ~IF_RXSTA;
        }
         
        if(IF_TXDAT == (I2CFLG&IF_TXDAT))
        {
			I2CTXD  = dat[cnt];   //
			cnt++;
			if(cnt>=10)
			{
				P13 = 0;    //重载丢失测试
			}
			//发送完退出
			if(cnt >= length)
			{
				I2CCON  |= 0x1<<2;  //STOP  IIC
				I2CFLG &= (~IF_TXDAT);
				I2CFLG = 0;
				return 0;
			}
			
            I2CFLG &= (~IF_TXDAT);
			
			
			//超时/出错退出
			if(RXNAK == (I2CFLG&RXNAK))
			{
				ret = 2;
				P11 = 0;
				I2CCON  |= 0x1<<2;  //STOP  IIC
				
				I2CFLG = 0;
				return ret;
			}
        }
        //仲载丢失
        if(IF_LSTARB == (I2CFLG&IF_LSTARB))
        {
			ret=1;
            I2CFLG &= ~IF_LSTARB;
            I2CFLG = 0;
            return ret;
        }        
        
	}
}

/*****************************************************
*函数名称：void I2C_Init(void)
*函数功能：IIC配置初始化
*入口参数：
*出口参数：
*****************************************************/
void I2C_Init(void)
{
	/*********************************** IIC 配置寄存器 ***********************************
	/*	
	寄存器 I2CCON		+I2CE	0x80	bit7：I2C 模块使能位， 1 有效
						+I2CIE	0x40 	bit6：I2C 中断使能位， 1 有效
						+STAIE	0x20 	bit5：总线出现 START 信号，中断使能信号
						+STPIE	0x10 	bit4：总线出现 STOP 信号，中断使能信号
						+STA	0x08	bit3：发送 START 信号
						+STP	0x04	bit2：发送 STOP 信号
						+I2CKD	0x00	bit1-0：I2C 时钟分频选择寄存器
											00： I2C 模块时钟Fiic选择内部 16MHz 高速时钟
											01： I2C 模块时钟Fiic选择内部 16MHz 高速时钟/2
											10： I2C 模块时钟Fiic选择内部 16MHz 高速时钟/4
											11： I2C 模块时钟Fiic选择内部 16MHz 高速时钟/8
	
	寄存器 I2CCON		+I2CCKD 0x00    bit6-0：(127~0)
										I2C 作为 master 输出数据频率选择 Fiic/(I2CCKD + 8)
	
	寄存器 I2CFLG标志位	BUSIDLE 	0x80 总线状态标志（只读）
						RXNAK 		0x40 总线接收响应标志（只读）
						IF_LSTARB 	0x20 I2C 发送的数据和接收到的数据不一致时出现总线丢失，高有效，写 0 清
						IF_RXSTA 	0x10 总线接收到 START 信号
						IF_RXSTP 	0x08 总线接收到 STOP 信号
						IF_TXDAT 	0x04 当 I2C 为主机时表明已发送一个字节数据并接收到响应标志
						IF_RXDAT 	0x02 接收一个字节数据完成
						IF_RXADR 	0x01 I2C 作为从机正确接收到从机地址
	**/
	
	/* 配置 IIC 时钟频率 119K */
//    I2CCON = 0x03;//Fi2c_CLK====== 16M   16M/2   16M/4  16M/8
//    I2CFG1 = 0x7f;  //Fi2c/(I2CFG1<6:0>+8) 
    //127+8  
    //00_ff:2M~ 119K ok
    //01_ff:1M~ 59K  
    //02_ff:500K~ 29K  
    //03_ff:250L~ 最慢 14K 
    //最大: 00_00: 2M
    
    
    I2CCON = 0x00;//Fi2c_CLK====== 16M
    I2CFG1 = 0xff;  //Fi2c/(I2CFG1<6:0>+8) 
    
    
    I2CFLG  = 0x0;		//清标志
    I2CCON  |= (0x1<<7);    //MODE en
//    I2CCON  |= (0x1<<6);  //interrupt en
//    I2CCON  &= ~(0x1<<7);   
    I2CCON  &= ~(0x1<<6);	//不开中断
    
//    I2CCON  |= (0x1<<5);  //START INT EN 中断使能
//    I2CCON  |= (0x1<<4);  //STOP INT EN
    I2CCON  &= ~(0x1<<5);  //不开 START INT EN
    I2CCON  &= ~(0x1<<4);  //不开 STOP INT EN
    
}


/**************************************************************
功能说明：IIC发送接收数据
	配置：SCL时钟频率119K，IIC中断关闭，从机设备地址dev_val
		  管脚悬空需要加外部上拉，或打开内部上拉
	1、6132主从模式都不支持混合模式(restart),6232支持混合模式
	2、主机回复NAK发送STOP，需要注意清RX标志位置
	   要先填写发stop再清RX标志，才能发出stop，和主机回NAK
	3、Restart的发送：需要在准备发送最后一笔数据的中断里面填写发送Start，
	读设备地址数据需要在上一次的数据发送结束的中断里面发生填写读地址数据。	 
	4、stop前会发送最后一次填写的TX_Dat数据
	5、用P30P31作为IIC时，需要将P33P34配置为非IIC模式
	6、stop后发送Start，要加一点延时（否则start发不出去）

***************************************************************/
#define HOSE_SEND_NUM 		10
#define HOSE_RECEIVE_NUM 	10
//-----------------------------------------------
void main()
{
    int i;
    unsigned char dev_val = 0;
    uint8_t datS[HOSE_SEND_NUM]={0};
	uint8_t datR[HOSE_RECEIVE_NUM]={0};
 
    SCCON = 0x00;//HRC 
    HRCON |= 0x80;
    
    /**************** IIC管脚配置 ***************/    
    P13F = 0;//
    P14F = 0;//
    P02F = 0XA5;//IIC SCL-----M4  
    P16F = 0XA5;//IIC SDA-----E4
    
    /****** UART0 模式1（波特率：9600 可调）**************/
    P07F = 6;//RX
    P06F = 6;//TX
    Uart0Mode1();
	printf("RUN------\r\n");
    
    P10F = 0X82;
    P11F = 0X82;
    P13F = 0X82;
    P13 = 1;
    for(i=0;i<10;i++)
    {
       P10 = ~P10; 
       delay(500);
    }
    P10 = 0;
    
    /*************** IIC 初始化配置 ****************/
	I2C_Init();		//IIC 寄存器配置
	dev_val = 0xA0;	//主机发送设备地址0xA0
	
	// 主机发送数据 
	for(i=0;i<HOSE_SEND_NUM;i++)
	{
		datS[i]=i+0x55;	//0123......
	}			
	for(i=0;i<HOSE_RECEIVE_NUM;i++)
	{
		datR[i]=0;	//清数组
	}	  
    ES0 = 1;	/* UART0 中断开 */
    EA = 1;     
    while(1)
    {
       P10 = ~P10; 
        if(BUSIDLE == (I2CFLG&BUSIDLE))   //总线空闲
        {
            I2C_WriteByteNum(dev_val,datS,HOSE_SEND_NUM);
            delay(100);//STOP发送后,需要加一点延时,才能发送
            P13 =1;
//			I2C_ReadByteNum(0x00,dev_val,datR,HOSE_RECEIVE_NUM);
            delay(100);//STOP发送后,需要加一点延时,才能发送
//			I2C_ReadByteNumRestr(0x00,dev_val,datR,HOSE_RECEIVE_NUM);
			delay(500);       
            printf("HOSE-r:");
//            for(i=0;i<HOSE_RECEIVE_NUM;i++)
//            {
//                printf("%c", datR[i]);	
//            }  
            for(i=0;i<HOSE_SEND_NUM;i++)
            {
                printf("%c", datS[i]);	
            }  
            printf("\r\n");
        }
		
		delay(500);
		delay(500);
		delay(500);
		delay(500);
		delay(500);
         
    }
    
   


}

    
 
    
   
    




