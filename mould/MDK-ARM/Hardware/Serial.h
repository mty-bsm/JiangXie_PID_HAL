#ifndef __SERIAL_H__
#define __SERIAL_H__
#include "stm32f1xx_hal.h"    
#include "main.h"
#include <stdarg.h>
extern UART_HandleTypeDef huart1;
void Serial_Sprintf(const char *format,...);
#endif
