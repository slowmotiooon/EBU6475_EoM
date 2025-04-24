#include "headerfile.h"

// int32_t motor_counter_1 = 0;
// int32_t motor_counter_2 = 0;

int32_t speed_0 = 0;
int32_t speed_1 = 0;

void Motor_Init(void) {
    Motor_SetDirection(LEFT_WHEEL, FORWARD);
    Motor_SetDirection(RIGHT_WHEEL, FORWARD);
    HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);
    HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
}

// void Motor_GetCounter() {
//     motor_counter_1 = (short) __HAL_TIM_GET_COUNTER(&htim2);
//     motor_counter_2 = (short) __HAL_TIM_GET_COUNTER(&htim3);
// }

void speed_limit(uint32_t *speed)
{
    if (*speed > 839)
    {
        *speed = 839;
    }
    if (*speed < 200)
    {
        *speed = 200;
    }
}

void Motor_SetDirection(const uint8_t wheel, const uint8_t direction) {
    if (wheel == LEFT_WHEEL) {
        if (direction == BACKWARD) {
            HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_1);
            HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
        } else {
            HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
            HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);
        }
    } else {
        if (direction == BACKWARD) {
            HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);
            HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);
        } else {
            HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_2);
            HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
        }
    }
}

void Motor_Stop(void) {
    HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
    HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);
    HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_1);
    HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_2);
}

void GetSpeed(void) {
    speed_1 = -(short) __HAL_TIM_GET_COUNTER(&htim2);
    __HAL_TIM_SET_COUNTER(&htim2, 0);
    speed_0 = (short) __HAL_TIM_GET_COUNTER(&htim3);
    __HAL_TIM_SET_COUNTER(&htim3, 0);
}

void Motor_SetSpeed(int32_t speed0, int32_t speed1)
{
    if (speed0 >= 0)
    {
        Motor_SetDirection(LEFT_WHEEL, FORWARD);
    }
    else
    {
        Motor_SetDirection(LEFT_WHEEL, BACKWARD);
        speed0 = abs(speed0);
    }
    speed_limit((uint32_t *)&speed0);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, speed0);

    if (speed1 >= 0)
    {
        Motor_SetDirection(RIGHT_WHEEL, FORWARD);
    }
    else
    {
        Motor_SetDirection(RIGHT_WHEEL, BACKWARD);
        speed1 = abs(speed1);
    }
    speed_limit((uint32_t *)&speed1);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, speed1);
}


