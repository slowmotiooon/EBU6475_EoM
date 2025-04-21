#include "headerfile.h"

uint8_t message[50];
extern int speed;

void OLED_Update(void) {
    sprintf((char *) message, "pitch: %.1f   ", imu.pit);
    OLED_ShowString(1, 1, (char *) message);
    sprintf((char *) message, "roll: %.1f    ", imu.rol);
    OLED_ShowString(2, 1, (char *) message);
    sprintf((char *) message, "yaw: %.1f    ", imu.yaw);
    OLED_ShowString(3, 1, (char *) message);
    sprintf((char *) message, "dist: %.2f   ", distance);
    OLED_ShowString(4, 1, (char *) message);
}
