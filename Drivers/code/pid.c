#include "headerfile.h"

//临时pid

int target_speed = 600;
int target_turn;

float med_angle = 4.04; //平衡时角度值偏移量

//float vertical_kp = 43; // 0 - 100
//float vertical_kd = 1.26 * 0.75; // 0 - 1
//float velocity_kp = -0.015; // 0 - -0.01
float vertical_kp = 98 * 0.6; // 0 - 100
float vertical_kd = 2.45 * 0.6; // 0 - 1
float velocity_kp = -0.045; // 0 - -0.01
float velocity_ki; // velocity_kp / 200
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
    velocity_ki = velocity_kp / 200;
    int err, err_lowout;
    //计算偏差值
    err = (encoder_L + encoder_R) / 2 - target;
    //低通滤波
    err_lowout = (1 - a) * err + a * err_lowout_last;
    err_lowout_last = err_lowout;
    //积分
    encoder_s += err_lowout;
    //积分限幅
    encoder_s = encoder_s > 500 ? 500 : (encoder_s < (-500) ? (-500) : encoder_s);
    if (stop == 1)
    {
        encoder_s = 0;
        stop = 0;
    }
    //速度环计算
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
