#ifndef BLUETOOTH_H
#define BLUETOOTH_H

extern uint8_t command_received;
extern uint8_t bluetooth_state;

void uart_para_send(void);
void bluetooth_control(void);
void bluetooth_state_scan(void);

#endif //BLUETOOTH_H
