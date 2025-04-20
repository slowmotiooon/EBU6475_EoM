#ifndef HEADERFILE_H
#define HEADERFILE_H

#include "stm32f4xx_hal.h"

#include "tim.h"
#include "usart.h"
#include "gpio.h"

#include "motor.h"
#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include "oled.h"
#include "interface.h"
#include "iic.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "mpu6050.h"
#include "usart.h"

extern float pitch, roll, yaw;

#endif //HEADERFILE_H
