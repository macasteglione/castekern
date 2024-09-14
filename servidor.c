#include "include/server.h"

int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        printf("Uso: [ip del servidor] [puerto]\n");
        exit(EXIT_FAILURE);
    }

    iniciarServidor(argv[1], atoi(argv[2]));

    exit(EXIT_SUCCESS);
}