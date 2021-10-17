#ifndef WIFI_H
#define WIFI_H

#include "string.h"

#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
#include "esp_wifi.h"
#include "esp_now.h"

#include "uart.h"

#define DEFAULT_CHANNEL 1
#define maxPayloadSize 245

extern uint8_t targetAddress[];
extern TimerHandle_t adjustChannelTimer;
enum messageType {boot, data, ping};

void wifiSetup();
void adjustChannel();

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
void OnDataRecv(const uint8_t *mac_addr, const uint8_t *data, int len);

#endif