#include "uart.h"

static QueueHandle_t uart1_queue;

void uartSetup()
{
    uart_config_t uart_config;
    uart_config.baud_rate = 115200;
    uart_config.data_bits = UART_DATA_8_BITS;
    uart_config.parity = UART_PARITY_DISABLE;
    uart_config.stop_bits = UART_STOP_BITS_1;
    uart_config.flow_ctrl = UART_HW_FLOWCTRL_DISABLE;
    uart_config.rx_flow_ctrl_thresh = 0;
    
    ESP_ERROR_CHECK( uart_param_config(UART_NUM_1, &uart_config));
    ESP_ERROR_CHECK( uart_set_pin(1, 12, 11, 17, 18));
    ESP_ERROR_CHECK( uart_driver_install(UART_NUM_1, 1024, 1024, 10, &uart1_queue, 0) );
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