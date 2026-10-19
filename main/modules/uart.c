#include "uart.h"
#include "defs.h"

#include <stdlib.h>
#include <string.h>

#include <esp_sleep.h>

#include <lwip/sockets.h>

#include <driver/uart.h>
#include <driver/gpio.h>

static char uart_buffer[UART_BUFFER_SIZE];

static char* buffer;

void uart_init() {
	
	uart_config_t uart_config = {
		
	    .baud_rate = 115200,
	    .data_bits = UART_DATA_8_BITS,
	    .parity = UART_PARITY_DISABLE,
	    .stop_bits = UART_STOP_BITS_1,
	    .flow_ctrl = UART_HW_FLOWCTRL_CTS_RTS
	};

	ESP_ERROR_CHECK( uart_param_config(UART_NUM_1, &uart_config) );
	ESP_ERROR_CHECK( uart_set_pin(UART_NUM_1, GPIO_NUM_17, GPIO_NUM_18, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE) );
	ESP_ERROR_CHECK( uart_driver_install(UART_NUM_1, UART_BUFFER_SIZE, 0, 0, NULL, 0) );
}

void uart_send(char* data, int size) {
	
	uart_write_bytes(UART_NUM_1, data, size);
}


void uart_process_response(int socket, struct sockaddr_in* address) {
	
	esp_sleep_enable_timer_wakeup(SLEEP_INTERVAL_USEC);
	
	size_t buffered_size = 0x00;
	
	uart_get_buffered_data_len(UART_NUM_1, &buffered_size);
	
	while (!buffered_size) { /// \TODO break by wait interval
		
		esp_light_sleep_start();
	
		uart_get_buffered_data_len(UART_NUM_1, &buffered_size);
	}
	
	int actual = uart_read_bytes(UART_NUM_1, uart_buffer, UART_BUFFER_SIZE, 100);
	
	int offset = 0x00; short expect = 0x00; memcpy(uart_buffer + 0x02, &expect, 0x02);
	
	buffer = malloc(expect);
	
	while (actual < expect) { /// \TODO break by wait interval
	
		uart_get_buffered_data_len(UART_NUM_1, &buffered_size);
		
		if (!buffered_size) continue;
		
		int size = uart_read_bytes(UART_NUM_1, uart_buffer, UART_BUFFER_SIZE, 100);
		
		memcpy(uart_buffer, buffer + offset, size);
				
		actual += size;
		offset += size;
	}
	
	short crc16 = 0x00; memcpy(buffer + expect - 0x02, &crc16, sizeof(short));
	
	/// \TODO calculate buffer checksum, send failure code if it not valid
	
	short frames = expect / UART_BUFFER_SIZE + 0x01;
	
	for(offset=0x00; offset<frames; offset += UART_BUFFER_SIZE) {
		
		static char frame[UDP_BUFFER_SIZE];
		
		int size = (expect - offset) >= UART_BUFFER_SIZE ? UART_BUFFER_SIZE : (expect - offset);
		
		buffer[0x00] = 0x00;
		memcpy(buffer + 0x01, &size, sizeof(size));
		memcpy(buffer + 0x05, &offset, sizeof(offset));
		memcpy(buffer + offset, frame + UDP_HEADER_SIZE, size);
		
		sendto(socket, frame, size, 0, (struct sockaddr *)address, sizeof(*address));
		
		if(size < UART_BUFFER_SIZE) break;
	}
}
