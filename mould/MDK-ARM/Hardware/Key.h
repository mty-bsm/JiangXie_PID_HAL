#ifndef __KEY_H__
#define __KEY_H__
#include "stm32f1xx_hal.h"    
#include "main.h"
//修改下面这个数量，还有Key.c上面的两个数组
#define Num_of_Key 4 
//非阻塞，放中断函数里用。间隔20ms最好
//没松手返回0，松手返回i
uint8_t Key_Songshou(void);
#endif
