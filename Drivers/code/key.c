//
// Created by armstrong on 25-4-27.
//

#include "headerfile.h"

int k1_state, k2_state, k3_state, k4_state, k1_last_state, k2_last_state, k3_last_state, k4_last_state;
void key_scan(void) {
    k1_state = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_10);
    k2_state = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_11);
    k3_state = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_12);
    k4_state = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_2);

    if (k1_state == 0 && k1_last_state == 1) {

    }

    if (k2_state == 0 && k2_last_state == 1) {
        stop = 0;   //启动
    }

    if (k3_state == 0 && k3_last_state == 1) {

    }

    if (k4_state == 0 && k4_last_state == 1) {
        stop = 1;   //停止
    }

    k1_last_state = k1_state;
    k2_last_state = k2_state;
    k3_last_state = k3_state;
    k4_last_state = k4_state;
}