#ifndef UART_H
#define UART_H

#include "driver/uart.h"
#include "tusb_cdc_acm.h"

void uartSetup();
void uartLoop();

#endif