#include "headerfile.h"

#define CPU_FREQUENCY_MHZ    84		// STM32时钟主频

uint16_t count;
float distance;

uint8_t barrier_state = 0;
uint16_t barrier_distance = 20;

void Delay_us(__IO uint32_t delay) {
    int last, curr, val;
    int temp;

    while (delay != 0) {
        temp = delay > 900 ? 900 : delay;
        last = SysTick->VAL;
        curr = last - CPU_FREQUENCY_MHZ * temp;
        if (curr >= 0) {
            do {
                val = SysTick->VAL;
            } while ((val < last) && (val >= curr));
        } else {
            curr += CPU_FREQUENCY_MHZ * 1000;
            do {
                val = SysTick->VAL;
            } while ((val <= last) || (val > curr));
        }
        delay -= temp;
    }
}

void SR04_GetDistance() {
    HAL_GPIO_WritePin(SR04_TRIG_GPIO_Port, SR04_TRIG_Pin, GPIO_PIN_SET);
    Delay_us(12);
    HAL_GPIO_WritePin(SR04_TRIG_GPIO_Port, SR04_TRIG_Pin, GPIO_PIN_RESET);
}

void barrier(void)
{
    // if (go_forward_flag == 1) {
    //     for (int i = 1; i <= 10; i++) {
    //         target_speed = i * 10;
    //         vTaskDelay(10);
    //     }
    //     go_forward_flag = 0;
    // }

    // if (go_backward_flag == 1) {
    //     for (int i = 29; i >= 0; i--) {
    //         target_speed += target_speed > 0 ? -10 : 10;
    //         target_turn -= 3;
    //         vTaskDelay(10);
    //     }
    //     go_backward_flag = 0;
    // }

    if (barrier_state == 1) {
        if (distance < barrier_distance) {
            stop_car();
            vTaskDelay(500);
            turn_speed = 20;
            vTaskDelay(7000);
            go_forward();
            turn_speed = 0;
        }
    }
}

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
