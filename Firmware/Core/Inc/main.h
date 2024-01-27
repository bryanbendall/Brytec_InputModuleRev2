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
#include "stm32g4xx_hal.h"

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
#define Can1Silent_Pin GPIO_PIN_13
#define Can1Silent_GPIO_Port GPIOC
#define TLE94112_EN_Pin GPIO_PIN_0
#define TLE94112_EN_GPIO_Port GPIOA
#define PowerSwitchStatus_Pin GPIO_PIN_1
#define PowerSwitchStatus_GPIO_Port GPIOA
#define Memory_Hold_Pin GPIO_PIN_2
#define Memory_Hold_GPIO_Port GPIOA
#define Memory_Wp_Pin GPIO_PIN_3
#define Memory_Wp_GPIO_Port GPIOA
#define Memory_SS_Pin GPIO_PIN_4
#define Memory_SS_GPIO_Port GPIOA
#define L9966_Rst_Pin GPIO_PIN_6
#define L9966_Rst_GPIO_Port GPIOC
#define SPI_SS_L9966_Pin GPIO_PIN_8
#define SPI_SS_L9966_GPIO_Port GPIOA
#define L9966_Sync_Pin GPIO_PIN_9
#define L9966_Sync_GPIO_Port GPIOA
#define L9966_Int_Pin GPIO_PIN_10
#define L9966_Int_GPIO_Port GPIOA
#define User_Led_Pin GPIO_PIN_15
#define User_Led_GPIO_Port GPIOA
#define SPI2_SS_TLE94112_Pin GPIO_PIN_4
#define SPI2_SS_TLE94112_GPIO_Port GPIOB
#define Can2Silent_Pin GPIO_PIN_7
#define Can2Silent_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
