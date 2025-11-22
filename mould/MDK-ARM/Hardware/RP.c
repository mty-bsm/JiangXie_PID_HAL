#include "RP.h"
uint32_t ADC_CHANNEL[Num_of_RP]={ADC_CHANNEL_2,ADC_CHANNEL_3,ADC_CHANNEL_4,ADC_CHANNEL_5};
//最后值在下面这个数组里
float ADC_Data_RP[Num_of_RP]={0};
void ADC_Change_Only_RANK(uint8_t Channel)
{
  ADC_ChannelConfTypeDef sConfig = {0};
	
  sConfig.Channel = ADC_CHANNEL[Channel];
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_55CYCLES_5;
  if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
}
float ADC_ReadRP(uint8_t Channel)
{
	ADC_Change_Only_RANK(Channel);
	HAL_ADC_Start(&hadc2);
	HAL_ADC_PollForConversion(&hadc2,HAL_MAX_DELAY);
	uint32_t ADC_DR=HAL_ADC_GetValue(&hadc2);
	float temp=ADC_DR/4095.0;
	return temp;
}
void ADC_updata_Data_RP()
{
	for(uint8_t i=0;i<Num_of_RP;i++)
	{
		ADC_Data_RP[i]=ADC_ReadRP(i);
	}
}
