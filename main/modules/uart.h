#pragma once

#include <lwip/sockets.h>

void uart_init();

void uart_send(uint8_t* data, int size);

void uart_process_response(int socket, struct sockaddr_in* source_address);
