#ifndef PID_H
#define PID_H

extern int target_speed;
extern float med_angle;
extern int target_turn;
extern int turn_speed;
extern uint8_t stop;

extern float vertical_kp;
extern float vertical_kd;
extern float velocity_kp;
extern float velocity_ki;
extern float turn_kp;
extern float turn_kd;
extern float Bias;

void control(void);

void go_forward(void);

void go_backward(void);

void turn_left(void);

void turn_big_left(void);

void turn_right(void);

void turn_big_right(void);

void stop_car(void);

void turn_straight(void);

#endif //PID_H
