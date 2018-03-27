#ifndef EMC2_TCPSERVER_
#define EMC2_TCPSERVER_

#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080


int set_tcp_server(int fd);

#endif //EMC2_TCPSERVER_
