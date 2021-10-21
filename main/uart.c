#include "uart.h"

static QueueHandle_t uart1_queue;

void uartSetup()
{
    uart_config_t uart_config
    {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .stop_bits = UART_STOP_BITS_1,
    };
    
    ESP_ERROR_CHECK( uart_param_config(UART_NUM_1, &uart_config));
    ESP_ERROR_CHECK( uart_set_pin(UART_NUM_1, 12, 11, 17, 18));
    ESP_ERROR_CHECK( uart_driver_install(UART_NUM_1, 1024, 1024, 0, NULL, 0) );
}

void uartLoop()
{
    uint8_t buf[11];
    buf[10] = 0;
    while (true)
    {
        int count = uart_read_bytes(UART_NUM_1, buf, sizeof(buf) - 1, 1);
        if (count > 0)
        {
            tinyusb_cdcacm_write_queue(0, buf, count);
            tinyusb_cdcacm_write_flush(0, portMAX_DELAY);
        }
    }
}