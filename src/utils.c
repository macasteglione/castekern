#include "../include/utils.h"

struct sockaddr_in *crear_dirreccion_ipv4(unsigned short port, char *ip)
{
    struct sockaddr_in *direccion = malloc(sizeof(struct sockaddr_in));

    direccion->sin_family = AF_INET; // direccion ipv4
    direccion->sin_port = htons(port);

    if (strlen(ip) == 0)
        direccion->sin_addr.s_addr = INADDR_ANY;
    else
        inet_pton(AF_INET, ip, &direccion->sin_addr.s_addr);

    return direccion;
}

int crear_socket_tcp_ipv4()
{
    return socket(AF_INET, SOCK_STREAM, 0);
}