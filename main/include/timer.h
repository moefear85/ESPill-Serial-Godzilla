#ifndef TIMER_H
#define TIMER_H

#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"

void timer(TimerCallbackFunction_t callback, int period_ms);

#endif