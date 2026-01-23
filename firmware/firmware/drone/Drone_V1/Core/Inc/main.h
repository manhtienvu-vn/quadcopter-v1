/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "stm32f4xx_hal.h"

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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LF_LED2_Pin GPIO_PIN_2
#define LF_LED2_GPIO_Port GPIOE
#define LED_Pin GPIO_PIN_13
#define LED_GPIO_Port GPIOC
#define LB_LED1_Pin GPIO_PIN_4
#define LB_LED1_GPIO_Port GPIOA
#define LB_LED2_Pin GPIO_PIN_5
#define LB_LED2_GPIO_Port GPIOA
#define RB_LED2_Pin GPIO_PIN_14
#define RB_LED2_GPIO_Port GPIOE
#define RB_LED1_Pin GPIO_PIN_15
#define RB_LED1_GPIO_Port GPIOE
#define BUZZER_Pin GPIO_PIN_11
#define BUZZER_GPIO_Port GPIOD
#define RF_LED1_Pin GPIO_PIN_10
#define RF_LED1_GPIO_Port GPIOC
#define RF_LED2_Pin GPIO_PIN_11
#define RF_LED2_GPIO_Port GPIOC
#define LF_LED1_Pin GPIO_PIN_1
#define LF_LED1_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
