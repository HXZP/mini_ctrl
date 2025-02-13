/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LCD_LED_Pin GPIO_PIN_3
#define LCD_LED_GPIO_Port GPIOC
#define KEY1_Pin GPIO_PIN_0
#define KEY1_GPIO_Port GPIOA
#define LCD_CS_Pin GPIO_PIN_4
#define LCD_CS_GPIO_Port GPIOA
#define LCD_A0_Pin GPIO_PIN_4
#define LCD_A0_GPIO_Port GPIOC
#define LCD_RES_Pin GPIO_PIN_5
#define LCD_RES_GPIO_Port GPIOC
#define SD_SWITCH_Pin GPIO_PIN_11
#define SD_SWITCH_GPIO_Port GPIOD
#define W0_Pin GPIO_PIN_1
#define W0_GPIO_Port GPIOD
#define W1_Pin GPIO_PIN_3
#define W1_GPIO_Port GPIOD
#define W2_Pin GPIO_PIN_4
#define W2_GPIO_Port GPIOD
#define CCW_Pin GPIO_PIN_5
#define CCW_GPIO_Port GPIOD
#define PUSH_Pin GPIO_PIN_6
#define PUSH_GPIO_Port GPIOD
#define CW_Pin GPIO_PIN_7
#define CW_GPIO_Port GPIOD
#define KEY2_Pin GPIO_PIN_0
#define KEY2_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
