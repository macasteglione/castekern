#ifndef UTILS_HEADER
#define UTILS_HEADER

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <malloc.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdlib.h>

struct AcceptedSocket
{
    int acceptedSocketFD;
    struct sockaddr_in address;
    int error;
    bool acceptedSuccessfully;
};

struct sockaddr_in *createIPv4Address(char *ip, int port);
int createTCPIpv4Socket();

#endif // !UTILS_HEADER