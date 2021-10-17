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
/*
    ESP_ERROR_CHECK( uart_param_config(UART_NUM_0, &uart_config));
    ESP_ERROR_CHECK( uart_set_pin(1, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE) );
    ESP_ERROR_CHECK( uart_driver_install(UART_NUM_0, 1024, 1024, 0, NULL, 0) );
*/
    ESP_ERROR_CHECK( uart_param_config(UART_NUM_1, &uart_config));
    ESP_ERROR_CHECK( uart_set_pin(1, 12, 11, 17, 18));
    ESP_ERROR_CHECK( uart_driver_install(UART_NUM_1, 1024, 1024, 10, &uart1_queue, 0) );
    //uart_intr_config_t intr_cfg;
    //intr_cfg.rxfifo_full_thresh = 1;
    //uart_set_rx_timeout(UART_NUM_1, 10);
    
    //ESP_ERROR_CHECK( uart_intr_config(UART_NUM_1, &intr_cfg) );
    //ESP_ERROR_CHECK( uart_enable_rx_intr(UART_NUM_1) );
}

void uartLoop()
{
    while (true)
    {
        uint8_t buf[11];
        buf[10] = 0;
        while (true)
        {
            int count = uart_read_bytes(UART_NUM_1, buf, sizeof(buf) - 1, 1);
            
            //printf("\r\ncount: %d, data: %s", count, (char*) buf);
            //fflush(stdout);
            if (count > 0)
            {
                //printf("\r\ncount: %d, data: %s", count, (char*) buf);
                //fflush(stdout);
                tinyusb_cdcacm_write_queue(0, buf, count);
                tinyusb_cdcacm_write_flush(0, portMAX_DELAY);
            }
        }
        /*
        uart_event_t event;
        printf("\r\nEntering xQueueRecieve()");
        fflush(stdout);
        if (xQueueReceive(uart1_queue, &event, portMAX_DELAY))
        {
            printf("\r\nEntered xQueueRecieve()");
            fflush(stdout);
            switch(event.type)
            {
                case UART_DATA:
                    printf("\r\nUART_DATA");
                    fflush(stdout);
                    break;
                case UART_BUFFER_FULL:
                    printf("\r\nUART_BUFFER_FULL");
                    fflush(stdout);
                    break;
                default:
                    printf("\r\nUART Unknown Event");
                    fflush(stdout);
                    break;
            }
        }
        */
    }
}