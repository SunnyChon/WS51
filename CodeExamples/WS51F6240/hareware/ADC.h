#ifndef __ADC_H
#define __ADC_H

//=============================== ADC配置寄存器 ================================
//  寄存器 ADCON
#define ADC_ADST    0x80 //bit7：ADC 转换开始控制位，写 1 启动转换，转换后硬件自动清 0
#define ADC_ADIE    0x40 //bit6：ADC 中断使能位
#define ADC_VSEL    0x10 //bit5-4：ADC 参考电压选择位
                            //00: 内部 1.6V 作为参考电压
                            //01: 外部 VDD
                            //10: 外部 VREF
                            //11：保留
#define ADC_ACKS    0x00 //bit3-1：时钟分频(0~7)
#define ADC_ADCF	0x01 //bit0：ADC 采样完成标志
   
//	寄存器 ADCFG 	
#define ADC_MODE    0x80 //bit7：ADC 启动转换模式
                            //0：仅软件写 ADST 可启动 ADC 转换
                            //1：软件写 ADST 和 Timer2 计数溢出均可启动 ADC 转换
#define ADC_ATMS	0x70 //bit6-4：ADC 采样时间为 2 的 ATMS 次幂
#define ADC_GAIN	0x03 //bit3-0：ADC 缩放设置				
                
//	寄存器 ADCHS 	
#define ADC_ADCHS   0x00 //bit4-0：ADC 采样通道选择

//	寄存器 ADCDH ADCDL 	（采样转换值）

//==============================ADC比较功能 寄存器
//	寄存器 ADCPC
#define ADC_ADCPE   0x80   //bit7：ADC 的比较器功能使能信号
#define ADC_ADCPIE  0x40   //bit6：ADC 的比较器功能中断使能信号
#define ADC_ADCPPS  0x20   //bit5：ADC 的比较器功能极性选择
                                    //0：大于设定的比较阈值
                                    //1：小于设定的比较阈值
#define ADC_ADCPF   0x01   //bit0：ADC 的比较器功能标志信号
        
//	寄存器 ADCPDH ADCPDL 	（ADC 比较功能阈值）

//	寄存器 ADCBGP
#define ADC_ABGE      //bit7：ADC 内部基准开启使能。当 ADC 使用内部基准作为基准源时，该基准自动开启，否则必须使能 ABGE 才能开启 ADC 内部基准。
#define ADC_ABGC      //bit5-0：ADC 内部基准调整位
//=============================== END ================================


#define ADC_CONFIG_REG          0   //0-不开中断
                                    //1-开中断
                                    //2-开定时器2溢出启动


extern u8 ad_flag;
extern unsigned int adc_val;

void AdCHS(u8 chs);            //通道选择
void AdcInitCFG(void);          //参考基准和缩放配置
void AdcInitCFG_enInt(void);    //开中断
void AdcInitCFG_enIntModeTimer2(void);//开中断开timer2模式

void setAdcCmpVal(u16 val);     //设置 ADC 比较功能阈值
void setAdcCmpCfg(void);        //开启比较器   

#endif