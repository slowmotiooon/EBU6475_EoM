#include "headerfile.h"

void uart_para_send(void)
{
    char str[50];
    sprintf(str, "%d,%d\n", target_speed, (speed_0 + speed_1)/2);
    HAL_UART_Transmit(&huart1, (uint8_t *)str, strlen(str), 50);
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
    if (huart->Instance == USART1)
    {


        HAL_UARTEx_ReceiveToIdle_DMA(&huart1, rx_buffer, sizeof(rx_buffer));
        __HAL_DMA_DISABLE_IT(&hdma_usart1_rx, DMA_IT_HT);
    }
}
