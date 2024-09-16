#ifndef UTILS_HEADER
#define UTILS_HEADER

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <malloc.h>
#include <pthread.h>
#include <stdlib.h>

#define MAX_BUFFER 1024
#define MAX_SOCKETS 10
#define MAX_NAMESIZE 50

struct AcceptedSocket
{
    int socketFD;
    struct sockaddr_in address;
    int error;
    int isAceppted; // boolean
    char userName[MAX_NAMESIZE];
};

struct sockaddr_in *createIPv4Address(char *ip, int port);
int createTCPIpv4Socket();

#endif // !UTILS_HEADER