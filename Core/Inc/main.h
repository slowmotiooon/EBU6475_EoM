/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BLUE_STATE_Pin GPIO_PIN_13
#define BLUE_STATE_GPIO_Port GPIOC
#define knob3_Pin GPIO_PIN_0
#define knob3_GPIO_Port GPIOC
#define BUTTON4_Pin GPIO_PIN_2
#define BUTTON4_GPIO_Port GPIOC
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define knob1_Pin GPIO_PIN_4
#define knob1_GPIO_Port GPIOA
#define knob2_Pin GPIO_PIN_1
#define knob2_GPIO_Port GPIOB
#define SPI_NS_Pin GPIO_PIN_10
#define SPI_NS_GPIO_Port GPIOB
#define Key1_Pin GPIO_PIN_13
#define Key1_GPIO_Port GPIOB
#define Key2_Pin GPIO_PIN_14
#define Key2_GPIO_Port GPIOB
#define Key3_Pin GPIO_PIN_15
#define Key3_GPIO_Port GPIOB
#define SR04_ECHO_Pin GPIO_PIN_11
#define SR04_ECHO_GPIO_Port GPIOA
#define SR04_ECHO_EXTI_IRQn EXTI15_10_IRQn
#define SR04_TRIG_Pin GPIO_PIN_12
#define SR04_TRIG_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define BUTTON1_Pin GPIO_PIN_10
#define BUTTON1_GPIO_Port GPIOC
#define BUTTON3_Pin GPIO_PIN_11
#define BUTTON3_GPIO_Port GPIOC
#define BUTTON2_Pin GPIO_PIN_12
#define BUTTON2_GPIO_Port GPIOC
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define BLUE_TX_Pin GPIO_PIN_6
#define BLUE_TX_GPIO_Port GPIOB
#define BLUE_RX_Pin GPIO_PIN_7
#define BLUE_RX_GPIO_Port GPIOB
#define OLED_SDA_Pin GPIO_PIN_8
#define OLED_SDA_GPIO_Port GPIOB
#define OLED_SCL_Pin GPIO_PIN_9
#define OLED_SCL_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
