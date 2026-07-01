/*********************************************************
*Copyright (C), 2020-2030, 深圳前海维晟智能技术有限公司
*文件名:	ADC.c
*作  者:	
*版  本:	
*日  期:	
*描  述:	
*备  注:     
**********************************************************/
#include "WS51F6240.h"	
#include <stdio.h>
#include "uart1.h"
#include "ADC.h"

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

//-----------------------------------------------
void main()
{
    int i;
    unsigned int k=0;
    
	SCCON = 0x00;//HRC 
    HRCON|=	0x80;//HRC使能
	delay_10ms();    
    

    /****** UART1 模式1（波特率：9600 可调） **************/
    P02F = 6;//RX
    P16F = 6;//TX
    Uart1Mode1();    
   /*************** ADC IO口配置 *************************/		
//	P16F = 4; //AIN0
    P17F = 4; //AIN1
    P21F = 4; //AIN2
    P07F = 4; //AIN3 
    P06F = 4; //AIN4
    P05F = 4; //AIN5
    P04F = 4; //AIN6
    P03F = 4; //AIN7
    P00F = 4; //AIN8
    P10F = 4; //AIN9
    P11F = 4; //AIN10
    P12F = 4; //AIN11
    P15F = 4; //AVRF
    
	P01F = 2; //输出
		
		

    //ADC 初始化
    ADCHS = 0x01;             //通道选择
    AdcInitCFG();           //
    
    setAdcCmpVal(3000);     //设置 ADC 比较功能阈值
    setAdcCmpCfg();         //开ADC的比较器
    EINT5 = 1;	            //ADC 中断开     
	EXIE |= 1;              //uart1中断
    EA = 1;                 //总中断开
    printf("\r\nSTR---%s\r\n", __TIME__);    
    
    printf("Power on register ADCON = %bx, ADCFG = %bx, ADCPC = %bx;\r\n",ADCON, ADCFG, ADCPC);
       
    i = (ADCON&0x30)>>4;   
    if(i == 0)    
        printf("Reference voltage source: Internal 1.6V as reference voltage\r\n");
    else if(i == 1)  
        printf("Reference voltage source: external VDD\r\n");
    else if(i == 2)  
        printf("Reference voltage source: external VREF\r\n");
    else
        printf("Reference voltage source: Keep\r\n");
    
//    printf("ADC 缩放设置：1/4 缩小\r\n");//Zoom settings
//    printf("ADC 缩放设置：1/3 缩小\r\n");
//    printf("ADC 缩放设置：1/4 缩小\r\n");
//    printf("ADC 缩放设置：不缩放\r\n");   
    
    printf("ADC sampling time ATMS(0-7): %bd\r\nZoom settings(0-0xb): 0x%bx\r\n", (ADCFG&0x70)>>4, (ADCFG&0xF));    
    
    printf("channel = %bx;\r\n", ADCHS);    
    
    P00F = 0x81;    //按键
    while(1)
    {        
        if(P00 == 0)//开始转换
        {
            i= 5;while(i--)delay(100);
            if(P00 == 0)
            {
                k=0;
                adc_val = 0;
                ADCON |= 0X80;  
                delay(1);
                
                //不开中断测试时，代码
                while (!(ADCON & ADC_ADCF)) //Wait complete flag  && (j--)
                {
                    delay(100);
                    if(k++>=200)
                    {
                        printf("Conversion timeout error\r\n");   //转换超时
                        break;
                    }
                }
                delay(1);                
                adc_val	= (((u16)ADCDH)<<4)|((u16)ADCDL>>4);
                
                printf("mcu get adcVal = 0x%4X,        %d\r\n", adc_val, adc_val);
                ADCON &= (~ADC_ADCF); //clear flag
                
                i= 10;while(i--)delay(100);
            }
        }
				 	if(ADC_ADCPF == (ADCPC & ADC_ADCPF))	//比较中断
				{
					  printf("ADC Interrupt\r\n"); 
						ADCPC &= (~ADC_ADCPF); //clear flag
						
						P01 = ~P01;  
				}		
    }
}

    
 
    
   
    




