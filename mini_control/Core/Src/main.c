/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "spi.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint32_t Pin_Data[4];
uint32_t RCC_Clock;

void LCD_Cmd(uint8_t data)
{
	HAL_GPIO_WritePin(A0_GPIO_Port,A0_Pin,0);
	HAL_SPI_Transmit(&hspi1, &data, 1, 1000);
}

void LCD_Dat(uint8_t data)
{
	HAL_GPIO_WritePin(A0_GPIO_Port,A0_Pin,1);
	HAL_SPI_Transmit(&hspi1, &data, 1, 1000);
}
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
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
#if 0	
	HAL_GPIO_WritePin(RES_GPIO_Port,RES_Pin,1);
	HAL_Delay(1);
	HAL_GPIO_WritePin(RES_GPIO_Port,RES_Pin,0);
	HAL_Delay(5);	
	HAL_GPIO_WritePin(RES_GPIO_Port,RES_Pin,1);

	LCD_Cmd(0x11);//sleep out
	HAL_Delay(10);
	
	LCD_Cmd(0x36);
	LCD_Dat(0x05);//左到右 上到下
	
	LCD_Cmd(0x20);//此命令用于从显示反转模式中恢复。
	
	LCD_Cmd(0xb2);
	LCD_Dat(0x0c);
	LCD_Dat(0x0c);
	LCD_Dat(0x00);
	LCD_Dat(0x33);
	LCD_Dat(0x33);
	
	LCD_Cmd(0xb7);
	LCD_Dat(0x35);	
	
	LCD_Cmd(0xbb);//VCOMS Setting
	LCD_Dat(0x35);
	
	LCD_Cmd(0xc0);//LCM Control 
	LCD_Dat(0x2c);	
	
	LCD_Cmd(0xc2);// VDV and VRH command write enable. 
	LCD_Dat(0x01);
	
	LCD_Cmd(0xc3);
	LCD_Dat(0x0b);
	
	LCD_Cmd(0xc4);
	LCD_Dat(0x20);

	LCD_Cmd(0x51);
	LCD_Dat(0xFF);//亮度00-FF
	
	LCD_Cmd(0xc6);
	LCD_Dat(0x1e);//40Hz
	
	LCD_Cmd(0xd0);//Power Control
	LCD_Dat(0xa4);	
	LCD_Dat(0xa1);	
	
	LCD_Cmd(0xe0);//正电压 Gamma 控制
	LCD_Dat(0xd0);
	LCD_Dat(0x00);
	LCD_Dat(0x02);
	LCD_Dat(0x07);
	LCD_Dat(0x0b);
	LCD_Dat(0x1a);
	LCD_Dat(0x31);
	LCD_Dat(0x54);	
	LCD_Dat(0x40);
	LCD_Dat(0x29);
	LCD_Dat(0x12);
	LCD_Dat(0x12);
	LCD_Dat(0x17);
	
	LCD_Cmd(0xe1);//负电压 Gamma 控制
	LCD_Dat(0xd0);
	LCD_Dat(0x00);
	LCD_Dat(0x02);
	LCD_Dat(0x07);
	LCD_Dat(0x05);
	LCD_Dat(0x25);
	LCD_Dat(0x2d);
	LCD_Dat(0x44);	
	LCD_Dat(0x45);
	LCD_Dat(0x1c);
	LCD_Dat(0x18);
	LCD_Dat(0x16);
	LCD_Dat(0x1c);


	LCD_Cmd(0x29);//Display On

	LCD_Cmd(0x2a);
	LCD_Dat(0x00);
	LCD_Dat(0x01);	

	
	LCD_Cmd(0x2b);
	LCD_Dat(0x00);
	LCD_Dat(0x01);		
#endif
  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();  /* Call init function for freertos objects (in freertos.c) */
  MX_FREERTOS_Init();

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
#if 0		
		Pin_Data[0] = HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_5);
		Pin_Data[1] = HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_6);
		Pin_Data[2] = HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_7);
		Pin_Data[3] = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0);
		
		
		LCD_Cmd(0x2a);
		LCD_Dat(0x00);
		LCD_Dat(0x01);	

		
		LCD_Cmd(0x2b);
		LCD_Dat(0x00);
		LCD_Dat(0x01);			
			
			
		HAL_Delay(100);
	
#endif		
//		RCC_Clock = HAL_RCC_GetSysClockFreq();
		
//		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_4,0);
//		HAL_Delay(500);
//		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_4,1);
//		HAL_Delay(500);
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
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
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM8 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM8) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

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

#ifdef  USE_FULL_ASSERT
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
