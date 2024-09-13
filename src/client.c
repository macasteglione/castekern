#include "../include/client.h"

void iniciar_socket_cliente(unsigned short port, char *ip)
{
    int socket_fd_cliente = crear_socket_tcp_ipv4();
    struct sockaddr_in *direccion = crear_dirreccion_ipv4(port, ip);

    int resultado = connect(socket_fd_cliente, (struct sockaddr *)direccion, sizeof(*direccion));

    if (resultado == 0)
        printf("La conexion fue exitosa.\n");

    enviar_mensaje(socket_fd_cliente);
}

void enviar_mensaje(int socket_fd_cliente)
{
    char *line = NULL;
    size_t tamano_linea = 0;
    printf("Escriba un mensaje para enviar (escriba 'salir' para cerrar):\n");

    while (1)
    {
        ssize_t contador_char = getline(&line, &tamano_linea, stdin);

        if (tamano_linea > 0)
        {
            if (strcmp(line, "salir\n") == 0)
                break;

            ssize_t tamano_enviado = send(socket_fd_cliente, line, tamano_linea, 0);
        }
    }

    close(socket_fd_cliente);
    shutdown(socket_fd_cliente, SHUT_RDWR);
}