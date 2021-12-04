#include "gpio.h"

//default uart0 RX:44, TX:43
const uint8_t UART_RX[] ={ 7,11};
const uint8_t UART_TX[] ={ 8,12};
const uint8_t UART_DTR[]={ 9,13};
const uint8_t UART_RTS[]={10,14};
const uint8_t UART_DSR[]={ 15,17};
const uint8_t UART_CTS[]={ 16,18};

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