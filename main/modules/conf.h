#pragma once

#include <stdio.h>

#include <lwip/sockets.h>

enum packet_type_t {
	
	GET_DEVICE_INFO  = 0x00,
	SET_NETWORK_INFO = 0xB0,
	SET_UART_INFO    = 0xB4,
	GET_UART_INFO    = 0xB5
};

typedef struct {
	
	uint32_t address;
	uint16_t netport;
	uint32_t netmask;
	uint16_t serial;
	
} network_info_t;

void init_spi_filesystem();

void deinit_spi_filesystem();

bool load_network_info();

const network_info_t* get_network_info();

void process_config_request(int socket, struct sockaddr_in* address, uint8_t* buffer, int size);
