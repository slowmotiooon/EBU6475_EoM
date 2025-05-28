//
// Created by slowmotiooon on 29/05/25.
//

#ifndef ABNORMAL_SPIN_H
#define ABNORMAL_SPIN_H

typedef struct
{
    uint8_t state;
    struct abnormal_state* next;
} abnormal_state;

int8_t getAbnormalState(void);

#endif //ABNORMAL_SPIN_H
