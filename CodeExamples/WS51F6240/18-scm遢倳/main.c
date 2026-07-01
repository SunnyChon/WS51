
/*********************************************************
*Copyright (C), 2020-2030, 深圳前海维晟智能技术有限公司
*文件名:	scm唤醒.c
*作  者:	
*版  本:	V1.00
*日  期:	20200418
*描  述:	
*备  注:     
**********************************************************/

#include "WS51F6240.h"
#include <stdio.h>
#include "intrins.h"

static void delay(int i)
{
	long j;
	for(j=0;j<10*i;++j);
}

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

//=============================== SCM 配置寄存器 =========================================

	/*	
	寄存器 XSCON	+XSCON_XLE	 xx  	bit3：LOSC使能信号，该位为高则LOSC打开，
                                                该位为低外设没有使用该时钟则LOSC关闭
					+XSCON_XLSTB xx   	bit0：LOSC稳定标志，为高时表明 LOSC 时钟有效，系统可切换到该时钟
    */

	/*	
	寄存器 SCMCON		+SCMCON_MLE	xx  	bit3：监控外部低速时钟使能， 1 有效
						+SCMCON_IEL	xx   	bit2：监控到外部低速时钟停止中断使能， 1 有效
						+SCMCON_ATL	xx   	bit1：自动重启并使用外部低速时钟 LOSC， 1 有效


	寄存器 SCMFLG		+SCMFLG_LSP	xx  	bit6：该位为 1 时，表示 XOSCL 工作异常，时钟切换到内部时钟
						+SCMFLG_LFD	xx   	bit0：XOSCL 工作异常中断标志，高有效
	**/
//=============================== END ================================
void INT5_isr(void) interrupt 8
{
    //SCM
    if((SCMFLG&0x01) == 0x01)
    {
        SCMFLG &= 0xFE;
        P13 = ~P13;  
    }
}    
/**************************************************************
说明：通过插拔晶振唤醒芯片
***************************************************************/
void main()
{

    int i;
    u8 j=0;
    SCCON = 0x00;//HRC 
	HRCON |= 0x80;
	
#if 1 
/*********************外部losc时钟配置*****************/
	/****************管脚配置	*************/
    P17F = 5;
	P21F = 5;
	
    //使能SCM
    SCMCON = 0x08+0x02+0x04; //
    
    //配置外部时钟使能
    XSCON = 0x08;
    
    //等待外部时钟稳定
    while((XSCON&0x01)==0x0);
		delay_1ms();
	
    //切换系统时钟为外部低速 RC
//	SCCON = 0x40;//LOSC 
#endif	

		/*************** 管脚配置 ****************/	
		P06F = 6;	//TX
		P13F = 2;
		P11F = 2;
		
		
	  /*************** 串口选择 ****************/
    Uart0Mode1();	
    printf("RUN------\r\n");
    

while(1)
{

	if((IDLFL == 0) && (IDLFH == 0))
//		if(STPF == 0)
        {
			printf("sleep\r\n");
            P11=~P11;
			_nop_();
			_nop_();
            P11=~P11;
			
			HRCON &= 0x7f;
			LRCON &= 0x7f;			
			MECON |= 0X80;	//IDLE/STOP 模式下，Flash 进入睡眠模式
	
			
			/*************** 芯片进入休眠 **************/
            PCON = 0X01;    //芯片进入 IDLE 模式
//            PCON = 0X02;    //芯片进入 STOP 模式
			_nop_();
			_nop_();
			_nop_();
			_nop_();
			//等待唤醒
			printf("IDLFL=%bx,IDLFH=%bx,STPF=%bx\r\n",IDLFL,IDLFH,STPF);
        }
    }
	}


    
 
    
   
    




