#include "headerfile.h"

int32_t motor_counter_1 = 0;
int32_t motor_counter_2 = 0;

int32_t motor_speed_1 = 0;
int32_t motor_speed_2 = 0;

void Motor_Init(void) {
    Motor_SetDirection(0, 1);
    Motor_SetDirection(1, 1);
    HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);
    HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
}

void Motor_SetSpeed(int speed) {
    if (speed > 99) speed = 99;
    if (speed < 0) speed = 0;
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, speed);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, speed);
}

void Motor_GetCounter() {
    motor_counter_1 = (short) __HAL_TIM_GET_COUNTER(&htim2);
    motor_counter_2 = (short) __HAL_TIM_GET_COUNTER(&htim3);
}

void Motor_GetSpeed() {
    motor_speed_1 = (short) __HAL_TIM_GET_COUNTER(&htim2);
    __HAL_TIM_SET_COUNTER(&htim2, 0);
    motor_speed_2 = (short) __HAL_TIM_GET_COUNTER(&htim3);
    __HAL_TIM_SET_COUNTER(&htim3, 0);
}

void Motor_SetDirection(const uint8_t wheel, const uint8_t direction) {
    if (wheel == LEFT_WHEEL) {
        if (direction == FORWARD) {
            HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_1);
            HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
        } else {
            HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
            HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);
        }
    } else {
        if (direction == FORWARD) {
            HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);
            HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);
        } else {
            HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_2);
            HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
        }
    }
}

void Motor_Stop() {
    HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
    HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);
    HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_1);
    HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_2);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim == &htim4) {
        Motor_GetSpeed();
    }
}
