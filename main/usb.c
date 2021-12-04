#include "usb.h"
#include "esp_debug_helpers.h"

#define CDC_COUNT CONFIG_CFG_TUD_CDC
static uint8_t buf[USBBUFSIZE + 2];

void usbSetup()
{
    tinyusb_config_t tusb_cfg = {};
    tinyusb_driver_install(&tusb_cfg);

    tinyusb_config_cdcacm_t amc_cfg =
    {
        .usb_dev = TINYUSB_USBDEV_0,
        .rx_unread_buf_sz = USBBUFSIZE,
        .callback_rx = &usbCallback,
        .callback_rx_wanted_char = NULL,
        .callback_line_state_changed = &tinyusb_cdc_line_state_changed_callback,
        .callback_line_coding_changed = &lineCodingCallback
    };
    for(int i=0;i<CDC_COUNT;i++)
    {
        amc_cfg.cdc_port=i;
        ESP_ERROR_CHECK( tusb_cdc_acm_init(&amc_cfg) );
    }
}

void usbCallback(int itf, cdcacm_event_t *event)
{ 
    //printf("data, itf: %d\n",itf);
    size_t rx_size = 0;
    esp_err_t ret = tinyusb_cdcacm_read(itf,buf+1,USBBUFSIZE,&rx_size);
    if (ret == ESP_OK)
        buf[rx_size + 1] = '\0';

    uart_write_bytes(itf,buf+1,rx_size);
}

void tinyusb_cdc_line_state_changed_callback(int itf, cdcacm_event_t *event)
{
    //printf("state, itf: %d\n",itf);
    int dtr = event->line_state_changed_data.dtr;
    int rts = event->line_state_changed_data.rts;

    gpio_set_level(UART_RTS[itf], !rts);
    gpio_set_level(UART_DTR[itf], !dtr);
}

void lineCodingCallback(int itf, cdcacm_event_t *event)
{
    //printf("coding, itf: %d\n",itf);
    int bit_rate = event->line_coding_changed_data.p_line_coding->bit_rate;
    uart_set_baudrate(itf, bit_rate);
}