#ifndef CLIENT_HEADER
#define CLIENT_HEADER

#include "utils.h"

#define MAX_BUFFER 1024

void startListeningAndPrintMessagesOnNewThread(int fd);
void listenAndPrint(int socketFD);
void readConsoleEntriesAndSendToServer(int socketFD);
void conectarCliente(char *ip, unsigned short port);

#endif // !CLIENT_HEADER