//
// Created by armstrong on 25-4-27.
//

#include "headerfile.h"

int k1_state, k2_state, k3_state, k4_state, k1_last_state, k2_last_state, k3_last_state, k4_last_state;

uint8_t speed_lock;
uint8_t barrier_distance_lock;

void key_scan(void) {
    k1_state = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_2);
    k2_state = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_11);
    k3_state = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_12);
    k4_state = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_10);

    if (k1_state == 0 && k1_last_state == 1) {
        __HAL_TIM_SetCounter(&htim4, 0);
        OLED_Clear();
        if (show_mode == 0) {
            show_mode = 1;
        }
        else if (show_mode == 1)
        {
            select_option--;
            if (select_option == 0)
            {
                select_option = 1;
                show_mode = 0;
            }
        }
        else if (show_mode == 4)
        {
            select_option--;
            if (select_option == 0)
            {
                select_option = 4;
                show_mode = 1;
            }
        }
        else if (show_mode == 7)
        {
            select_barrier_option --;
            if (select_barrier_option == 0)
            {
                show_mode = 4;
                select_barrier_option = 1;
                barrier_distance_lock = 0;
            }
        }
        else
        {
            speed_lock = 0;
            if (show_mode == 2 || show_mode == 3 || show_mode == 5 || show_mode == 6)
            {
                show_mode = 1;
            }
            else if (show_mode == 8)
            {
                show_mode = 4;
            }
        }
    }

    if (k2_state == 0 && k2_last_state == 1) {
        __HAL_TIM_SetCounter(&htim4, 0);
        OLED_Clear();
        if (show_mode == 0) {
            show_mode = 1;
        }
        else if (show_mode == 1)
        {
            select_option++;
            if (select_option >= 5)
            {
                show_mode = 4;
                select_option = 1;
            }
        }
        else if (show_mode == 4)
        {
            select_option++;
            if (select_option >= 2)
            {
                select_option = 2;
            }
        }
        else if (show_mode == 7)
        {
            select_barrier_option ++;
            if (select_barrier_option == 3)
            {
                select_barrier_option = 2;
            }
        }
    }

    if (k3_state == 0 && k3_last_state == 1) {
        __HAL_TIM_SetCounter(&htim4, 0);
        OLED_Clear();
        if (show_mode == 0) {
            show_mode = 1;
        }
        else if (show_mode == 1)
        {
            if (select_option == 1)
            {
                show_mode = 2;
            }
            else if (select_option == 2)
            {
                show_mode = 3;
            }
            else if (select_option == 3)
            {
                show_mode = 5;
            }
            else if (select_option == 4)
            {
                show_mode = 6;
            }
        }
        else if (show_mode == 2)
        {
            if (speed_lock == 1)
            {
                speed_lock = 0;
            }
            else
            {
                speed_lock = 1;
            }
        }
        else if (show_mode == 3)
        {
            if (stop == 1)
            {
                stop = 0;
            }
            else
            {
                stop = 1;
            }
        }
        else if (show_mode == 4)
        {
            if (select_option == 1)
            {
                show_mode = 7;
                select_barrier_option = 1;
            }
            else if (select_option == 2)
            {
                show_mode = 8;
            }
        }
        else if (show_mode == 7)
        {
            if (select_barrier_option == 1)
            {
                if (barrier_state == 1)
                {
                    barrier_state = 0;
                }
                else
                {
                    barrier_state = 1;
                }
            }
            else if (select_barrier_option == 2)
            {
                if (barrier_distance_lock == 1)
                {
                    barrier_distance_lock = 0;
                }
                else
                {
                    barrier_distance_lock = 1;
                }
            }
        }
    }

    if (k4_state == 0 && k4_last_state == 1) {
        if (show_mode == 0 || show_mode == 9)
        {
            if (stop == 0)
            {
                stop = 1;   //停止
            }
            else
            {
                stop = 0;   //运行
            }
        }
        else if (show_mode == 1 || show_mode == 4 )
        {
            stop = 1;
        }
    }

    k1_last_state = k1_state;
    k2_last_state = k2_state;
    k3_last_state = k3_state;
    k4_last_state = k4_state;
}