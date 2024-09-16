#include "../include/server.h"

struct AcceptedSocket acceptedSockets[MAX_SOCKETS];
int acceptedSocketsCount = 0;

void initServer(char *ip, unsigned short port)
{
    int serverSocketFD = createTCPIpv4Socket();
    struct sockaddr_in *serverAddress = createIPv4Address(ip, port);

    int result = bind(serverSocketFD, serverAddress, sizeof(*serverAddress));
    if (result < 0)
        printf("Error: %s:%d ya esta en uso.\n", ip, port);
    else
    {
        printf("Socket conectado en %s:%d\n", ip, port);
        listen(serverSocketFD, 10);

        listeningConnections(serverSocketFD);
    }

    shutdown(serverSocketFD, SHUT_RDWR);
    close(serverSocketFD);
}

void listeningConnections(int serverSocketFD)
{
    while (1)
    {
        struct AcceptedSocket *clientSocket = acceptConnection(serverSocketFD);
        acceptedSockets[acceptedSocketsCount++] = *clientSocket;
        listeningThreadServer(clientSocket);
    }
}

void listeningThreadServer(struct AcceptedSocket *pSocket)
{
    pthread_t id;
    pthread_create(&id, NULL, showMsgServer, pSocket->socketFD);
}

void showMsgServer(int socketFD)
{
    struct AcceptedSocket *client = NULL;

    for (int i = 0; i < acceptedSocketsCount; i++)
        if (acceptedSockets[i].socketFD == socketFD)
        {
            client = &acceptedSockets[i];
            break;
        }

    char buffer[MAX_BUFFER];

    while (1)
    {
        ssize_t amountReceived = recv(socketFD, buffer, MAX_BUFFER, 0);

        if (amountReceived > 0)
        {
            buffer[amountReceived] = 0;
            printf("%s\n", buffer);

            broadcastMsg(buffer, socketFD);
        }

        if (amountReceived == 0)
        {
            /*
            if (client != NULL)
            {
                printf("'%s' se ha desconectado.\n", client->userName);
                broadcastMsg(strcat(client->userName, " se ha desconectado."), socketFD);
            }
            */
            break;
        }
    }

    close(socketFD);
}

void broadcastMsg(char *buffer, int socketFD)
{
    for (int i = 0; i < acceptedSocketsCount; i++)
        if (acceptedSockets[i].socketFD != socketFD)
            send(acceptedSockets[i].socketFD, buffer, strlen(buffer), 0);
}

struct AcceptedSocket *acceptConnection(int serverSocketFD)
{
    struct sockaddr_in clientAddress;
    int clientAddressSize = sizeof(struct sockaddr_in);
    int clientSocketFD = accept(serverSocketFD, &clientAddress, &clientAddressSize);

    struct AcceptedSocket *acceptedSocket = malloc(sizeof(struct AcceptedSocket));
    acceptedSocket->address = clientAddress;
    acceptedSocket->socketFD = clientSocketFD;
    acceptedSocket->isAceppted = clientSocketFD > 0;

    /*
    if (acceptedSocket->isAceppted)
    {
        // Recibir el nombre del cliente
        char userName[MAX_BUFFER];
        ssize_t nameLength = recv(clientSocketFD, userName, sizeof(userName), 0);

        if (nameLength > 0)
        {
            userName[nameLength] = '\0';
            strncpy(acceptedSocket->userName, userName, sizeof(acceptedSocket->userName) - 1); // Copiar el nombre recibido
            acceptedSocket->userName[sizeof(acceptedSocket->userName) - 1] = '\0';             // Asegurar terminación en nulo

            // Crear un mensaje de conexión
            char connectMsg[MAX_BUFFER];
            snprintf(connectMsg, sizeof(connectMsg), "'%s' se ha conectado al chat.", acceptedSocket->userName);

            // Imprimir y difundir el mensaje de conexión
            printf("Cliente conectado '%s'\n", acceptedSocket->userName);
            broadcastMsg(connectMsg, clientSocketFD);
        }
    }
    */

    if (!acceptedSocket->isAceppted)
        acceptedSocket->error = clientSocketFD;

    return acceptedSocket;
}