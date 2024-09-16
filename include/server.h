#ifndef SERVER_HEADER
#define SERVER_HEADER

#include "utils.h"

struct AcceptedSocket *acceptConnection(int serverSocketFD);
void listeningThreadServer(struct AcceptedSocket *pSocket);
void showMsgServer(int socketFD);
void listeningConnections(int serverSocketFD);
void broadcastMsg(char *buffer, int socketFD);
void initServer(char *ip, unsigned short port);

#endif // !SERVER_HEADER