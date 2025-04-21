#include "headerfile.h"

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == SR04_ECHO_Pin) {
        if (HAL_GPIO_ReadPin(SR04_ECHO_GPIO_Port, SR04_ECHO_Pin) == GPIO_PIN_SET) {
            __HAL_TIM_SET_COUNTER(&htim5, 0);
            HAL_TIM_Base_Start(&htim5);
        } else {
            HAL_TIM_Base_Stop(&htim5);
            count = __HAL_TIM_GET_COUNTER(&htim5);
            distance = (float) count / 1000000 * 346 * 100 / 2;
        }
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim == &htim4) {
        Motor_GetSpeed();
        mpu6500_getdata();
    }
}
