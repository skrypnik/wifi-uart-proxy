#pragma once

enum request_type_t {
	
	UDP_UART_REQUEST = 0x00,
	UDP_CONF_REQUEST = 0x80
};

void udp_server_task(void* parameters);
