//
// Created by armstrong on 25-4-27.
//

#include "headerfile.h"

int k1_state, k2_state, k3_state, k1_last_state, k2_last_state, k3_last_state;
void key_scan(void) {
    k1_state = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13);
    k2_state = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14);
    k3_state = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_15);

    if (k1_state == 0 && k1_last_state == 1) {
        stop = 1;   //停止
    }

    if (k2_state == 0 && k2_last_state == 1) {
        stop = 0;   //启动
    }

    if (k3_state == 0 && k3_last_state == 1) {
        //target_speed = 300; //低速模式
    }

    k1_last_state = k1_state;
    k2_last_state = k2_state;
    k3_last_state = k3_state;
}