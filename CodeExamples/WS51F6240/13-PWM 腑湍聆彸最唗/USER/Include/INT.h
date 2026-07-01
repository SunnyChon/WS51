#ifndef __INT_H
#define __INT_H
#include "WS51F6240.h"	
/************ ÷–∂œπ‹Ω≈≈‰÷√÷µ ***********/
#define IT_PIN_P00  0X00
#define IT_PIN_P01  0X01
#define IT_PIN_P02  0X02
#define IT_PIN_P03  0X03
#define IT_PIN_P04  0X04
#define IT_PIN_P05  0X05
#define IT_PIN_P06  0X06
#define IT_PIN_P07  0X07

#define IT_PIN_P10  0X08
#define IT_PIN_P11  0X09
#define IT_PIN_P12  0X0A
#define IT_PIN_P13  0X0b
#define IT_PIN_P14  0X0c
#define IT_PIN_P15  0X0d
#define IT_PIN_P16  0X0e
#define IT_PIN_P17  0X0f

#define IT_PIN_P20  0X10
#define IT_PIN_P21  0X11

#define INT_PIN IT_PIN_P01 //P00-P01;P10-P17;P30-P37

void Uart0Mode1_Init(void);
void UART0_write(int8_t dat);
void Int0SetMode0(void);
void Int1SetMode0(void);
void Int2SetMode0(void);





#endif