#ifndef GPIO_H
#define GPIO_H

#include "driver/gpio.h"

#define UART0_RTS_PIN 41
#define UART0_DTR_PIN 42
#define UART0_RTS_DTR_PINS ((1ULL<<UART0_RTS_PIN) | (1ULL<<UART0_DTR_PIN))
#define UART1_RTS_PIN 14
#define UART1_DTR_PIN 13
#define UART1_RTS_DTR_PINS ((1ULL<<UART1_RTS_PIN) | (1ULL<<UART1_DTR_PIN))

void gpioSetup();

#endif