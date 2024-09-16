#include "../include/client.h"

void connectClient(char *ip, unsigned short port)
{
    int socketFD = createTCPIpv4Socket();
    struct sockaddr_in *address = createIPv4Address(ip, port);

    int result = connect(socketFD, address, sizeof(*address));
    if (result < 0)
        printf("Error al conectar a %s:%d\n", ip, port);
    else
    {
        printf("Conectado a %s:%d\n", ip, port);
        listeningThreadClient(socketFD);
        sendUserMsg(socketFD);
    }

    close(socketFD);
}

void sendUserMsg(int socketFD)
{
    char buffer[MAX_BUFFER];

    char *name = NULL;
    size_t nameSize = 0;
    printf("Ingresa tu nombre: ");
    ssize_t nameCount = getline(&name, &nameSize, stdin);
    name[nameCount - 1] = 0;

    //send(socketFD, name, strlen(name), 0);

    char *line = NULL;
    size_t lineSize = 0;
    printf("Bienvenido al chat (Escriba 'salir' para cerrar)...\n");

    while (1)
    {
        ssize_t charCount = getline(&line, &lineSize, stdin);
        line[charCount - 1] = 0;

        sprintf(buffer, "%s >> %s", name, line);

        if (charCount > 0)
        {
            if (strcmp(line, "salir") == 0)
                break;

            ssize_t amountWasSent = send(socketFD, buffer, strlen(buffer), 0);
        }
    }
}

void listeningThreadClient(int socketFD)
{
    pthread_t id;
    pthread_create(&id, NULL, showMsgClient, socketFD);
}

void showMsgClient(int socketFD)
{
    char buffer[MAX_BUFFER];

    while (1)
    {
        ssize_t amountReceived = recv(socketFD, buffer, MAX_BUFFER, 0);

        if (amountReceived > 0)
        {
            buffer[amountReceived] = 0;
            printf("%s\n", buffer);
        }

        if (amountReceived == 0)
        {
            printf("El servidor se ha desconectado.\n");
            break;
        }
    }

    close(socketFD);
}