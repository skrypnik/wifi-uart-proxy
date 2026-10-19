#include "udps.h"
#include "uart.h"
#include "defs.h"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <lwip/sockets.h>
#include <lwip/sys.h>
#include <lwip/netdb.h>

#include <esp_log.h>

static const char *TAG = "UDPS";

static char address[32];

static char udp_buffer[UDP_BUFFER_SIZE];

void print_hex(char* buffer, int size) {
	
	for(int idx=0x00; idx<size; ++idx) {
		
		printf("%02X ", buffer[idx]);
	}
	
	printf("\n");
}

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
	
	ESP_LOGE( TAG, "Socket created at %d", UDP_SERVER_PORT );
	
	uart_init();

    while (true) {
		
		int size = recvfrom(udp_socket, udp_buffer, UDP_BUFFER_SIZE, 0, (struct sockaddr*)&source_address, (socklen_t *)&address_family);

		if (size == -1) {
			
            ESP_LOGE(TAG, "Receive failed");
            continue;
        }

        inet_ntop(address_family, &source_address.sin_addr, address, sizeof(address));
        ESP_LOGI( TAG, "Received packet from %s: ", address );
		print_hex(udp_buffer, size);
		
		uart_send(udp_buffer + UDP_HEADER_SIZE, size - UDP_HEADER_SIZE);

        uart_process_response(udp_socket, &source_address);
    }

    close(udp_socket);
}
