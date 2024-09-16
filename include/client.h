#ifndef CLIENT_HEADER
#define CLIENT_HEADER

#include "utils.h"

void listeningThreadClient(int fd);
void showMsgClient(int socketFD);
void sendUserMsg(int socketFD);
void connectClient(char *ip, unsigned short port);

#endif // !CLIENT_HEADER