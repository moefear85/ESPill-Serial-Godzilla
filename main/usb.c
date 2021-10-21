#include "usb.h"

static uint8_t buf[USBBUFSIZE + 2];

void usbSetup()
{
    tinyusb_config_t tusb_cfg = {};
    tinyusb_driver_install(&tusb_cfg);

    tinyusb_config_cdcacm_t amc_cfg =
    {
        .usb_dev = TINYUSB_USBDEV_0,
        .cdc_port = TINYUSB_CDC_ACM_0,
        .rx_unread_buf_sz = USBBUFSIZE,
        .callback_rx = &usbCallback,
        .callback_rx_wanted_char = NULL,
        .callback_line_state_changed = &tinyusb_cdc_line_state_changed_callback,
        .callback_line_coding_changed = &lineCodingCallback
    };
    tusb_cdc_acm_init(&amc_cfg);
}

void usbCallback(int itf, cdcacm_event_t *event)
{
    size_t rx_size = 0;
    esp_err_t ret = tinyusb_cdcacm_read(itf, buf + 1, USBBUFSIZE, &rx_size);
    if (ret == ESP_OK)
        buf[rx_size + 1] = '\0';

    uart_write_bytes(UART_NUM_1, buf + 1, rx_size);
}

void tinyusb_cdc_line_state_changed_callback(int itf, cdcacm_event_t *event)
{
    int dtr = event->line_state_changed_data.dtr;
    int rts = event->line_state_changed_data.rts;

    gpio_set_level(UART1_RTS_PIN, !rts);
    gpio_set_level(UART1_DTR_PIN, !dtr);
}

void lineCodingCallback(int itf, cdcacm_event_t *event)
{
    int bit_rate = event->line_coding_changed_data.p_line_coding->bit_rate;
    uart_set_baudrate(UART_NUM_1, bit_rate);
}