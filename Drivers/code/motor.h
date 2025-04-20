
#ifndef MOTOR_H
#define MOTOR_H

#define FORWARD 0
#define BACKWARD 1
#define LEFT_WHEEL 0
#define RIGHT_WHEEL 1

extern int32_t motor_counter_1;
extern int32_t motor_counter_2;

extern int32_t motor_speed_1;
extern int32_t motor_speed_2;

void Motor_Init(void);

void Motor_SetSpeed(int speed);

void Motor_GetSpeed();

void Motor_GetCounter();

void Motor_SetDirection(const uint8_t wheel, const uint8_t direction);

void Motor_Stop();

#endif //MOTOR_H
