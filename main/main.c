/* TODO
1- Make the remote (espnow) output uart reconfigure speed depending on CDC speed selection
2- Make the remote (espnow) scan for AP channel & update espnow, otherwise no communication unless by chance both channels are same
*/

#include "main.h"

void app_main(void)
{
    uartSetup();
    gpioSetup();
    wifiSetup();
    usbSetup();

    adjustChannelTimer = xTimerCreate(NULL, 5000, true, NULL, adjustChannel);
    xTimerStart(adjustChannelTimer, 0);
    adjustChannel();

    uartLoop();
}