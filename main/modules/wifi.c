#include "wifi.h"

#include "nvs_flash.h"
#include "esp_wifi.h"
#include "esp_log.h"

#include <esp_sleep.h>

#define SLEEP_INTERVAL_USEC     100000
#define INIT_WAIT_INTERVAL_USEC 5000000

static const char* TAG = "WIFI";

int wifi_status = WIFI_NOT_CONFIGURED;

void wifi_event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data)
{
    if (event_id == WIFI_EVENT_AP_START) {
		
        ESP_LOGI( TAG, "Access point started" );
		
		wifi_status = WIFI_WAIT_FOR_STATION;
    } 
	
	if (event_id == WIFI_EVENT_AP_STACONNECTED) {
		
        ESP_LOGI( TAG, "Station connected");
		
		wifi_status = WIFI_STATION_CONNECTED;
    }
	
	if (event_id == WIFI_EVENT_AP_STADISCONNECTED) {
		
        ESP_LOGI( TAG, "Station disconnected" );
		
		wifi_status = WIFI_STATION_DISCONNECTED;
    }
}

void wifi_init_access_point(void)
{
    ESP_ERROR_CHECK( nvs_flash_init() );
    ESP_ERROR_CHECK( esp_netif_init() );
    ESP_ERROR_CHECK( esp_event_loop_create_default() );

    esp_netif_t* p_netif = esp_netif_create_default_wifi_ap();
	
    if (!p_netif) {
    
		ESP_LOGE( TAG, "Failed to create default network interface" );
		
        return;
    }

    ESP_ERROR_CHECK( esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, wifi_event_handler, NULL) );

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
	
    ESP_ERROR_CHECK( esp_wifi_init(&cfg) );

    ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_AP) );

    wifi_config_t wifi_config = {
		
        .ap = {
			
            .ssid           = ESP_WIFI_SSID,
            .ssid_len       = strlen(ESP_WIFI_SSID),
            .channel        = ESP_WIFI_CHANNEL,
            .password       = ESP_WIFI_PASSWORD,
            .max_connection = MAX_WIFI_STATIONS,
            .authmode       = WIFI_AUTH_WPA_WPA2_PSK,
        }
    };

    if (strlen(ESP_WIFI_PASSWORD) == 0x00) {
		
        wifi_config.ap.authmode = WIFI_AUTH_OPEN;
    }

    ESP_ERROR_CHECK( esp_wifi_set_config(WIFI_IF_AP, &wifi_config) );
    ESP_ERROR_CHECK( esp_wifi_start() );

    esp_netif_ip_info_t if_info;

	ESP_ERROR_CHECK( esp_netif_get_ip_info(p_netif, &if_info) );
    ESP_LOGI( TAG, "ESP32 AP IP: "IPSTR, IP2STR(&if_info.ip) );
}

int wifi_init_status(void)
{
	esp_sleep_enable_timer_wakeup(SLEEP_INTERVAL_USEC);
	
	int iterations = INIT_WAIT_INTERVAL_USEC / SLEEP_INTERVAL_USEC;
	
	for(int idx=0x00; idx<iterations; ++idx) {
		
		if(wifi_status != WIFI_NOT_CONFIGURED) {
			
			return WIFI_WAIT_FOR_STATION;
		}
		
		esp_light_sleep_start();
	}
		
	return WIFI_NOT_CONFIGURED;
}
