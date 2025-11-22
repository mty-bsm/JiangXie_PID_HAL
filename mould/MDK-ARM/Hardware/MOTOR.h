#ifndef __MOTOR_H__
#define __MOTOR_H__
#include "stm32f1xx_hal.h"    
#include "main.h"
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
void MOTOR_Start(void);
void MOTOR_PWMControl(int Speed);//-100到100
void MOTOR_DirectionChange(void);
int16_t MOTOR_ReadSpeed(void);
int16_t MOTOR_ReadLocation(void);
#endif
