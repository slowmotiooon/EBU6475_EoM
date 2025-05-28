//
// Created by slowmotiooon on 29/05/25.
//

#include "headerfile.h"

int8_t getAbnormalState(void)
{
    if (target_speed==0 && PWM_out>800 && Roll < 30 && Roll > -30) return 1;
    return 0;
}