#ifndef __OLED_H__
#define __OLED_H__
//使用 PB8和PB9 I2C1
//x从0到127 y从0到7
//每个字符高8像素，宽6像素
#include "stm32f1xx_hal.h"    
#include <stdarg.h>
extern I2C_HandleTypeDef hi2c1;

void OLED_Init(void);

void OLED_Clear(void);
void OLED_Send(uint8_t*command,uint16_t num);
void OLED_SetPosition(uint8_t y,uint8_t x);
void OLED_ShowChar(uint8_t y,uint8_t x,uint8_t Char);
void OLED_ShowString(uint8_t y,uint8_t x,uint8_t*string);
void OLED_ShowFloat(uint8_t y,uint8_t x,float data);
void OLED_Showint(uint8_t y,uint8_t x,int data);
void OLED_Sprintf(uint8_t y,uint8_t x,const char *format,...);
void OLED_Reverse(void);
#endif
