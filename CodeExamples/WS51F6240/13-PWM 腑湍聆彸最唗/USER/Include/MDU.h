#ifndef __MDU_H
#define __MDU_H
#include "WS51F0032.h"
#include <stdio.h>



void Multiplier_Init(void);
void Divider_Init(void);
void LShift_Init(u8 Num);
void RShift_Init(u8 Num);
void Write_Mul_Div(int8_t * dat,u8 len);
void Read_Result(int8_t * dat,u8 len);











#endif