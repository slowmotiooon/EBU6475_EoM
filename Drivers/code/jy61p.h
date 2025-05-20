#ifndef __JY61P_H
#define __JY61P_H

#include "main.h" 

void jy61p_ReceiveData(uint8_t RxData);

extern float Roll,Pitch,Yaw;
extern float Gx, Gy, Gz;

extern uint8_t uart6_receive;

#endif
