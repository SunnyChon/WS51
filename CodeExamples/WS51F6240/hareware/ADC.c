/*********************************************************
*Copyright (C), 2020-2030, 深圳前海维晟智能技术有限公司
*文件名:	adc.c
*作  者:	
*版  本:	
*日  期:	
*描  述:	
*备  注:     
**********************************************************/
#include "WS51F6240.h"	
#include "ADC.h"


//=============================== ADC 配置寄存器 =========================================
	/*	
	寄存器 ADCON		+ADC_ADST	0x80	bit7：ADC 转换开始控制位，写 1 启动转换，转换后硬件自动清 0
	+ADC_ADIE	0x40 	bit6：ADC 中断使能位，写0关闭ADC中断（可产生中断标志，不产生中断请求），写1使能ADC中断
						+ADC_VSEL	0x10 	bit5-4：ADC 参考电压选择位
                                                        00: 内部 1.6V 作为参考电压
                                                        01: 外部 VDD
                                                        10: 外部 VREF
                                                        11：保留
						+ADC_ACKS	0x0E 	bit3-1：时钟分频(0~7)不分频~128分频
						+ADC_ADCF	0x01	bit0：ADC 采样完成标志
    
	寄存器 ADCFG        +ADC_MODE	0x80	bit7：ADC 启动转换模式：
                                                        0：仅软件写 ADST 可启动 ADC 转换
                                                        1：软件写 ADST 和 Timer2 计数溢出均可启动 ADC 转换
						+ADC_ATMS	0x70 	bit6-4：ADC 采样时间为 2 的 ATMS 次幂，1~128个时钟周期
						+ADC_GAIN	0x0b	bit3-0：ADC 缩放设置 ：0x00,1/4缩放;
																									 0x01,1/3缩放;
																									 0x02,1/2缩放;
																									 0x03,不缩放;
																									 0x04,内部增益系数确定*2;
																									 0x05,内部增益系数确定*4;
																									 0x06,内部增益系数确定*6;
		  																						 0x07,内部增益系数确定*8;
																									 0x08,内部增益系数确定*10;
																									 0x09,内部增益系数确定*12;
																									 0x0a,内部增益系数确定*15;
																									 0x0b,内部增益系数确定*20;
																									 其他，保留
																									 
																									 
    寄存器 ADCHS 	    bit4-0：ADC 采样通道选择

    寄存器 ADCDH ADCDL 	（采样转换值）
    
    //====== ADC比较功能 寄存器
    寄存器 ADCPC
                        +ADC_ADCPE   0x80       bit7：ADC 的比较器功能使能信号
                        +ADC_ADCPIE  0x40       bit6：ADC 的比较器功能中断使能信号
                        +ADC_ADCPPS  0x20       bit5：ADC 的比较器功能极性选择
                                                        0：大于设定的比较阈值
                                                        1：小于设定的比较阈值
                        +ADC_ADCPF   0x01       bit0：ADC 的比较器功能标志信号
        
    寄存器 ADCPDH ADCPDL 	（ADC 比较功能阈值）

    寄存器 ADCBGP
                        +ADC_ABGE           bit7：ADC 内部基准开启使能。当 ADC 使用内部基准作为基准源时，该基准自动开启，否则必须使能 ABGE 才能开启 ADC 内部基准。
                        +ADC_ABGC           bit5-0：ADC 内部基准调整位    
	**/
//=============================== END ================================

    
/*****************************************************
*函数名称：void AdcInitCFG(void)
*函数功能：基准和缩放配置
*入口参数：
*出口参数：
*****************************************************/
void AdcInitCFG(void)
{
    ADCON = 0;
    ADCFG = 0;
    ADCON = ADC_VSEL|ADC_ACKS; 
	ADCFG = ADC_ATMS|ADC_GAIN;       
}
/*****************************************************
*函数名称：void AdcInitCFG_INNER(void)
*函数功能：基准和缩放配置
*入口参数：
*出口参数：
*****************************************************/
void AdcInitCFG_INNER(void)
{
    ADCON = 0;
    ADCFG = 0;
    ADCON = ADC_ACKS; 
	ADCFG = ADC_ATMS|ADC_GAIN;       
} 
/*****************************************************
*函数名称：void AdcInitCFG(void)
*函数功能：基准和缩放配置       开中断
*入口参数：
*出口参数：
*****************************************************/
void AdcInitCFG_enInt(void)
{
    ADCON = 0;
    ADCFG = 0;
    ADCON = ADC_VSEL|ADC_ACKS|ADC_ADIE;  
	ADCFG = ADC_ATMS|ADC_GAIN;      
}
 
/*****************************************************
*函数名称：void AdcInitCFG(void)
*函数功能：基准和缩放配置       开中断 timer2和写启动转换模式
*入口参数：
*出口参数：
*****************************************************/
void AdcInitCFG_enIntModeTimer2(void)
{
    ADCON = 0;
    ADCFG = 0;
    ADCON = ADC_VSEL|ADC_ACKS|ADC_ADIE;  
	ADCFG = ADC_ATMS|ADC_GAIN|ADC_MODE;      
}

/*****************************************************
*函数名称：void AdcCHs(u8 chs)
*函数功能：
*入口参数：
*出口参数：
*****************************************************/
void AdcCHs(u8 chs)
{
    ADCHS = chs;   //XXX
}

/*****************************************************
*函数名称：void setAdcCMP(u16 val)
*函数功能：设置 ADC 比较功能阈值
*入口参数：
*出口参数：
*****************************************************/
void setAdcCmpVal(u16 val)
{
    ADCPDH = val>>4;    
    ADCPDL = (val&0xf)<<4;        
}

/*****************************************************
*函数名称：void setAdcCmpCfg()
*函数功能：设置 ADC 比较功能阈值
*入口参数：
*出口参数：
*****************************************************/
void setAdcCmpCfg(void)
{
    
    //====== ADC比较功能 寄存器
//    寄存器 ADCPC
//                        +ADC_ADCPE   0x80       bit7：ADC 的比较器功能使能信号
//                        +ADC_ADCPIE  0x40       bit6：ADC 的比较器功能中断使能信号
//                        +ADC_ADCPPS  0x20       bit5：ADC 的比较器功能极性选择
//                                                        0：大于设定的比较阈值
//                                                        1：小于设定的比较阈值
//                        +ADC_ADCPF   0x01       bit0：ADC 的比较器功能标志信号
    ADCPC = 0;
    ADCPC = ADC_ADCPE+ADC_ADCPPS;     //+ADC_ADCPIE
}



u8 ad_flag=0;
unsigned int adc_val = 0;
void ADC_Isr() interrupt 8
{
    if(ADC_ADCF == (ADCON & ADC_ADCF))
    {
        ADCON &= (~ADC_ADCF); //clear flag
//        adc_val	= (((u16)ADCDH)<<4)|((u16)ADCDL>>4);
//        ad_flag = 1;
				P01 = ~P01;
    }
}
