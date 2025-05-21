
#ifndef SR04_H
#define SR04_H

extern uint16_t count;
extern float distance;
extern uint8_t barrier_flag;

void Delay_us(__IO uint32_t delay);

void SR04_GetDistance();

extern uint8_t barrier_state;
extern uint16_t barrier_distance;

void barrier(void);

#endif //SR04_H
