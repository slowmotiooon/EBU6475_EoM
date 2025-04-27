#ifndef PID_H
#define PID_H

extern int target_speed;
extern float med_angle;
extern int target_turn;
extern uint8_t stop;

void control(void);

#endif //PID_H
