#ifndef SERVER_HEADER
#define SERVER_HEADER

#include "utils.h"

#define MAX_BUFFER 1024

struct socket_entrante;
void iniciar_socket_servidor(unsigned short port, char *ip);
void recibir_mensaje(int socket_fd_cliente, int socket_fd_servidor);
struct socket_entrante *aceptar_mensaje_entrante(int socket_fd_servidor);

#endif // !SERVER_HEADER