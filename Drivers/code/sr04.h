
#ifndef SR04_H
#define SR04_H

extern uint16_t count;
extern float distance;
extern uint8_t barrier_flag;

void Delay_us(__IO uint32_t delay);

void SR04_GetDistance();

extern uint8_t barrier_state;
extern uint16_t barrier_distance;
extern uint8_t barrier_flag;
extern uint8_t go_forward_flag, go_backward_flag;

void barrier(void);
void obsAvoid(void);

#endif //SR04_H
