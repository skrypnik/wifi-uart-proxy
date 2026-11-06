#pragma once

#include <stdint.h>
#include <stdio.h>

#include <lwip/sockets.h>

enum packet_type_t {
	
	GET_COMMON_INFO  = 0x00,
	SET_NETWORK_INFO = 0xB0,
	SET_UART_INFO    = 0xB4,
	GET_UART_INFO    = 0xB5
};

enum response_code_t {
	
	RESPONSE_ALLOWED_REQUEST = 0x00,
	RESPONSE_UNKNOWN_REQUEST = 0x01,
	RESPONSE_INVALID_REQUEST = 0x02
};

typedef struct {
	
	uint16_t serial;
	uint8_t  sync;
	uint8_t  size;
	
} packet_header_t;


typedef struct {
	
	uint32_t address;
	uint16_t netport;
	uint32_t netmask;
	uint16_t serial;
	
} network_info_t;

typedef struct {
			
	uint8_t  project;
	uint8_t  major;
	uint8_t  minor;	
	uint8_t  variation;
	uint16_t year;
	uint8_t  month;
	uint8_t  day;
	
} firmware_info_t;

typedef struct {
	
	uint8_t major;
	uint8_t minor;	
	uint8_t variation;
	
} protocol_info_t;

void init_spi_filesystem();

void deinit_spi_filesystem();

bool load_network_info();

bool load_firmware_info();

bool load_protocol_info();

const network_info_t* get_network_info();

const firmware_info_t* get_firmware_info();

const protocol_info_t* get_protocol_info();

bool check_config_packet(uint8_t* header);

void process_config_request(int socket, struct sockaddr_in* address, uint8_t* payload, int size);
