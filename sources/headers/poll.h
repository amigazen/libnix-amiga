#ifndef _HEADERS_POLL_H
#define _HEADERS_POLL_H

#include <sys/types.h>

/* Poll events */
#define POLLIN     0x0001  /* There is data to read */
#define POLLPRI    0x0002  /* There is urgent data to read */
#define POLLOUT    0x0004  /* Writing now will not block */
#define POLLERR    0x0008  /* Error condition */
#define POLLHUP    0x0010  /* Hung up */
#define POLLNVAL   0x0020  /* Invalid request: fd not open */

/* Poll structure */
struct pollfd {
    int fd;         /* file descriptor */
    short events;   /* events to look for */
    short revents; /* events returned */
};

/* Function prototypes */
extern int poll(struct pollfd *fds, unsigned int nfds, int timeout);

#endif /* _HEADERS_POLL_H */
