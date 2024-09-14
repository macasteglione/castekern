# Chat TCP con Broadcast Multithreading

Este es un programa de servidor-cliente basado en sockets TCP que permite a múltiples clientes conectarse y enviar mensajes a través de un servidor.

## Instalación

**Clona el repositorio** (o copiar el código fuente a tu directorio local):

```sh
git clone https://github.com/macasteglione/chat-room
```

**Compilá** el servidor y cliente:

```sh
make cliente && make servidor
```

## Uso

### 1. Ejecutar el servidor

Primero debes crear el servidor con una dirección ip y un puerto.

```sh
./bin/servidor [ip] [puerto]
```
### 2. Ejecutar los clientes

Con el servidor en marcha, conecte el cliente utilizando la dirección ip y el puerto del servidor.

```sh
./bin/cliente [ip] [puerto]
```

Una vez que el cliente esté conectado, puedes escribir mensajes en la consola y enviarlos al servidor. Para salir, escribe salir y presiona Enter.