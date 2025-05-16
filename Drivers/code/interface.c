#include "headerfile.h"

char message[20];
// extern int speed;

uint8_t show_mode; //0为默认数据界面，1为菜单，2为速度设置界面，3为电机设置界面，4为超声波设置界面，5为PID参数界面
uint8_t select_option = 1;

void oled_show(void) {
    if (show_mode == 0)
    {
        sprintf(message, "        DATA   ");
        OLED_ShowString_small(1, 1, message);
        sprintf(message, "    speed:%d   ", target_speed);
        OLED_ShowString_small(3, 1, message);
        sprintf(message, "    distance:%.1f  ", distance);
        OLED_ShowString_small(4, 1, message);
        sprintf(message, "    roll:%.1f  ", imu.rol);
        OLED_ShowString_small(5, 1, message);
        sprintf(message, "    battery:%d  ", battery);
        OLED_ShowString_small(6, 1, message);
        if (bluetooth_state == 1)
        {
            sprintf(message, "    BT connected   ");
            OLED_ShowString_small(8, 1, message);
        }
        else
        {
            sprintf(message, "    BT disconnected   ");
            OLED_ShowString_small(8, 1, message);
        }
    }
    else if (show_mode == 1)
    {
        sprintf(message, "speed");
        OLED_ShowString_big(1, 5, message);
        sprintf(message, "motor");
        OLED_ShowString_big(2, 5, message);
        sprintf(message, "ultrasonic");
        OLED_ShowString_big(3, 5, message);
        sprintf(message, "pid");
        OLED_ShowString_big(4, 5, message);

        if (select_option == 1)
        {
            sprintf(message, ">>");
            OLED_ShowString_big(1, 2, message);
        }
        else if (select_option == 2)
        {
            sprintf(message, ">>");
            OLED_ShowString_big(2, 2, message);
        }
        else if (select_option == 3)
        {
            sprintf(message, ">>");
            OLED_ShowString_big(3, 2, message);
        }
        else if (select_option == 4)
        {
            sprintf(message, ">>");
            OLED_ShowString_big(4, 2, message);
        }
    }
    else if (show_mode == 2)
    {
        sprintf(message, "     SPEED   ");
        OLED_ShowString_big(1, 1, message);
        sprintf(message, "       %d   ", target_speed);
        OLED_ShowString_big(3, 1, message);
    }
    else if (show_mode == 3)
    {
        sprintf(message, "      MOTOR   ");
        OLED_ShowString_big(1, 1, message);
        if (stop == 1)
        {
            sprintf(message, "       STOP   ");
            OLED_ShowString_big(3, 1, message);
        }
        else
        {
            sprintf(message, "       RUN   ");
            OLED_ShowString_big(3, 1, message);
        }
    }
    else if (show_mode == 4)
    {
        sprintf(message, "    ULTRASON ");
        OLED_ShowString_big(1, 1, message);

    }
    else if (show_mode == 5)
    {
        sprintf(message, "       PID   ");
        OLED_ShowString_big(1, 1, message);
        sprintf(message, "    ver_kp:%.2f   ", vertical_kp);
        OLED_ShowString_small(4, 1, message);
        sprintf(message, "    ver_kd:%.2f   ", vertical_kd);
        OLED_ShowString_small(5, 1, message);
        sprintf(message, "    vel_kp:%.2f   ", velocity_kp);
        OLED_ShowString_small(6, 1, message);
        sprintf(message, "    vel_ki:%.4f    ", velocity_ki);
        OLED_ShowString_small(7, 1, message);
    }
}
