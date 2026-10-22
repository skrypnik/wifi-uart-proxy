#include "uart.h"
#include "defs.h"
#include "lwip/sockets.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <driver/uart.h>
#include <driver/gpio.h>

uint8_t uart_buffer[UART_BUFFER_SIZE];

static const uint8_t UART_CHECKSUM_ERROR [] = { 0x02, 0xFF, 0x01, 0x00, 0x02, 0x18, 0x52 };
static const uint8_t UART_SYNCBYTE_ERROR [] = { 0x02, 0xFF, 0x00, 0x00, 0x22, 0x0B };

static const uint16_t polynom[256] =
{
	0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50A5, 0x60C6, 0x70E7, 0x8108, 0x9129, 0xA14A, 0xB16B, 0xC18C, 0xD1AD, 0xE1CE, 0xF1EF,
	0x1231, 0x0210, 0x3273, 0x2252, 0x52B5, 0x4294, 0x72F7, 0x62D6, 0x9339, 0x8318, 0xB37B, 0xA35A, 0xD3BD, 0xC39C, 0xF3FF, 0xE3DE,
	0x2462, 0x3443, 0x0420, 0x1401, 0x64E6, 0x74C7, 0x44A4, 0x5485, 0xA56A, 0xB54B, 0x8528, 0x9509, 0xE5EE, 0xF5CF, 0xC5AC, 0xD58D,
	0x3653, 0x2672, 0x1611, 0x0630, 0x76D7, 0x66F6, 0x5695, 0x46B4, 0xB75B, 0xA77A, 0x9719, 0x8738, 0xF7DF, 0xE7FE, 0xD79D, 0xC7BC,
	0x48C4, 0x58E5, 0x6886, 0x78A7, 0x0840, 0x1861, 0x2802, 0x3823, 0xC9CC, 0xD9ED, 0xE98E, 0xF9AF, 0x8948, 0x9969, 0xA90A, 0xB92B,
	0x5AF5, 0x4AD4, 0x7AB7, 0x6A96, 0x1A71, 0x0A50, 0x3A33, 0x2A12, 0xDBFD, 0xCBDC, 0xFBBF, 0xEB9E, 0x9B79, 0x8B58, 0xBB3B, 0xAB1A,
	0x6CA6, 0x7C87, 0x4CE4, 0x5CC5, 0x2C22, 0x3C03, 0x0C60, 0x1C41, 0xEDAE, 0xFD8F, 0xCDEC, 0xDDCD, 0xAD2A, 0xBD0B, 0x8D68, 0x9D49,
	0x7E97, 0x6EB6, 0x5ED5, 0x4EF4, 0x3E13, 0x2E32, 0x1E51, 0x0E70, 0xFF9F, 0xEFBE, 0xDFDD, 0xCFFC, 0xBF1B, 0xAF3A, 0x9F59, 0x8F78,
	0x9188, 0x81A9, 0xB1CA, 0xA1EB, 0xD10C, 0xC12D, 0xF14E, 0xE16F, 0x1080, 0x00A1, 0x30C2, 0x20E3, 0x5004, 0x4025, 0x7046, 0x6067,
	0x83B9, 0x9398, 0xA3FB, 0xB3DA, 0xC33D, 0xD31C, 0xE37F, 0xF35E, 0x02B1, 0x1290, 0x22F3, 0x32D2, 0x4235, 0x5214, 0x6277, 0x7256,
	0xB5EA, 0xA5CB, 0x95A8, 0x8589, 0xF56E, 0xE54F, 0xD52C, 0xC50D, 0x34E2, 0x24C3, 0x14A0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
	0xA7DB, 0xB7FA, 0x8799, 0x97B8, 0xE75F, 0xF77E, 0xC71D, 0xD73C, 0x26D3, 0x36F2, 0x0691, 0x16B0, 0x6657, 0x7676, 0x4615, 0x5634,
	0xD94C, 0xC96D, 0xF90E, 0xE92F, 0x99C8, 0x89E9, 0xB98A, 0xA9AB, 0x5844, 0x4865, 0x7806, 0x6827, 0x18C0, 0x08E1, 0x3882, 0x28A3,
	0xCB7D, 0xDB5C, 0xEB3F, 0xFB1E, 0x8BF9, 0x9BD8, 0xABBB, 0xBB9A, 0x4A75, 0x5A54, 0x6A37, 0x7A16, 0x0AF1, 0x1AD0, 0x2AB3, 0x3A92,
	0xFD2E, 0xED0F, 0xDD6C, 0xCD4D, 0xBDAA, 0xAD8B, 0x9DE8, 0x8DC9, 0x7C26, 0x6C07, 0x5C64, 0x4C45, 0x3CA2, 0x2C83, 0x1CE0, 0x0CC1,
	0xEF1F, 0xFF3E, 0xCF5D, 0xDF7C, 0xAF9B, 0xBFBA, 0x8FD9, 0x9FF8, 0x6E17, 0x7E36, 0x4E55, 0x5E74, 0x2E93, 0x3EB2, 0x0ED1, 0x1EF0
};

uint16_t CRC16(const void* buffer, int size)
{
 	uint8_t* ptr = (uint8_t*) buffer ;
 	
	uint16_t crc = 0x00;
 
 	while(size--)
 	{
 		uint8_t data = *ptr++;
  		data ^= (uint8_t) (crc >> 0x08);
  		uint16_t temp = polynom[data];
  		crc = temp ^ (crc << 0x08);
 	}
	
	uint8_t rbyte = crc >> 0x08;
	
	return (crc << 0x08) | rbyte;
}	

void uart_init() {
	
	uart_config_t uart_config = {
		
	    .baud_rate = 115200,
	    .data_bits = UART_DATA_8_BITS,
	    .parity = UART_PARITY_DISABLE,
	    .stop_bits = UART_STOP_BITS_1,
	    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
	};

	ESP_ERROR_CHECK( uart_param_config(UART_NUM_2, &uart_config) );
	ESP_ERROR_CHECK( uart_set_pin(UART_NUM_2, GPIO_NUM_17, GPIO_NUM_16, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE) );
	ESP_ERROR_CHECK( uart_driver_install(UART_NUM_2, UART_BUFFER_SIZE, 0, 0, NULL, 0) );
}

void uart_send(uint8_t* data, int size) {
	
	uart_write_bytes(UART_NUM_2, data, size);
}

void uart_process_response(int socket, struct sockaddr_in* source_address) {
	
	size_t data_size = 0x00;
	
	uart_get_buffered_data_len(UART_NUM_2, &data_size);
	
	while (!data_size) { /// \TODO break by wait interval
	
		uart_get_buffered_data_len(UART_NUM_2, &data_size);
	}
	
	int actual = uart_read_bytes(UART_NUM_2, uart_buffer, UART_BUFFER_SIZE, 0);
	
	uint16_t sync = 0x00;
	memcpy( &sync, uart_buffer, sizeof(sync));
	
	if(sync != 0x02) {
		
		printf("ERROR: WRONG SYNC BYTE.\n");
		
		static uint_fast8_t error[0x0F];
		memset(error, 0x00, 0x0F);
		memcpy(error + UDP_HEADER_SIZE, UART_SYNCBYTE_ERROR, 0x06);
		
		socklen_t addrlen = sizeof(*source_address);			
		sendto(socket, error, 0x0F, 0, (struct sockaddr *)source_address, addrlen);
		
		return;
	}
	
	uint16_t expect = 0x00;
	memcpy( &expect, uart_buffer + sizeof(sync), sizeof(expect));
	expect = expect	+ UART_HEADER_SIZE + UART_CHECKSUM_SIZE;
	
	printf("Buffer size: %d\n", expect);
	uint8_t* buffer = (uint8_t*) heap_caps_malloc(expect, MALLOC_CAP_8BIT);
	memcpy(buffer, uart_buffer, actual);
	
	int offset = actual; 
	
	while (actual < expect) { /// \TODO break by wait interval
	
		int size = uart_read_bytes(UART_NUM_2, uart_buffer, UART_BUFFER_SIZE, 10);
		
		if(size <= 0x00) continue;
		
		memcpy(buffer + offset, uart_buffer, size);
				
		actual += size;
		offset += size;
	}
	
	uint16_t act_crc = 0x00, exp_crc = CRC16(buffer, expect - UART_CHECKSUM_SIZE);
	memcpy(&act_crc, buffer + expect - UART_CHECKSUM_SIZE, UART_CHECKSUM_SIZE);
	printf("CRC16: %X %X\n", act_crc, exp_crc);
	
	if(act_crc != exp_crc) {
		
		printf("ERROR: WRONG CRC.\n");

		static uint_fast8_t error[0x10];
		memset(error, 0x00, 0x10);
		memcpy(error + UDP_HEADER_SIZE, UART_CHECKSUM_ERROR, 0x07);

		socklen_t addrlen = sizeof(*source_address);			
		sendto(socket, error, 0x10, 0, (struct sockaddr *)source_address, addrlen);

		return;
	}
	
	short frames = actual / UART_BUFFER_SIZE + 0x01;
	
	printf("Frames count: %d\n", frames);
	
	static uint8_t frame[UDP_BUFFER_SIZE];
	
	for(int idx=0x00; idx<frames; ++idx) {
		
		offset = idx * UART_BUFFER_SIZE;
		
		int size = (expect - offset) > UART_BUFFER_SIZE ? UART_BUFFER_SIZE : (expect - offset);
		
		printf("Frame size: %d\n", size);
		
		memset(frame, 0x00, 0x01);
		memcpy(frame + 0x01, &expect, sizeof(expect));
		memcpy(frame + 0x05, &offset, sizeof(offset));
		memcpy(frame + 0x09, buffer + offset, size);
		
		socklen_t addrlen = sizeof(*source_address);			
		int sent = sendto(socket, frame, size + UDP_HEADER_SIZE, 0, (struct sockaddr *)source_address, addrlen);
		
		if(sent < 0x00) {
			
			printf("Sending failed...\n");
			break;
		}
		
		printf("Sent %d bytes\n", sent);
	}
	
	heap_caps_free(buffer);
}
