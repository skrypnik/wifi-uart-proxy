#include "udps.h"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <lwip/sockets.h>
#include <lwip/sys.h>
#include <lwip/netdb.h>

#include <esp_log.h>

static const char *TAG = "UDPS";

void udp_server_task(void* parameters) {
	
    char rx_buffer[MAX_BUFFER_SIZE];
	
    char addr_str[128];
    int addr_family = AF_INET;
    int ip_protocol = IPPROTO_UDP;
    struct sockaddr_in dest_addr;

    dest_addr.sin_family = AF_INET;
    dest_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    dest_addr.sin_port = htons(UDP_SERVER_PORT);

    int sock = socket(addr_family, SOCK_DGRAM, ip_protocol);
	
    if (sock == -1) {
		
        ESP_LOGE(TAG, "Failed to create socket");
        return;
    }

    if (bind(sock, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) == -1) {
		
        ESP_LOGE(TAG, "Failed to bind");
        close(sock);
        return;
    }

    while (true) {

		if (recvfrom(sock, rx_buffer, MAX_BUFFER_SIZE, 0, (struct sockaddr *)&dest_addr, (socklen_t *)&addr_family) == -1) {
			
            ESP_LOGE(TAG, "recvfrom failed");
            continue;
        }

        inet_ntop(addr_family, &dest_addr.sin_addr, addr_str, sizeof(addr_str));
        ESP_LOGI(TAG, "Received packet from %s: %s", addr_str, rx_buffer);

        sendto(sock, rx_buffer, strlen(rx_buffer), 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
    }

    close(sock);
}
