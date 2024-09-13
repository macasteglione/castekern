#include "../include/server.h"

struct socket_entrante
{
    int socket_fd;
    struct sockaddr_in direccion;
    int error;
    int aceptadoCorrectamente; // booleano
};

void iniciar_socket_servidor(unsigned short port, char *ip)
{
    int socket_fd_servidor = crear_socket_tcp_ipv4();
    struct sockaddr_in *direccion = crear_dirreccion_ipv4(port, ip);

    int resultado = bind(socket_fd_servidor, (struct sockaddr *)direccion, sizeof(*direccion));

    if (resultado == 0)
        printf("El socket esta enlazado correctamente.\n");

    int resultado_listen = listen(socket_fd_servidor, 10);
    struct socket_entrante *socket_cliente = aceptar_mensaje_entrante(socket_fd_servidor);

    recibir_mensaje(socket_cliente->socket_fd, socket_fd_servidor);
}

void recibir_mensaje(int socket_fd_cliente, int socket_fd_servidor)
{
    char buffer[MAX_BUFFER];

    while (1)
    {
        ssize_t tamano_recibido = recv(socket_fd_cliente, buffer, MAX_BUFFER, 0);

        if (tamano_recibido > 0)
        {
            buffer[tamano_recibido] = 0;
            printf("La respuesta fue: %s\n", buffer);
        }

        if (tamano_recibido == 0)
            break;
    }

    close(socket_fd_cliente);
    shutdown(socket_fd_servidor, SHUT_RDWR);
}

struct socket_entrante *aceptar_mensaje_entrante(int socket_fd_servidor)
{
    struct sockaddr_in direccion_cliente;
    int tamano_direccion_cliente = sizeof(direccion_cliente);
    int socket_fd_cliente = accept(socket_fd_servidor, (struct sockaddr *)&direccion_cliente, &tamano_direccion_cliente);

    struct socket_entrante *socket_aceptado = malloc(sizeof(struct socket_entrante));
    socket_aceptado->direccion = direccion_cliente;
    socket_aceptado->socket_fd = socket_fd_cliente;
    socket_aceptado->aceptadoCorrectamente = socket_fd_cliente > 0;

    if (!socket_aceptado->aceptadoCorrectamente)
        socket_aceptado->error = socket_fd_cliente;

    return socket_aceptado;
}