#ifndef __RP_H__
#define __RP_H__
#include "stm32f1xx_hal.h"    
#include "main.h"
extern ADC_HandleTypeDef hadc2;
//用的ADC2，常规组，RANK只有1个。通过切换RANK的通道来读不同的旋钮
#define Num_of_RP 4
extern uint32_t ADC_CHANNEL[Num_of_RP];
//最后值在下面这个数组里
extern float ADC_Data_RP[Num_of_RP];
void ADC_updata_Data_RP(void);
#endif
