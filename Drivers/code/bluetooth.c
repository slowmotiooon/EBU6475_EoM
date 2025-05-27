#include "headerfile.h"

uint8_t command_received = 0;
uint8_t bluetooth_state;

void uart_para_send(void) {
    char str[50];
    sprintf(str, "%d,%d\n", target_speed, (speed_0 + speed_1) / 2);
    // sprintf(str, "%.2f,%.2f\n", imu.rol, med_angle);
    HAL_UART_Transmit(&huart1, (uint8_t *) str, strlen(str), 50);
}

void bluetooth_state_scan(void) {
    bluetooth_state = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);
    if (bluetooth_state == 0)
    {
        target_speed = 0;
    }
}

void bluetooth_control(void) {
    if (command_received) {
        if (rx_buffer[0] == 'c') {
            if (rx_buffer[1] == 'f') go_forward();
            else if (rx_buffer[1] == 'b') go_backward();
            else if (rx_buffer[1] == 'l') turn_left();
            else if (rx_buffer[1] == 'm') turn_big_left();
            else if (rx_buffer[1] == 'n') turn_big_right();
            else if (rx_buffer[1] == 'r') turn_right();
            else if (rx_buffer[1] == 's') stop_car();
            else if (rx_buffer[1] == 't') {
                if (barrier_state == 0) {
                    barrier_state = 1;
                }
                else {
                    barrier_state = 0;
                }
            }
        } else if (rx_buffer[0] == 's') {
            float *p = &med_angle;
            float range = 0;
            if (rx_buffer[1] == '1') p = &med_angle, range = 0.01;
            else if (rx_buffer[1] == '2') p = &vertical_kp, range = 1;
            else if (rx_buffer[1] == '3') p = &vertical_kd, range = 0.01;
            else if (rx_buffer[1] == '4') p = &velocity_kp, range = 0.001;
            else if (rx_buffer[1] == '5') p = &turn_kp, range = 0.01;
            else if (rx_buffer[1] == '6') p = &turn_kd, range = 0.01;
            if (rx_buffer[2] == 'u') *p += range;
            else if (rx_buffer[2] == 'v') *p += range * 5;
            else if (rx_buffer[2] == 'w') *p += range * 10;
            else if (rx_buffer[2] == 'x') *p += range * 100;
            else if (rx_buffer[2] == 'd') *p -= range;
            else if (rx_buffer[2] == 'e') *p -= range * 5;
            else if (rx_buffer[2] == 'f') *p -= range * 10;
            else if (rx_buffer[2] == 'g') *p -= range * 100;
            else if (rx_buffer[2] == 'r') *p = 0;
        }
        command_received = 0;
    }
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size) {
    if (huart->Instance == USART1) {
        command_received = 1;

        HAL_UARTEx_ReceiveToIdle_DMA(&huart1, rx_buffer, sizeof(rx_buffer));
        __HAL_DMA_DISABLE_IT(&hdma_usart1_rx, DMA_IT_HT);
    }
}
