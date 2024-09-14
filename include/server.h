#ifndef SERVER_HEADER
#define SERVER_HEADER

#include "utils.h"

#define MAX_BUFFER 1024

struct AcceptedSocket *acceptIncomingConnection(int serverSocketFD);
void acceptNewConnectionAndReceiveAndPrintItsData(int serverSocketFD);
void receiveAndPrintIncomingData(int socketFD);
void startAcceptingIncomingConnections(int serverSocketFD);
void receiveAndPrintIncomingDataOnSeparateThread(struct AcceptedSocket *pSocket);
void sendReceivedMessageToTheOtherClients(char *buffer, int socketFD);
void iniciarServidor(char *ip, unsigned short port);

#endif // !SERVER_HEADER