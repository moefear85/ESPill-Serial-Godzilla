#include "main.h"

TaskHandle_t uartLoopHandle[UART_COUNT];
uint8_t uart[]={0,1};

void uartSetup()
{
    uart_config_t uart_config = 
    {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .stop_bits = UART_STOP_BITS_1,
    };
    for(int uart_num=0;uart_num<UART_COUNT;uart_num++)
    {
        ESP_ERROR_CHECK( uart_param_config(uart_num, &uart_config));
        ESP_ERROR_CHECK( uart_set_pin(uart_num,UART_TX[uart_num],UART_RX[uart_num],UART_DSR[uart_num],UART_CTS[uart_num]));
        ESP_ERROR_CHECK( uart_driver_install(uart_num, 1024, 1024, 0, NULL, 0) );
        xTaskCreate(uartLoop, NULL, 2048, &uart[uart_num], 0, &uartLoopHandle[uart_num]);
    }
}

void uartLoop(void* args)
{
    uint8_t num=*(uint8_t*)args;
    //printf("uart Loop: %d\n",num);
    uint8_t buf[11];
    buf[10] = 0;
    while (true)
    {
        int count = uart_read_bytes(num, buf, sizeof(buf) - 1, 1);
        if (count > 0)
        {
            //printf("uart%d: forwarding %d bytes...",num,count); fflush(stdout);
            tinyusb_cdcacm_write_queue(num, buf, count);
            //printf("done. Flushing..."); fflush(stdout);
            tinyusb_cdcacm_write_flush(num, portMAX_DELAY);
            //printf("done\n");
        }
        //else printf("uart%d: No data\n",num);
    }
}