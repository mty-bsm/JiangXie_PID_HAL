/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
  
// light up the blue LED HAL_GPIO_WritePin(TEST_LED_GPIO_Port,TEST_LED_Pin,0);

/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Key.h"
#include "OLED.h"
#include "RP.h"
#include "MOTOR.h"
#include "Serial.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t KeyNum=0;
float Kp=0.8,Ki=0,Kd,Want=0,Real,Out,Err0,Err1,ErrInt=0;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
	
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
	  
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_TIM1_Init();
  MX_ADC2_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  OLED_Init();
  HAL_TIM_Base_Start_IT(&htim1);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
  HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  // OLED_Reverse();
  OLED_Clear();
  // OLED_ShowString(0,0,"KeyNum:");
  OLED_ShowString(0,0,"Kp:");
  OLED_ShowString(1,0,"Ki:");
  OLED_ShowString(2,0,"Kd:");
  // OLED_ShowString(3,0,"ErrInt:");
  OLED_ShowString(4,0,"Want:");
  OLED_ShowString(5,0,"Real:");
  OLED_ShowString(6,0,"Out:");
  //OLED_ShowString(7,0,"Location:");
  MOTOR_Start();
   MOTOR_PWMControl(-100);
  while (1)
  {
    		//按键检测
		// KeyNum=Key_Songshou();
	  //   if(KeyNum!=0)
	  //   {
		//   OLED_ShowChar(0,42,KeyNum+'0');
		//   switch(KeyNum)
		//   {
		// 	  case 1:Want+=10;break;
		// 	  case 2:Want-=10;break;
		// 	  case 3:Want=0;break;
		// 	  default :break;
		//   }
	  //   }
		//更新旋钮数据并显示新数据
		ADC_updata_Data_RP();
		OLED_ShowFloat(0,24,ADC_Data_RP[0]);
		Kp=ADC_Data_RP[0];
	  OLED_ShowFloat(1,24,ADC_Data_RP[1]);
		Ki=ADC_Data_RP[1];
	  OLED_ShowFloat(2,24,ADC_Data_RP[2]);
		Kd=ADC_Data_RP[2];
    Want=(ADC_Data_RP[3]-0.5)*180.0;
		//显示电机状态
		OLED_Sprintf(5,30,"%04.0f",Real);
		OLED_Sprintf(4,30,"%04.0f",Want);
    OLED_Sprintf(6,30,"%04.0f",Out);
//		OLED_Showint(6,54,MOTOR_ReadLocation());
		//串口发消息
		Serial_Sprintf("%04.2f,%04.2f\r\n",Want,Real);

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  // 判断是哪个定时器触发了中断
  static uint16_t count=0;
  if (htim->Instance == TIM1)
  {
	  count++;
	  if(count==20)
	  {
		//PID
		//获取实际值
     Real=MOTOR_ReadSpeed();
		Err0=Err1;
		Err1=Want-Real;
    	if (Ki != 0)
			{
				ErrInt += Err0;
			}
			else
			{
				ErrInt = 0;
			}
		Out=Kp*Err1+Ki*ErrInt+Kd*(Err1-Err0);
		//输出限幅
		if(Out>=100)
		{
			Out=100;
		}
		if(Out<=-100)
		{
			Out=-100;
		}
		//把Out输出，进行调控
		MOTOR_PWMControl((int)Out);
		
		count=0;
	  }
  }
 }
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
