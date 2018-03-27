

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include "uart.h"
#include "tcpserver.h"

#define LOOP (10)

int tcpserver_read_acq()
{
	// Creating socket file descriptor
	int server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (!server_fd){
		printf("ERROR: socket failed\n");
		return -1;
	}

	int new_socket = set_tcp_server(server_fd);
	if (new_socket < 0) {
		printf("Server init failed (error code %d)", new_socket);
		return -2;
	}

	uint run = LOOP;
	int valread = 0;
	char buffer[1024] = {0};
    char *hello = "Hello from server";

	while (run) {
		valread = read(new_socket , buffer, sizeof(buffer));
		printf("%d buffer read = 0x%x\n", (LOOP-run), buffer);

		send(new_socket , hello , strlen(hello) , 0 );
		printf("Hello message sent\n");
		run--;
	  }

	  close(new_socket);

	  return 0;
}

int read_uart()
{
	char *portname = "/dev/ttyULx";//"/dev/ttyUSB1";

	int uart_fd = open (portname, O_RDWR | O_NOCTTY | O_SYNC);
	if (uart_fd < 0) {
		printf("error %d opening %s: %s", errno, portname, strerror (errno));
		return -1;
	}

	int err = set_interface_attribs (uart_fd, B115200, 0); // set speed to 115,200 bps, 8n1 (no parity)
	if (err < 0) {
		printf("Fail to set interface attribute (error %d)\n", err);
		return -2;
	}
	set_blocking (uart_fd, 0);                // set no blocking

	uint run = LOOP;
	char buffer[100] = {0};
	while (run) {
		int n = read (uart_fd, buffer, sizeof buffer);  // read up to 100 characters if ready to read
		printf("%d- UART read %s\n", buffer, (LOOP-run));
		run--;
	}

	return 0;
}

// packetID | rd(1)/wr(0) | id | value
// apogee rw | apogee id | 0/1/readFrequency | packetID
// 16 bits | 1 bit | 15 bit | 32 bits
int main(int argc, char const *argv[])
{
	printf("TCP server test : %d\n", tcpserver_read_acq());
	printf("UART test : %d\n", read_uart());

    return 0;
}
