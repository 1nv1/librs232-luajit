#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int serial_open(char *serial_name, speed_t baud);
int serial_read(int serial_fd, char *data, int size, int timeout_usec);
void serial_send(int serial_fd, char *data, int size);
void serial_close(int fd);
