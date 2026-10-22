#include <unistd.h>

#include <esp_log.h>

#include "modules/wifi.h"
#include "modules/udps.h"
//#include "modules/conf.h"

#define SLEEP_INTERVAL_USEC 100000

static const char* TAG = "MAIN";

void app_main(void)
{
//	init_spi_filesystem();
//	
//	network_info_t network_info;
//	
//	bool done = read_network_info(&network_info);
//	
//	if(done) {
//		
//		printf("ADDRESS: %X\n", (unsigned int) network_info.address);
//		printf("NETMASK: %X\n", (unsigned int) network_info.netmask);
//		printf("NETPORT: %d\n", network_info.netport);
//	}
//	
//	deinit_spi_filesystem();
			
	wifi_init_access_point();
	
	if(wifi_init_status() == WIFI_NOT_CONFIGURED) {
		
		ESP_LOGI( TAG, "Can't configure WiFi access point. Exiting...");
				
		return;
	}
	
	xTaskCreate(udp_server_task, "udp_server_task", 2048, NULL, 1, NULL);
}
