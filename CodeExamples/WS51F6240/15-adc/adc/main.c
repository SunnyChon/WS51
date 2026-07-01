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
    unsigned int eeromsum=0,eeromdat[15] = {0},mindat = 4095,maxdat=0,fc=0,num=0;
    u8 num_cnt=0;
    
    int i;
    unsigned int k=0;
   
	SCCON = 0x00;//HRC 
    HRCON |= 0x80; 

	/*********** UART1 初始化配置(无备选管脚) ***********/
//	P13F=6;//UART1_RX
	P16F=6;//UART1_TX
    Uart1Mode1();    
    
    /*************** ADC IO口配置 *************************/  
//    P16F = 0X4; //AIN0
	
//	  P17F = 0X4; //AIN1
	
//	  P21F = 0X4; //AIN2
//	  P07F = 0X4; //AIN3 
//	  P06F = 0X4; //AIN4
//	  P05F = 0X4; //AIN5
	  P04F = 0X4; //AIN6

//    P00F = 0X4; //AIN8
//    P10F = 0X4; //AIN9
//    P11F = 0X4; //AIN10
//    P12F = 0X4; //AIN11
		
	P03F = 0X4; //AVRF
    
	P01F = 0x81;    //按键
	
    //ADC 初始化
//	PWCON = 0x03;
    ADCHS = 0x06;             //通道选择
//    ADCHS = 0x1c;				//通道选择OP
//    ADCHS = 0x1b;				//通道选择
//	  ADCHS = 0x1d;             //通道选择LDO-vdd
//    PWCON = 0x1f; 			//LDO校准
		if(P01==0)		
		{
			AdcInitCFG_INNER();		//ADC内部参考电压参数配置
			ACBCON = 0;				//ADC校准使能关闭
		}
		
		else   
		{
			AdcInitCFG();       	//ADC外部参考电压参数配置
			ACBCON = 0;				//ADC校准使能关闭
		}

	
	EXIE |= 1;              //uart1中断
    EA = 1;                 //总中断开
    printf("\r\nSTR---%s\r\n", __TIME__);      
	printf("ADCBGP = %bx\r\n", ADCBGP); 	
//    printf("AKDAT = %bd\r\n", AKDAT);   
//    printf("AMDAT = %bd\r\n", AMDAT); 
	printf("ACBCON = %bx\r\n", ACBCON); 
    
    printf("Power on register ADCON = %bx, ADCFG = %bx;\r\n",ADCON, ADCFG);
       
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
	
//    OP_Init(); //OP输入端
    P00F = 0x81;    //按键
    while(1)
    {
        if(P00 == 1)//开始转换
        {
//            i=100;while(i--)delay(100);
            for(i=0;i<15;i++)  //采15个转换值，求平均值
            {
                k=0;
                adc_val = 0;
                ADCON |= 0X80;  
                delay(1);
                
                //不开中断测试时，代码
                while (!(ADCON & 0x01)) //Wait complete flag  && (j--)
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
                
//                printf("mcu get adcVal = 0x%4X,        %d\r\n", adc_val, adc_val);
                ADCON &= (~0x01); //clear flag
                                
                // 采样15个值，保存最大和最小值
                eeromsum = eeromsum+adc_val;
                eeromdat[num_cnt] = adc_val;
                 
                if(mindat > eeromdat[num_cnt])
                    mindat = eeromdat[num_cnt]; 
                if(maxdat < eeromdat[num_cnt])        
                    maxdat = eeromdat[num_cnt]; 
                num_cnt++; 
                    
                if(num_cnt>=15)
                {
                    num_cnt = 0;
                    printf("Current count = %4d;", num);
                    num++;
                    adc_val = eeromsum/15;
                    
                    eeromsum=0; 

                    for(i=0;i<15;i++)
                        eeromsum+=(eeromdat[i]-adc_val)*(eeromdat[i]-adc_val);

                    fc=eeromsum*10/15;
                    
                    printf("min,max,average,fc        %4d,%4d,%4d,%4d\r\n",mindat,maxdat,adc_val,fc);
                    eeromsum = 0;
                    mindat = 4095;
                    maxdat = 0;                    
                }       
            }
            i= 10;while(i--)delay(100);
        }
		
    }


}

    
 
    
   
    




