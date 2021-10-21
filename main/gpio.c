#include "gpio.h"

void gpioSetup()
{
    gpio_config_t io_conf;

    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = UART0_RTS_DTR_PINS;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;

    io_conf.pin_bit_mask = UART1_RTS_DTR_PINS;

    gpio_config(&io_conf);
}