#include "conf.h"

#include <esp_spiffs.h>
#include <esp_log.h>

#define TAG "CONF"

#define NETWORK_INFO_PATH "/spiffs/network.cfg"

static network_info_t network_info;

void init_spi_filesystem() {
	
	esp_vfs_spiffs_conf_t config = {
		
		.max_files = 5,
	    .base_path = "/spiffs",
	    .partition_label = NULL,
	    .format_if_mount_failed = true
	};
	
	esp_vfs_spiffs_register(&config);
}

void deinit_spi_filesystem() {
	
	esp_vfs_spiffs_unregister(NULL);
}

bool load_network_info() {
	
	printf("Loading network info...\n");
	
	FILE* file = fopen(NETWORK_INFO_PATH, "r");
	
	if(file == NULL) {
		
		ESP_LOGE( TAG, "Failed to open configuration file..." );	
			
		return false;
	}
	
	if(fread(&network_info, 0x01, sizeof(network_info_t), file) <= 0x00) {
		
		ESP_LOGE( TAG, "Failed to read configuration..." );
		fclose(file);
		return false;
	}
	
	fclose(file);
	
	printf("Network info loaded successfully...\n");
	
	printf("ADDRESS: %X\n", (unsigned int) network_info.address);
	printf("NETMASK: %X\n", (unsigned int) network_info.netmask);
	printf("NETPORT: %d\n", network_info.netport);
	printf("SERIAL:  %d\n", network_info.serial);
	
	return true;
}

const network_info_t* get_network_info()
{
	return &network_info;
}

void process_config_request(int socket, struct sockaddr_in* address, uint8_t* buffer, int size)
{
	int8_t type = buffer[0x00];
	
	if(type == GET_DEVICE_INFO) {
		
		
	}
}
