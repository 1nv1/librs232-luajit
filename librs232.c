/*
 *  librs232.c
 *  Author: Nelson Lombardo (C) 2013
 *  e-mail: nelson.lombardo@gmail.com
 *  License: MIT
 */

#include "librs232.h"

int serial_open(char *serial_name, speed_t baud)
{
    struct termios newtermios;
    int fd;

    fd = open(serial_name,O_RDWR | O_NOCTTY); 

    newtermios.c_cflag |= CBAUD | CS8 | CLOCAL | CREAD;
    newtermios.c_iflag = IGNPAR;
    newtermios.c_oflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    newtermios.c_lflag &=  ~OPOST;
    newtermios.c_cc[VMIN]=0;
    newtermios.c_cc[VTIME]=0;

    cfsetospeed(&newtermios,baud);
    cfsetispeed(&newtermios,baud);

    if (tcflush(fd,TCIFLUSH)==-1) return -1;
    if (tcflush(fd,TCOFLUSH)==-1) return -1;
    if (tcsetattr(fd,TCSANOW,&newtermios)==-1) return -1;  
 
    return fd;
}

int seria_read(int serial_fd, char *data, int size, int timeout_usec)
{
    fd_set fds;
    struct timeval timeout;
    int count=0;
    int ret;
    int n;

    do {    
        FD_ZERO(&fds);
        FD_SET (serial_fd, &fds);

        timeout.tv_sec = 0;  
        timeout.tv_usec = timeout_usec;

        ret = select (serial_fd+1, &fds, NULL, NULL, &timeout);

        if (ret > 0) {
            n = read (serial_fd, (data + count), size-count);
        count += n;
        data[count] = 0;
        }
    } while ((count < size) && (ret == 1));
    return count;
}

void serial_write (int serial_fd, char *data, int size)
{
    write(serial_fd, data, size);
}

void serial_close(int fd)
{
    close(fd);
}
