#include "Serial.h"
void Serial_Sprintf(const char *format,...)
{	
    char buffer[128];
    va_list args;
    va_start(args, format);
    vsprintf(buffer, format, args);
    va_end(args);
	HAL_UART_Transmit(&huart1,buffer,strlen(buffer),HAL_MAX_DELAY);
}