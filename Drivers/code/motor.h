
#ifndef MOTOR_H
#define MOTOR_H

#define FORWARD 0
#define BACKWARD 1
#define LEFT_WHEEL 0
#define RIGHT_WHEEL 1

// extern int32_t motor_counter_1;
// extern int32_t motor_counter_2;

extern int32_t speed_0;
extern int32_t speed_1;

void Motor_Init(void);

void GetSpeed(void);

void Motor_SetSpeed(int32_t speed0, int32_t speed1);

// void Motor_GetCounter();

void Motor_SetDirection(const uint8_t wheel, const uint8_t direction);

void Motor_Stop(void);

#endif //MOTOR_H
