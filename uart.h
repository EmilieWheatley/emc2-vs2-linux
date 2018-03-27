#ifndef EMC2_UART_
#define EMC2_UART_

#include <termios.h>

int set_interface_attribs (int fd, int speed, int parity);
void set_blocking (int fd, int should_block);

#endif /* EMC2_UART_ */
