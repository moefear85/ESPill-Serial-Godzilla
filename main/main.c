#include "main.h"

void app_main(void)
{
    uartSetup();
    gpioSetup();
    usbSetup();

    uartLoop();
}