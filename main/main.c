#include <unistd.h>

#include <esp_log.h>

#include "modules/wifi.h"
#include "modules/udps.h"
#include "modules/conf.h"

#define SLEEP_INTERVAL_USEC 100000

static const char* TAG = "MAIN";

void app_main(void)
{
	//////////////////////////////////////////////////////////////////////////////
	
//	init_spi_filesystem();
//	
//	load_network_info();
//	load_firmware_info();
//	load_protocol_info();
//	
//	deinit_spi_filesystem();
	
	//////////////////////////////////////////////////////////////////////////////
				
	wifi_init_access_point();
	
	if(wifi_init_status() == WIFI_NOT_CONFIGURED) {
		
		ESP_LOGI( TAG, "Can't configure WiFi access point. Exiting...\n");
				
		return;
	}
	
	//////////////////////////////////////////////////////////////////////////////
	printf("Creating network handler...\n");
	xTaskCreate(udp_server_task, "udp_server_task", 4096, NULL, 1, NULL);
	printf("Network handler created...\n");
}
