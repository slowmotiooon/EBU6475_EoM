/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "headerfile.h"
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
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for Task_OLED */
osThreadId_t Task_OLEDHandle;
const osThreadAttr_t Task_OLED_attributes = {
  .name = "Task_OLED",
  .stack_size = 400 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal,
};
/* Definitions for Task_CarControl */
osThreadId_t Task_CarControlHandle;
const osThreadAttr_t Task_CarControl_attributes = {
  .name = "Task_CarControl",
  .stack_size = 400 * 4,
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for Task_SR04 */
osThreadId_t Task_SR04Handle;
const osThreadAttr_t Task_SR04_attributes = {
  .name = "Task_SR04",
  .stack_size = 300 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal,
};
/* Definitions for Task_Bluetooth */
osThreadId_t Task_BluetoothHandle;
const osThreadAttr_t Task_Bluetooth_attributes = {
  .name = "Task_Bluetooth",
  .stack_size = 384 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Task_Knob */
osThreadId_t Task_KnobHandle;
const osThreadAttr_t Task_Knob_attributes = {
  .name = "Task_Knob",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityLow,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void AppTask_OLED(void *argument);
void AppTask_CarControl(void *argument);
void AppTask_SR04(void *argument);
void AppTask_Bluetooth(void *argument);
void AppTask_Knob(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of Task_OLED */
  Task_OLEDHandle = osThreadNew(AppTask_OLED, NULL, &Task_OLED_attributes);

  /* creation of Task_CarControl */
  Task_CarControlHandle = osThreadNew(AppTask_CarControl, NULL, &Task_CarControl_attributes);

  /* creation of Task_SR04 */
  Task_SR04Handle = osThreadNew(AppTask_SR04, NULL, &Task_SR04_attributes);

  /* creation of Task_Bluetooth */
  Task_BluetoothHandle = osThreadNew(AppTask_Bluetooth, NULL, &Task_Bluetooth_attributes);

  /* creation of Task_Knob */
  Task_KnobHandle = osThreadNew(AppTask_Knob, NULL, &Task_Knob_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_AppTask_OLED */
/**
  * @brief  Function implementing the Task_OLED thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_AppTask_OLED */
void AppTask_OLED(void *argument)
{
  /* USER CODE BEGIN AppTask_OLED */
  /* Infinite loop */
  for (;;) {
    key_scan();
    OLED_Update();
    vTaskDelay(100);
  }
  /* USER CODE END AppTask_OLED */
}

/* USER CODE BEGIN Header_AppTask_CarControl */
/**
* @brief Function implementing the Task_CarControl thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_AppTask_CarControl */
void AppTask_CarControl(void *argument)
{
  /* USER CODE BEGIN AppTask_CarControl */
  /* Infinite loop */
  for (;;) {
    mpu6500_getdata();
    GetSpeed();
    // control();
    vTaskDelay(5);
  }
  /* USER CODE END AppTask_CarControl */
}

/* USER CODE BEGIN Header_AppTask_SR04 */
/**
* @brief Function implementing the Task_SR04 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_AppTask_SR04 */
void AppTask_SR04(void *argument)
{
  /* USER CODE BEGIN AppTask_SR04 */
  /* Infinite loop */
  for (;;) {
    SR04_GetDistance();
    vTaskDelay(300);
  }
  /* USER CODE END AppTask_SR04 */
}

/* USER CODE BEGIN Header_AppTask_Bluetooth */
/**
* @brief Function implementing the Task_Bluetooth thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_AppTask_Bluetooth */
void AppTask_Bluetooth(void *argument)
{
  /* USER CODE BEGIN AppTask_Bluetooth */
  /* Infinite loop */
  for (;;) {
    uart_para_send();
    if (command_received) {
      if (rx_buffer[0] == 'c') {
        if (rx_buffer[1] == 'f') go_forward();
        else if (rx_buffer[1] == 'b') go_backward();
        else if (rx_buffer[1] == 'l') turn_left();
        else if (rx_buffer[1] == 'r') turn_right();
        else if (rx_buffer[1] == 's') stop_car();
        else if (rx_buffer[1] == 't') turn_straight();
      } else if (rx_buffer[0] == 's') {
        float *p = &med_angle;
        float range = 0;
        if (rx_buffer[1] == '1') p = &med_angle, range = 0.01;
        else if (rx_buffer[1] == '2') p = &vertical_kp, range = 1;
        else if (rx_buffer[1] == '3') p = &vertical_kd, range = 0.01;
        else if (rx_buffer[1] == '4') p = &velocity_kp, range = 0.001;
        else if (rx_buffer[1] == '5') p = &turn_kp, range = 0.01;
        else if (rx_buffer[1] == '6') p = &turn_kd, range = 0.01;
        if (rx_buffer[2] == 'u') *p += range;
        else if (rx_buffer[2] == 'v') *p += range * 5;
        else if (rx_buffer[2] == 'w') *p += range * 10;
        else if (rx_buffer[2] == 'x') *p += range * 100;
        else if (rx_buffer[2] == 'd') *p -= range;
        else if (rx_buffer[2] == 'e') *p -= range * 5;
        else if (rx_buffer[2] == 'f') *p -= range * 10;
        else if (rx_buffer[2] == 'g') *p -= range * 100;
        else if (rx_buffer[2] == 'r') *p = 0;
      }
      command_received = 0;
    }
    vTaskDelay(50);
  }
  /* USER CODE END AppTask_Bluetooth */
}

/* USER CODE BEGIN Header_AppTask_Knob */
/**
* @brief Function implementing the Task_Knob thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_AppTask_Knob */
void AppTask_Knob(void *argument)
{
  /* USER CODE BEGIN AppTask_Knob */
  /* Infinite loop */
  for (;;) {
    get_adc();
    set_speed();
    vTaskDelay(50);
  }
  /* USER CODE END AppTask_Knob */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

