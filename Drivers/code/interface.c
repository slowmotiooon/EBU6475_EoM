#include "headerfile.h"

uint8_t message[50];
extern int speed;

void OLED_Update(void) {
    sprintf((char *) message, "mot0:%d    ", speed_0);
    OLED_ShowString(1, 1, (char *) message);
    sprintf((char *) message, "mot1:%d    ", speed_1);
    OLED_ShowString(2, 1, (char *) message);
    sprintf((char *) message, "roll: %.1f    ", imu.rol);
    OLED_ShowString(3, 1, (char *) message);
    sprintf((char *) message, "gyrox: %d    ", mpu_data.gx);
    OLED_ShowString(4, 1, (char *) message);
    // sprintf((char *) message, "distance: %.1f  ", distance);
    // OLED_ShowString(4, 1, (char *) message);
}
