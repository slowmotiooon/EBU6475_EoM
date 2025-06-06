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
/* Definitions for Taks_ObsAvoid */
osThreadId_t Taks_ObsAvoidHandle;
const osThreadAttr_t Taks_ObsAvoid_attributes = {
  .name = "Taks_ObsAvoid",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for Task_Abnormal */
osThreadId_t Task_AbnormalHandle;
const osThreadAttr_t Task_Abnormal_attributes = {
  .name = "Task_Abnormal",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void AppTask_OLED(void *argument);
void AppTask_CarControl(void *argument);
void AppTask_SR04(void *argument);
void AppTask_Bluetooth(void *argument);
void AppTask_Knob(void *argument);
void AppTask_ObsAvoid(void *argument);
void AppTask_AbnormalDetect(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void configureTimerForRunTimeStats(void);
unsigned long getRunTimeCounterValue(void);

/* USER CODE BEGIN 1 */
/* Functions needed when configGENERATE_RUN_TIME_STATS is on */
__weak void configureTimerForRunTimeStats(void)
{

}

__weak unsigned long getRunTimeCounterValue(void)
{
return 0;
}
/* USER CODE END 1 */

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

  /* creation of Taks_ObsAvoid */
  Taks_ObsAvoidHandle = osThreadNew(AppTask_ObsAvoid, NULL, &Taks_ObsAvoid_attributes);

  /* creation of Task_Abnormal */
  Task_AbnormalHandle = osThreadNew(AppTask_AbnormalDetect, NULL, &Task_Abnormal_attributes);

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
    OLED_Update();
    vTaskDelay(200);
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
    control();
    // Motor_SetSpeed(100, 100);
    vTaskDelay(10);
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
    // uart_para_send();
    bluetooth_control();
    bluetooth_state_scan();
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
    key_scan();
    get_adc();
    set_speed();
    vTaskDelay(50);
  }
  /* USER CODE END AppTask_Knob */
}

/* USER CODE BEGIN Header_AppTask_ObsAvoid */
/**
* @brief Function implementing the Taks_ObsAvoid thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_AppTask_ObsAvoid */
void AppTask_ObsAvoid(void *argument)
{
  /* USER CODE BEGIN AppTask_ObsAvoid */
  /* Infinite loop */
  for(;;) {
  barrier();
    vTaskDelay(100);
  }
  /* USER CODE END AppTask_ObsAvoid */
}

/* USER CODE BEGIN Header_AppTask_AbnormalDetect */
/**
* @brief Function implementing the Task_Abnormal thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_AppTask_AbnormalDetect */
void AppTask_AbnormalDetect(void *argument)
{
  /* USER CODE BEGIN AppTask_AbnormalDetect */
  int8_t states[4] = {0,0,0,0};

  /* Infinite loop */
  for(uint8_t i=0;;i=(i+1)%4)
  {
    states[i] = getAbnormalState();
    if (states[0] && states[1] && states[2] && states[3]) stop = 1;
    vTaskDelay(80);
  }
  /* USER CODE END AppTask_AbnormalDetect */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

