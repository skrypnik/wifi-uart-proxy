file( GLOB_RECURSE PROJECT_HEADERS *.h)
file( GLOB_RECURSE PROJECT_SOURCES *.c)

idf_component_register(

	SRCS ${PROJECT_HEADERS} ${PROJECT_SOURCES}
)

spiffs_create_partition_image( storage ../image FLASH_IN_PROJECT )