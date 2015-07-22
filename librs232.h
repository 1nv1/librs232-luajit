/*
 *  librs232.h
 *  Author: Nelson Lombardo (C) 2013
 *  e-mail: nelson.lombardo@gmail.com
 *  License: MIT
 */
#ifndef _LIBRS232_H_
#define _LIBRS232_H_

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


/*******************************************************************************
 * Public Methods - Direct access to any serial port device define in Linux    *
 ******************************************************************************/

int serial_open(char *serial_name, speed_t baud);
int serial_read(int serial_fd, char *data, int size, int timeout_usec);
void serial_send(int serial_fd, char *data, int size);
void serial_close(int fd);

#endif
