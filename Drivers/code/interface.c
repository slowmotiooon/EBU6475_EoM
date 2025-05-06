#include "headerfile.h"

char message[20];
// extern int speed;

uint8_t show_mode; //0为默认数据界面，1为菜单，2为速度设置界面，3为电机设置界面，4为超声波设置界面
uint8_t select_option = 1;

void OLED_Update(void) {
    if (show_mode == 0)
    {
        sprintf(message, "      DATA   ");
        OLED_ShowString(1, 1, message);
        sprintf(message, "  speed:%d   ", target_speed);
        OLED_ShowString(2, 1, message);
        sprintf(message, "  distance:%.1f  ", distance);
        OLED_ShowString(3, 1, message);
        sprintf(message, "  roll:%.1f  ", imu.rol);
        OLED_ShowString(4, 1, message);
    }
    else if (show_mode == 1)
    {
        sprintf(message, "speed");
        OLED_ShowString(1, 5, message);
        sprintf(message, "motor");
        OLED_ShowString(2, 5, message);
        sprintf(message, "ultrasonic");
        OLED_ShowString(3, 5, message);

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
        sprintf(message, "    ULTRASON ");
        OLED_ShowString(1, 1, message);

    }
}
