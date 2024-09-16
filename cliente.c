#include "include/client.h"

int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        printf("Uso: [ip del servidor] [puerto]\n");
        exit(EXIT_FAILURE);
    }

    connectClient(argv[1], atoi(argv[2]));

    exit(EXIT_SUCCESS);
}