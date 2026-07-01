#ifndef __UART0_H
#define __UART0_H

void Uart0Mode1(void);  //9600

void putBinary(unsigned int number);//将一个int型数据的二进制形式正序，倒叙打印输出
void vcan_sendware(u16 *wareaddr, unsigned int waresize);    


#endif