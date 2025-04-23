#include "headerfile.h"

uint8_t message[50];
extern int speed;

void OLED_Update(void) {
    // sprintf((char *) message, "pitch: %.1f   ", imu.pit);
    // OLED_ShowString(1, 1, (char *) message);
    sprintf((char *) message, "roll: %.1f    ", imu.rol);
    OLED_ShowString(2, 1, (char *) message);
    // sprintf((char *) message, "gyrox: %d    ", mpu_data.ax);
    // OLED_ShowString(3, 1, (char *) message);
    sprintf((char *) message, "gyroy: %d   ", mpu_data.ay);
    OLED_ShowString(4, 1, (char *) message);
}
