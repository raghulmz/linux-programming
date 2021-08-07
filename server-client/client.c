#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>

#define SERVER_ADDR "127.0.0.1"
#define SERVER_PORT 12345
#define MESSAGE "hello!\n"

void main()
{
    // Create a socket
    int socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in my_addr;

    my_addr.sin_family = AF_INET;
    my_addr.sin_addr.s_addr = inet_addr(SERVER_ADDR);
    my_addr.sin_port = htons(SERVER_PORT);

    if (connect(socket_fd, (struct sockaddr *)&my_addr, sizeof(my_addr)) < 0)
    {
        printf("Error connecting to server %s:%d %s", SERVER_ADDR, SERVER_PORT, strerror(errno));
    }

    char message[50] = MESSAGE;
    if (write(socket_fd, message, sizeof(message)) < 0)
    {
        printf("Error witing message to socket\n");
        exit(EXIT_FAILURE);
    }

    char recevied[50];
    memset(recevied, 0, sizeof(recevied));
    if (read(socket_fd, recevied, sizeof(message)) < 0)
    {
        printf("Error reading from fd %d\n", socket_fd);
        exit(EXIT_FAILURE);
    }
    printf("%s", recevied);
    fflush(stdout);
    exit(EXIT_SUCCESS);
}