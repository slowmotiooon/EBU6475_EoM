#include "headerfile.h"

//临时pid

int target_speed;
int target_turn;

float med_angle; //平衡时角度值偏移量

float vertical_kp;
float vertical_kd;
float velocity_kp;
float velocity_ki;
float turn_kp;
float turn_kd;
uint8_t stop;

float velocity_out, vertical_out, turn_out, PWM_out;

float vertical(float med, float angel, float gyro_x)
{
    float temp = vertical_kp * (angel - med) + vertical_kd * gyro_x;
    return temp;
}

float velocity(int target, int encoder_L, int encoder_R)
{
    static int err_lowout_last, encoder_s;
    static float a = 0.7;
    int err, err_lowout;
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
    float temp = velocity_kp * err_lowout + velocity_ki * encoder_s;
    return temp;
}

float turn(int gyro_z, int target_turn)
{
    float temp = turn_kp * target_turn + turn_kd * gyro_z;
    return temp;
}

void control(void)
{
    float roll = imu.rol;
    short gyrox = mpu_data.gx;
    short gyroz = mpu_data.gz;

    velocity_out = velocity(target_speed, speed_0, speed_1);
    vertical_out = vertical(velocity_out + med_angle, roll, gyrox);
    turn_out = turn(gyroz, target_turn);

    PWM_out = vertical_out;

    int motor0 = PWM_out - turn_out;
    int motor1 = PWM_out + turn_out;

    Motor_SetSpeed(motor0, motor1);
}
