#include "timer.h"

void timer(TimerCallbackFunction_t callback, int period_ms)
{
    TimerHandle_t handle = xTimerCreate(NULL, period_ms, pdTRUE, NULL, callback);
    xTimerStart(handle, 0);
    callback(handle);
}