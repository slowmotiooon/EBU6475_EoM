//
// Created by armstrong on 25-4-27.
//
#include "headerfile.h"

uint32_t adc1_value;
uint32_t adc2_value;
uint32_t adc3_value;

uint32_t adc_value[3];

void get_adc(void) {
    HAL_ADC_Start_DMA(&hadc1, adc_value, sizeof(adc_value)/sizeof(uint32_t));
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    if (hadc->Instance == ADC1){
        adc1_value = adc_value[0];
        adc2_value = adc_value[1];
        adc3_value = adc_value[2];
    }
}

void set_speed(void) {
    uint32_t speed;
    speed = 600 * (adc1_value / 4096);
    target_speed = speed;
}
