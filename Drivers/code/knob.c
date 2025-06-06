//
// Created by armstrong on 25-4-27.
//
#include "headerfile.h"

uint32_t adc1_value;
uint32_t adc2_value;
uint32_t adc3_value;

uint32_t adc_value[3];

uint16_t battery;

void get_adc(void) {
    HAL_ADC_Start_DMA(&hadc1, adc_value, 3);
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
    if (hadc->Instance == ADC1) {
        adc1_value = adc_value[0];
        adc2_value = adc_value[1];
        adc3_value = adc_value[2];

        battery = adc2_value * 100 / 4095;

        if (barrier_distance_lock == 1)
        {
            barrier_distance = adc3_value * 120 / 4095;
        }
    }
}

void set_speed(void) {
    if (speed_lock == 1)
    {
        float speed = 600 * ((float)adc1_value / 4096);
        target_speed = (int)speed;
    }
}
