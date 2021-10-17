#ifndef USB_H
#define USB_H

#include "wifi.h"
#include "uart.h"
#include "tinyusb.h"
#include "tusb_cdc_acm.h"

#include "gpio.h"

#define USBBUFSIZE 1024

void usbSetup();
void usbCallback(int itf, cdcacm_event_t *event);
void lineCodingCallback(int itf, cdcacm_event_t *event);
void tinyusb_cdc_line_state_changed_callback(int itf, cdcacm_event_t *event);

#endif