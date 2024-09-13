#ifndef CLIENT_HEADER
#define CLIENT_HEADER

#include "utils.h"

#define MAX_BUFFER 1024

void iniciar_socket_cliente(unsigned short port, char *ip);
void enviar_mensaje(int socket_fd);

#endif // !CLIENT_HEADER