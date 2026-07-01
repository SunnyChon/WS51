#include "MDU.h"


void Multiplier_Init(void)
{
	MDUCON &= 0x00;   //MODE :00 乘法运算
//	MDUIDX = 0x87;    //IDXINC：1 读写MDUDAT不递增  MDCIDX：7 MDUDAT索引位第8字节
}

void Divider_Init(void)
{
	MDUCON = 0x40;   //MODE :01 除法运算
}

void LShift_Init(u8 Num)
{
	MDUCON = 0x80 + Num;   //MODE :10 左移位操作+移位次数
}

void RShift_Init(u8 Num)
{
	MDUCON = 0xC0 + Num;   //MODE :11 右移位操作+移位次数
}

void Write_Mul_Div(int8_t * dat,u8 len)
{
	u8 i;
	for(i = 0;i < len;i++)
	{
		MDUIDX = 0x87 - i;
		MDUDAT = *dat;
		dat++;
	}
}

//void Write_Mul_Div(int8_t * dat,u8 len)
//{
//	u8 i;
//	MDUIDX = 0x00;
//	for(i = 0;i < len;i++)
//	{
//		MDUDAT = *dat;
//		dat++;
//	}
//}

void Read_Result(int8_t * dat,u8 len)
{
	u8 i;
	for(i = 0;i < len;i++)
	{
		MDUIDX = 0x87-i;
		*dat = MDUDAT;
		dat++;
	}
}





