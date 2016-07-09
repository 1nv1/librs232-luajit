/*
 *  librs232.c
 *  Author: Nelson Lombardo (C) 2013-2016
 *  e-mail: nelson.lombardo@gmail.com
 *  License: MIT
 */

#include "librs232.h"

void librs232_init(DEV_RS232* dev, char* name, int timeout)
{
	int i;
	dev->connect = 0;
	dev->fd = -1;
	dev->timeout = timeout;
	for(i=0; (i < DEV_NAME_LEN)||(*(name + i)!='\0');  i++)
	{
		*(dev->name + i) = *(name + i);
	}
}

int librs232_open(DEV_RS232* dev, int baud)
{
	struct termios newtermios;
	speed_t baudios;
  dev->fd = open(dev->name,O_RDWR | O_NOCTTY); 

  newtermios.c_cflag |= CBAUD | CS8 | CLOCAL | CREAD;
  newtermios.c_iflag = IGNPAR;
  newtermios.c_oflag &= ~(ICANON | ECHO | ECHOE | ISIG);
  newtermios.c_lflag &=  ~OPOST;
  newtermios.c_cc[VMIN]=0;
  newtermios.c_cc[VTIME]=0;

	switch(baud) {
		case 9600:
			baudios = B9600;
			break;
		case 19200:
			baudios = B19200;
			break;
		case 38400:
			baudios = B38400;
			break;
		case 115200:
			baudios = B115200;
			break;
			baudios = B9600;
	}
  cfsetospeed(&newtermios, baudios);
  cfsetispeed(&newtermios, baudios);
  
  dev->baud = baudios;

  if (tcflush(dev->fd,TCIFLUSH)==-1) return(EXIT_FAILURE);
  if (tcflush(dev->fd,TCOFLUSH)==-1) return(EXIT_FAILURE);
  if (tcsetattr(dev->fd,TCSANOW,&newtermios)==-1) return(EXIT_FAILURE);  
 
	dev->connect = 1;
  return(EXIT_SUCCESS);
}

int librs232_read(DEV_RS232* dev, char* data, int size)
{
	fd_set fds;
	struct timeval timeout;
	int count=0;
	int ret;
	int n;
	do {    
		FD_ZERO(&fds);
		FD_SET(dev->fd, &fds);
		timeout.tv_sec = 0;  
		timeout.tv_usec = dev->timeout;
		ret = select (dev->fd + 1, &fds, NULL, NULL, &timeout);
		if (ret > 0) {
			n = read (dev->fd, (data + count), size-count);
			count += n;
			data[count] = 0;
		}
	} while ((count < size) && (ret == 1));
	return(count);
}

int librs232_write (DEV_RS232* dev, char* data, int size)
{
	return(write(dev->fd, data, size));
}

int librs232_close(DEV_RS232* dev)
{
	dev->connect = 0;
	return(close(dev->fd));
}
