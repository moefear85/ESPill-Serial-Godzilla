#include "wifi.h"

int adjustChannelCounter = 0;
TimerHandle_t adjustChannelTimer;
uint8_t targetAddress[] = {0xa8,0x48,0xfa,0xdd,0x63,0x03};

void wifiSetup()
{
    esp_netif_init();
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg);
    esp_wifi_set_mode(WIFI_MODE_STA);
    esp_wifi_start();
    esp_now_init();
    esp_now_register_recv_cb(OnDataRecv);
    esp_now_register_send_cb(OnDataSent);
    esp_now_peer_info_t peer = 
    {
      .peer_addr =
      {
        [0] = targetAddress[0],
        [1] = targetAddress[1],
        [2] = targetAddress[2],
        [3] = targetAddress[3],
        [4] = targetAddress[4],
        [5] = targetAddress[5]
      }
    };
    esp_now_add_peer(&peer);
}

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len)
{
  switch (incomingData[0])
  {
    case boot:
      printf("Unexpected Boot Mode Message Recieved\n");
      break;
    case data:
      tinyusb_cdcacm_write_queue(0, (uint8_t*) (incomingData + 1), len - 1);
      tinyusb_cdcacm_write_flush(0, portMAX_DELAY);
      break;
    case ping:
      break;
    default:
      printf("Unknown Packet Header Recieved\n");
  }
}

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t stat)
{
}

void adjustChannel()
{
    //printf("%d -- Quck Scan...", adjustChannelCounter++); fflush(stdout);
    uint8_t primary, oldPrimary;
    wifi_second_chan_t secondary, oldSecondary;
    esp_wifi_get_channel(&oldPrimary, &oldSecondary);
    wifi_scan_config_t config = 
    {
        .ssid = (u_char*) "moefear85-P20",
        .channel = oldPrimary,
    };
    //printf("Wifi Channel: %d\n", primary);
    esp_wifi_scan_start(&config, true);
    //printf("Done. "); fflush(stdout);
    uint16_t apCount;
    esp_wifi_scan_get_ap_num(&apCount);
    //printf("AP Count: %d\n", apCount);
    if (apCount < 1)
    {
        //printf("AP not Found.\n");
        config.channel = 0;
        //printf("Full Scan..."); fflush(stdout);
        esp_wifi_scan_start(&config, true);
        //printf("Done. "); fflush(stdout);
        esp_wifi_scan_get_ap_num(&apCount);
    }
    if (apCount < 1)
    {
        //printf("AP still not Found. Using default. "); fflush(stdout);
        primary = DEFAULT_CHANNEL;
        secondary = 0;
    }
    else
    {
        //printf("AP Found. "); fflush(stdout);
        wifi_ap_record_t aps[apCount];
        esp_wifi_scan_get_ap_records(&apCount, aps);
        primary = aps[0].primary;
        secondary = aps[0].second;
    }
    if (primary != oldPrimary || secondary != oldSecondary)
    {
        //printf("Channel changed: %d\n", primary);
        esp_wifi_set_channel(primary, secondary);
    }
    else
    {
        //printf("Channel same: %d\n", primary);
    }
}