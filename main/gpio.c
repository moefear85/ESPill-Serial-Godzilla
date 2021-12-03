#include "gpio.h"

const uint8_t UART_RX[]={0,11};
const uint8_t UART_TX[]={0,12};
const uint8_t UART_DTR[]={42,13};
const uint8_t UART_RTS[]={41,14};
const uint8_t UART_DSR[]={0,17};
const uint8_t UART_CTS[]={0,18};

#define UART0_RTS_DTR ((1ULL<<UART_RTS[0]) | (1ULL<<UART_DTR[0]))
#define UART1_RTS_DTR ((1ULL<<UART_RTS[1]) | (1ULL<<UART_DTR[1]))

void gpioSetup()
{
    gpio_config_t io_conf =
    {
        .mode = GPIO_MODE_OUTPUT,
    };
    io_conf.pin_bit_mask=UART0_RTS_DTR;
    gpio_config(&io_conf);
    io_conf.pin_bit_mask=UART1_RTS_DTR;
    gpio_config(&io_conf);
}