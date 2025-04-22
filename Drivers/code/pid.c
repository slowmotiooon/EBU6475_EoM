#include "headerfile.h"

//临时pid

int target_speed;
int target_turn;

float med_angle;

float vertical_kp;
float vertical_kd;
float velocity_kp;
float velocity_ki;
float turn_kp;
float turn_kd;
uint8_t stop;

int vertical(float med, float angel, float gyro_x)
{
    int temp = vertical_kp * (angel - med) + vertical_kd * gyro_x;
    return temp;
}

int velocity(int target, int encoder_L, int encoder_R)
{
    static int err_lowout_last, encoder_s;
    static float a = 0.7;
    int err, err_lowout, temp;
    err = (encoder_L + encoder_R) / 2 - target;
    err_lowout = (1 - a) * err + a * err_lowout_last;
    err_lowout_last = err_lowout;
    encoder_s += err_lowout;
    encoder_s = encoder_s > 20000 ? 20000 : (encoder_s < (-20000) ? (-20000) : encoder_s);
    if (stop == 1)
    {
        encoder_s = 0;
        stop = 0;
    }
    temp = velocity_kp * err + velocity_ki * encoder_s;
    return temp;
}

int turn(float gyro_z, int target_turn)
{
    int temp = turn_kp * target_turn + turn_kd * gyro_z;
    return temp;
}

void control(void)
{
    float pitch = imu.pit;
    short gyroy = mpu_data.gy;
    short gyroz = mpu_data.gz;

    int velocity_out = velocity(target_speed, speed_0, speed_1);
    int vertical_out = vertical(velocity_out + med_angle, pitch, gyroy);
    int turn_out = turn(gyroz, target_turn);

    int PWM_out = vertical_out;

    int motor0 = PWM_out - turn_out;
    int motor1 = PWM_out + turn_out;

    Motor_SetSpeed(motor0, motor1);
}
