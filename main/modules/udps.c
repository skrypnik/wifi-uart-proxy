#include "udps.h"
#include "conf.h"
#include "uart.h"
#include "defs.h"

#include <stdio.h>

#include <esp_log.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <lwip/netdb.h>
#include <lwip/sys.h>

#include <driver/uart.h>
#include <driver/gpio.h>
#include <string.h>

static const char *TAG = "UDPS";

uint8_t udp_buffer[UDP_BUFFER_SIZE];

void udp_server_task(void* parameters) {
	
    int address_family = AF_INET;
    int ip_protocol = IPPROTO_UDP;
	
	struct sockaddr_in listen_address;
    listen_address.sin_family = AF_INET;
    listen_address.sin_addr.s_addr = htonl(INADDR_ANY);
    listen_address.sin_port = htons(UDP_SERVER_PORT);
	
	struct sockaddr_in source_address;

    int udp_socket = socket(address_family, SOCK_DGRAM, ip_protocol);
	
    if (udp_socket == -1) {
		
        ESP_LOGE( TAG, "Failed to create socket" );
        return;
    }

    if (bind(udp_socket, (struct sockaddr*)&listen_address, sizeof(listen_address)) == -1) {
		
        ESP_LOGE (TAG, "Failed to bind address" );
        close(udp_socket);
        return;
    }
	
	printf("Socket created at %d\n", UDP_SERVER_PORT);
	
	uart_init();

    while (true) {
		
		printf("Wait for packet...\n");
		
		socklen_t addrlen = sizeof(source_address);
		
		int size = recvfrom(udp_socket, udp_buffer, UDP_BUFFER_SIZE, 0, (struct sockaddr*)&source_address, &addrlen);

		if (size == -1) {
			
            ESP_LOGE(TAG, "Receive failed...");
            continue;
        }
		
		//////////////////////////////////////////////////////////////////////////////
		
		int32_t header; memcpy(&header, udp_buffer, sizeof(header));
		
		//////////////////////////////////////////////////////////////////////////////
		
		if(header) {
			
			process_config_request(udp_socket, &source_address, udp_buffer + sizeof(header), size - sizeof(header));
			
			continue;
		}
		
		//////////////////////////////////////////////////////////////////////////////

		uart_send(udp_buffer + UDP_HEADER_SIZE, size - UDP_HEADER_SIZE);
        uart_process_response(udp_socket, &source_address);
    }

    close(udp_socket);
}
