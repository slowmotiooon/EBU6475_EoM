#include "headerfile.h"

//临时pid

int target_speed = 0;
int target_turn = 0;
int turn_speed = 0;

float med_angle = 1.25; //平衡时角度值偏移量

float vertical_kp = 56 * 0.6; // 0 - 100
float vertical_kd = 3.5 * 0.6; // 0 - 1
float velocity_kp = -0.01; // 0 - -0.01
float velocity_ki; // velocity_kp / 200
float Bias = 0;

// float vertical_kp = 0; // 0 - 100
// float vertical_kd = 0; // 0 - 1
// float velocity_kp = 0; // 0 - -0.01
// float velocity_ki = 0; // velocity_kp / 200

float turn_kp = 1; /*-2.5*/
float turn_kd = -0.2; /* *-0.3*/
uint8_t stop = 0;

float velocity_out, vertical_out, turn_out, PWM_out;

float vertical(float med, float angel, float gyro_x) {
    float temp = vertical_kp * (angel - med) + vertical_kd * gyro_x;
    return temp;
}

float velocity(int target, int encoder_L, int encoder_R) {
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
    encoder_s = encoder_s > 10000 ? 10000 : (encoder_s < (-10000) ? (-10000) : encoder_s);
    if (stop == 1) {
        encoder_s = 0;
    }
    //速度环计算
    float temp = velocity_kp * err_lowout + velocity_ki * encoder_s;
    return temp;
}

// float turn(float gyro_z, int target_turn) {
//     float temp = turn_kp * target_turn + turn_kd * gyro_z;
//     return temp;
// }

float turn(int target_turn, float gyro_z) {
    // if(abs(target_turn - yaw) < 360 - abs(target_turn - yaw)) {
    //     Bias = target_turn - yaw;
    // }
    // else {
    //     Bias = 360 - abs(target_turn - yaw);
    //     if(target_turn - yaw > 0)
    //         Bias *= -1;
    // }
    // Bias *= -1;
    // float temp = turn_kp * Bias + turn_kd * gyro_z;
    return turn_kp * target_turn + turn_kd * gyro_z;
}

void control(void) {
    // float roll = imu.rol;
    // short gyrox = mpu_data.gx;
    // short gyroz = mpu_data.gz;
    float roll = Roll;
    float gyrox = Gx;
    float gyroz = Gz;
    float yaw = Yaw;

    velocity_out = velocity(target_speed, speed_0, speed_1);
    vertical_out = vertical(velocity_out + med_angle, roll, gyrox);
    turn_out = turn(turn_speed, gyroz);

    PWM_out = vertical_out;

    int motor0 = PWM_out - turn_out;
    int motor1 = PWM_out + turn_out;

    if (roll > 50 || roll < -50 || stop == 1) {
        Motor_Stop();
    } else {
        Motor_Start();
        Motor_SetSpeed(motor0, motor1);
    }
}

void go_forward(void) {
    for (int i = 1; i <= 30; i++) {
        target_speed = i * 10;
        vTaskDelay(10);
    }
}

void go_backward(void) {
    for (int i = -1; i >= -30; i--) {
        target_speed = i * 10;
        vTaskDelay(10);
    }
}

void turn_left(void) {
    int target_increment = 20; // 目标增加的角度
    int step = 5; // 每次增加的步长
    for (int i = 0; i <= target_increment; i += step) {
        turn_speed += step;
        vTaskDelay(10); // 延迟以实现平滑过渡
    }
}

void turn_right(void) {
    int target_increment = 20; // 目标减少的角度
    int step = 5; // 每次减少的步长
    for (int i = 0; i <= target_increment; i += step) {
        turn_speed -= step;
        vTaskDelay(10); // 延迟以实现平滑过渡
    }
}

void stop_car(void) {
    for (int i = 29; i >= 0; i--) {
        target_speed += target_speed > 0 ? -10 : 10;
        vTaskDelay(10);
    }
    turn_speed = 0;
}
