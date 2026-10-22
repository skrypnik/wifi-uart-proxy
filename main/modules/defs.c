#include "defs.h"

void print_hex(uint8_t* buffer, int size) {
	
	for(int idx=0x00; idx<size; ++idx) {
		
		printf("%02X ", buffer[idx]);
	}
	
	printf("\n");
}