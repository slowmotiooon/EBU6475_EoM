#ifndef HEADERFILE_H
#define HEADERFILE_H

#include "stm32f4xx_hal.h"

#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "spi.h"
#include "dma.h"
#include "adc.h"

#include "motor.h"
#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include "stdlib.h"
#include "math.h"
#include "oled.h"
#include "interface.h"
#include "usart.h"
#include "sr04.h"
#include "mpu6500.h"
#include "bsp_spi.h"
#include "struct_typedef.h"
#include "pid.h"
#include "bluetooth.h"
#include "key.h"
#include "knob.h"
#include "lala.h"

#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

extern uint8_t rx_buffer[50];

extern DMA_HandleTypeDef hdma_usart1_rx;

#endif //HEADERFILE_H
