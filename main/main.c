#include "main.h"

void app_main(void)
{
    gpioSetup();
    usbSetup();
    uartSetup();
}