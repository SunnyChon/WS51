#ifndef __Init_H
#define __Init_H
#include "WS51F6240.h"	
#include <stdio.h>

#define IO_OPM    0X02      //0X02输出模式；0x41上拉输入
#define IO_IPM    0x01      //0x41   10K上拉电阻打开

void Timer0_Init(void);
void Timer1_Init(void);
void Timer2_Init(void);
void Timer3_Init(void);

void Int0SetMode0(void);

void Uart0Mode1_Init(void);
void UART0_write(int8_t dat);


#endif