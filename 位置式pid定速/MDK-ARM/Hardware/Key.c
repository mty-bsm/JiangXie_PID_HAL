#include "Key.h"
GPIO_TypeDef * Key_Port[Num_of_Key]={K1_GPIO_Port,K2_GPIO_Port,K3_GPIO_Port,K4_GPIO_Port};
uint16_t Key_Pin[Num_of_Key]={K1_Pin,K2_Pin,K3_Pin,K4_Pin};
uint8_t Key_State[Num_of_Key][2]={0};
uint8_t Key_Songshou()
{
//	static uint8_t K1_State_0,K1_State_1,K2_State_0,K2_State_1,K3_State_0,K3_State_1,K4_State_0,K4_State_1;
//	K1_State_0=K1_State_1;K1_State_1=HAL_GPIO_ReadPin(K1_GPIO_Port,K1_Pin);
//	K2_State_0=K2_State_1;K2_State_1=HAL_GPIO_ReadPin(K2_GPIO_Port,K2_Pin);
//	K3_State_0=K3_State_1;K3_State_1=HAL_GPIO_ReadPin(K3_GPIO_Port,K3_Pin);
//	K4_State_0=K4_State_1;K4_State_1=HAL_GPIO_ReadPin(K4_GPIO_Port,K4_Pin);
//	if(K1_State_0==1&&K1_State_1==0)
//	return 1;
//	if(K2_State_0==1&&K2_State_1==0)
//	return 2;
//	if(K3_State_0==1&&K3_State_1==0)
//	return 3;
//	if(K4_State_0==1&&K4_State_1==0)
//	return 4;
//	
//	return 0;
	for(uint8_t i=0;i<Num_of_Key;i++)
	{
		Key_State[i][0]=Key_State[i][1];
		Key_State[i][1]=HAL_GPIO_ReadPin(Key_Port[i],Key_Pin[i]);
		if(Key_State[i][0]==0&&Key_State[i][1]==1)
		{
			return i+1;
		}
	}
	return 0;
}
