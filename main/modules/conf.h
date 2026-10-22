#pragma once

#include <stdio.h>

typedef struct {
	
	uint32_t address;
	uint32_t netmask;
	uint16_t netport;
	
} network_info_t;

void init_spi_filesystem();

void deinit_spi_filesystem();

bool read_network_info(network_info_t* info);
