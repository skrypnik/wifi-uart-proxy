#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_netif.h"

#define ESP_WIFI_SSID   	"RADIO"
#define ESP_WIFI_PASSWORD	"12345678"
#define MAX_WIFI_STATIONS	2
#define ESP_WIFI_CHANNEL	1

enum wifi_status_t {
	
	WIFI_NOT_CONFIGURED       = 0x00,
	WIFI_WAIT_FOR_STATION     = 0x01,
	WIFI_STATION_CONNECTED    = 0x02,
	WIFI_STATION_DISCONNECTED = 0x03
};

void wifi_event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data);

void wifi_init_access_point(void);

int wifi_init_status(void);
