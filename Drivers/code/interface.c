#include "headerfile.h"

char message[20];
// extern int speed;

uint8_t show_mode = 0; //0为默认数据界面，1为菜单，2为速度设置界面，3为电机设置界面，4为菜单第二栏，5为蓝牙界面，6为电量界面，7为超声波设置界面，8为PID参数界面
uint8_t select_option = 1;
uint8_t select_barrier_option = 1;

void OLED_Update(void) {
    if (show_mode == 0)
    {
        sprintf(message, "      DATA   ");
        OLED_ShowString(1, 1, message);
        sprintf(message, "speed:%d  ", target_speed);
        OLED_ShowString(2, 1, message);
        sprintf(message, "bar:%d", barrier_state);
        OLED_ShowString(2, 10, message);
        sprintf(message, "rol:%.0f ", Roll);
        OLED_ShowString(3, 1, message);
        sprintf(message, "ya:%.0f ", Yaw);
        OLED_ShowString(3, 9, message);
        sprintf(message, "  distance:%.1f  ", distance);
        OLED_ShowString(4, 1, message);
    }
    else if (show_mode == 1)
    {
        sprintf(message, "speed");
        OLED_ShowString(1, 5, message);
        sprintf(message, "motor");
        OLED_ShowString(2, 5, message);
        sprintf(message, "bluetooth");
        OLED_ShowString(3, 5, message);
        sprintf(message, "battery");
        OLED_ShowString(4, 5, message);

        if (select_option == 1)
        {
            sprintf(message, ">>");
            OLED_ShowString(1, 2, message);
        }
        else if (select_option == 2)
        {
            sprintf(message, ">>");
            OLED_ShowString(2, 2, message);
        }
        else if (select_option == 3)
        {
            sprintf(message, ">>");
            OLED_ShowString(3, 2, message);
        }
        else if (select_option == 4)
        {
            sprintf(message, ">>");
            OLED_ShowString(4, 2, message);
        }
    }
    else if (show_mode == 2)
    {
        sprintf(message, "     SPEED   ");
        OLED_ShowString(1, 1, message);
        sprintf(message, "       %d   ", target_speed);
        OLED_ShowString(3, 1, message);
    }
    else if (show_mode == 3)
    {
        sprintf(message, "      MOTOR   ");
        OLED_ShowString(1, 1, message);
        if (stop == 1)
        {
            sprintf(message, "       STOP   ");
            OLED_ShowString(3, 1, message);
        }
        else
        {
            sprintf(message, "       RUN   ");
            OLED_ShowString(3, 1, message);
        }
    }
    else if (show_mode == 4)
    {
        sprintf(message, "ultrasonic");
        OLED_ShowString(1, 5, message);
        sprintf(message, "pid");
        OLED_ShowString(2, 5, message);

        if (select_option == 1)
        {
            sprintf(message, ">>");
            OLED_ShowString(1, 2, message);
        }
        else if (select_option == 2)
        {
            sprintf(message, ">>");
            OLED_ShowString(2, 2, message);
        }
    }
    else if (show_mode == 5)
    {
        sprintf(message, "    BLUETOOTH ");
        OLED_ShowString(1, 1, message);
        if (bluetooth_state == 1)
        {
            sprintf(message,"    CONNECTED   ");
            OLED_ShowString(3, 1, message);
        }
        else
        {
            sprintf(message,"  DISCONNECTED ");
            OLED_ShowString(3, 1, message);
        }

    }
    else if (show_mode == 6)
    {
        sprintf(message, "     BATTERY ");
        OLED_ShowString(1, 1, message);
        sprintf(message, "       %d%%  ", battery);
        OLED_ShowString(3, 1, message);
    }
    else if (show_mode == 7)
    {
        sprintf(message, "    ULTRASON ");
        OLED_ShowString(1, 1, message);
        if (barrier_state == 1)
        {
            sprintf(message, "ON ");
            OLED_ShowString(3, 7, message);
        }
        else
        {
            sprintf(message, "OFF");
            OLED_ShowString(3, 7, message);
        }
        sprintf(message, "%dcm ", barrier_distance);
        OLED_ShowString(4, 7, message);

        if (select_barrier_option == 1)
        {
            sprintf(message, ">>");
            OLED_ShowString(3, 3, message);
        }
        else if (select_barrier_option == 2)
        {
            sprintf(message, ">>");
            OLED_ShowString(4, 3, message);
        }
    }
    else if (show_mode == 8)
    {
        // sprintf(message, "       PID   ");
        // OLED_ShowString(1, 1, message);
        sprintf(message, "  ver_kp:%.2f   ", vertical_kp);
        OLED_ShowString(1, 1, message);
        sprintf(message, "  ver_kd:%.2f   ", vertical_kd);
        OLED_ShowString(2, 1, message);
        sprintf(message, "  vel_kp:%.2f   ", velocity_kp);
        OLED_ShowString(3, 1, message);
        sprintf(message, "  vel_ki:%.4f  ", velocity_ki);
        OLED_ShowString(4, 1, message);

    }
    else if (show_mode == 9)
    {
        sprintf(message, "roll:%.2f   ", Roll);
        OLED_ShowString(1, 1, message);
        sprintf(message, "gx:%.2f   ", Gx);
        OLED_ShowString(2, 1, message);
        sprintf(message, "stop:%d   ", stop);
        OLED_ShowString(3, 1, message);
        sprintf(message, "yaw:%.2f   ", Yaw);
        OLED_ShowString(4, 1, message);

    }
    else if (show_mode == 10)
    {
        sprintf(message, "speed0:%d   ", speed_0);
        OLED_ShowString(1, 1, message);
        sprintf(message, "speed1:%d   ", speed_1);
        OLED_ShowString(2, 1, message);
    }
}
