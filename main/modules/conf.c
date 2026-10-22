#include "conf.h"

#include <esp_spiffs.h>
#include <esp_log.h>

#define TAG "CONF"

#define NETWORK_INFO_PATH "/spiffs/network.bin"

void init_spi_filesystem() {
	
	esp_vfs_spiffs_conf_t config = {
		
		.max_files = 5,
	    .base_path = "/spiffs",
	    .partition_label = NULL,
	    .format_if_mount_failed = true,
	};
	
	esp_vfs_spiffs_register(&config);
}

void deinit_spi_filesystem() {
	
	esp_vfs_spiffs_unregister(NULL);
}

bool read_network_info(network_info_t* info) {
	
	static network_info_t network_info;
	network_info.address = 0xC00A1001;
	network_info.netmask = 0xFFFF0000;
	network_info.netport = 16777;
	
	FILE* file = fopen(NETWORK_INFO_PATH, "r");
	
	if(file == NULL) {
		
		ESP_LOGE( TAG, "Creating default configuration..." );
		
		file = fopen(NETWORK_INFO_PATH, "w");
		
		if(file == NULL) {
			
			ESP_LOGE( TAG, "Failed to create default configuration..." );		
			
			return false;
		}
		
		if (fwrite(&network_info, sizeof(network_info), 0x01, file) <= 0x00) {
			
		    ESP_LOGE( TAG, "Failed to write configuration..." );
			fclose(file);
			
			return false;
		}
		
		fclose(file);
		
		file = fopen(NETWORK_INFO_PATH, "r");
		
		if(file == NULL) {
			
			ESP_LOGE( TAG, "Failed to open configuration file..." );	
				
			return false;
		}		
	}
	
	if(fread(&network_info, sizeof(network_info), 0x01, file) <= 0x00) {
		
		ESP_LOGE( TAG, "Failed to read configuration..." );
		fclose(file);
		return false;
	}
	
	fclose(file);
	
	return true;
}