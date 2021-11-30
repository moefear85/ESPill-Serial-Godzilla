#include "usb.h"

static uint8_t buf[USBBUFSIZE + 2];
my_tusb_desc_device_t my_desc={};
tusb_desc_strarray_device_t my_string_descriptor =
{
    (char[]){0x09, 0x04}, // 0: is supported language is English (0x0409)
    "Itani Industries",   // 1: Manufacturer
    "USB-UART Adapter",   // 2: Product
    "012-345",            // 3: Serials, should use chip ID
};

void usbSetup()
{
    tinyusb_config_t tusb_cfg = {};
    
    tusb_cfg.descriptor=&my_desc;
    //tusb_cfg.string_descriptor=my_string_descriptor;

    my_desc.bLength=sizeof(my_desc);
    my_desc.bDescriptorType=1;
    my_desc.bcdUSB= 0x0200;
    my_desc.bDeviceClass=239;
    my_desc.bDeviceSubClass=2;
    my_desc.bDeviceProtocol=1;
    my_desc.bMaxPacketSize0=64;
    my_desc.idVendor=0x303a;
    my_desc.idProduct=0x4001;
    my_desc.bcdDevice=0x0101;
    my_desc.iManufacturer=1;
    my_desc.iProduct=2;
    my_desc.iSerialNumber=3;
    my_desc.bNumConfigurations=1;

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
    ESP_ERROR_CHECK( tusb_cdc_acm_init(&amc_cfg) );
    amc_cfg.cdc_port=1;
    ESP_ERROR_CHECK( tusb_cdc_acm_init(&amc_cfg) );
    amc_cfg.cdc_port=2;
    ESP_ERROR_CHECK( tusb_cdc_acm_init(&amc_cfg) );
}

void usbCallback(int itf, cdcacm_event_t *event)
{
    printf("data, itf: %d\n",itf);
    size_t rx_size = 0;
    esp_err_t ret = tinyusb_cdcacm_read(itf, buf + 1, USBBUFSIZE, &rx_size);
    if (ret == ESP_OK)
        buf[rx_size + 1] = '\0';

    uart_write_bytes(UART_NUM_1, buf + 1, rx_size);
}

void tinyusb_cdc_line_state_changed_callback(int itf, cdcacm_event_t *event)
{
    printf("state, itf: %d\n",itf);
    int dtr = event->line_state_changed_data.dtr;
    int rts = event->line_state_changed_data.rts;

    gpio_set_level(UART1_RTS_PIN, !rts);
    gpio_set_level(UART1_DTR_PIN, !dtr);
}

void lineCodingCallback(int itf, cdcacm_event_t *event)
{
    printf("coding, itf: %d\n",itf);
    int bit_rate = event->line_coding_changed_data.p_line_coding->bit_rate;
    uart_set_baudrate(UART_NUM_1, bit_rate);
}