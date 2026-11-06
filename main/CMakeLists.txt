file( GLOB_RECURSE PROJECT_HEADERS *.h)
file( GLOB_RECURSE PROJECT_SOURCES *.c)

idf_component_register(

	SRCS ${PROJECT_HEADERS} ${PROJECT_SOURCES}
	REQUIRES esp_wifi esp_netif esp_timer nvs_flash esp_driver_uart esp_driver_gpio spiffs
)

set( REQS esp_timer )

spiffs_create_partition_image( storage ../image FLASH_IN_PROJECT )
