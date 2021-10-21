#include "gpio.h"

void gpioSetup()
{
    gpio_config_t io_conf =
    {
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = UART1_RTS_DTR_PINS,
    };
    gpio_config(&io_conf);
}