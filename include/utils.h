#ifndef UTILS_HEADER
#define UTILS_HEADER

#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <malloc.h>

struct sockaddr_in *crear_dirreccion_ipv4(unsigned short port, char *ip);


int crear_socket_tcp_ipv4();

#endif // !UTILS_HEADER