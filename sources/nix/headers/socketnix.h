
#ifndef SOCKET_COMMON_H
#define SOCKET_COMMON_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <proto/socket.h>

/* Socket address families */
#ifndef AF_INET
#define AF_INET 2
#endif

/* Error codes */
#ifndef EAFNOSUPPORT
#define EAFNOSUPPORT 97
#endif

#endif /* SOCKET_COMMON_H */
