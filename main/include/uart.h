#ifndef UART_H
#define UART_H

#include "driver/uart.h"
#include "tusb_cdc_acm.h"

#define UART_COUNT 2

void uartSetup();
void uartLoop();

#endif