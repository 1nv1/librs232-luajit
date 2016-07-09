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

#define DEV_NAME_LEN	50

typedef struct __DEV_RS232 {
	int connect;
	char name[DEV_NAME_LEN];
	speed_t baud;
	int fd;
	int timeout;
} DEV_RS232;

/*******************************************************************************
 * Public Methods - Direct access to any serial port device define in Linux    *
 ******************************************************************************/

void librs232_init(DEV_RS232* dev, char* name, int timeout);
int librs232_open(DEV_RS232* dev, int baud);
int librs232_read(DEV_RS232* dev, char *data, int size);
int librs232_write(DEV_RS232* dev, char *data, int size);
int librs232_close(DEV_RS232* dev);

#endif
