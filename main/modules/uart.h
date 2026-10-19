#pragma once

#include <lwip/sockets.h>

void uart_init();

void uart_send(char* data, int size);

void uart_process_response(int socket, struct sockaddr_in* address);
