#include "headerfile.h"

#define CPU_FREQUENCY_MHZ    72		// STM32时钟主频

uint16_t count;
float distance;

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
