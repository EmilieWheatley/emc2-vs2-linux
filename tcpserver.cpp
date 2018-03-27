#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#include "tcpserver.h"


int set_tcp_server(int fd)
{
	int opt = 1;
	struct sockaddr_in address;
	int addrlen = sizeof(address);
	int new_socket;

	// Forcefully attaching socket to the port 8080
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) { // optional
	  printf("ERROR: setsockopt");
	  return -1;
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons( PORT );

	// Forcefully attaching socket to the port 8080
	if (bind(fd, (struct sockaddr *)&address, sizeof(address))<0) {
	  printf("ERROR: bind failed");
	  return -2;
	}

	if (listen(fd, 3) < 0) {
	  printf("ERROR: listen");
	  return -3;
	}

	if ((new_socket = accept(fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
	  printf("ERROR: accept");
	  return -4;
	}

  return new_socket;
}
