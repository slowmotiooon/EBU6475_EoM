#include "headerfile.h"

void mpu6500_init()
{
    mpu_device_init();
    init_quaternion();
}

void mpu6500_getdata()
{
    mpu_get_data();
    imu_ahrs_update();
    imu_attitude_update();
}
