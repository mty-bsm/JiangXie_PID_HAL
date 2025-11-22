#include "MOTOR.h"
void MOTOR_PWMControl(int Speed)
{
	if(Speed>=0)
	{
		HAL_GPIO_WritePin(MOTOR_direction1_GPIO_Port,MOTOR_direction1_Pin,1);
		HAL_GPIO_WritePin(MOTOR_direction2_GPIO_Port,MOTOR_direction2_Pin,0);
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, Speed); 
	}
	else
	{
		HAL_GPIO_WritePin(MOTOR_direction1_GPIO_Port,MOTOR_direction1_Pin,0);
		HAL_GPIO_WritePin(MOTOR_direction2_GPIO_Port,MOTOR_direction2_Pin,1);
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, -Speed); 
	}
}
void MOTOR_Start()
{
	HAL_GPIO_WritePin(MOTOR_direction1_GPIO_Port,MOTOR_direction1_Pin,1);
	HAL_GPIO_WritePin(MOTOR_direction2_GPIO_Port,MOTOR_direction2_Pin,0);
}
void MOTOR_DirectionChange()
{
	HAL_GPIO_TogglePin(MOTOR_direction1_GPIO_Port,MOTOR_direction1_Pin);
	HAL_GPIO_TogglePin(MOTOR_direction2_GPIO_Port,MOTOR_direction2_Pin);
}
int16_t MOTOR_ReadLocation()
{
	return (int16_t)__HAL_TIM_GET_COUNTER(&htim3);
}
int16_t MOTOR_ReadSpeed()
{
	static int16_t location0=0,location1=0;
	location0=location1;
	location1=(int16_t)__HAL_TIM_GET_COUNTER(&htim3);
	return location1-location0;
}
