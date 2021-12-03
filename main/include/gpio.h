#ifndef GPIO_H
#define GPIO_H

#include "driver/gpio.h"

extern const uint8_t UART_RX [];
extern const uint8_t UART_TX [];
extern const uint8_t UART_RTS[];
extern const uint8_t UART_CTS[];
extern const uint8_t UART_DTR[];
extern const uint8_t UART_DSR[];

void gpioSetup();

#endif