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

#define BACKLOG_LEN 10
#define LISTEN_PORT 12345

int socket_fd;

static void
stop_server(int signo)
{
    printf("\nSIGINT received, shutting down.\n");
    fflush(stdout);
    printf("Closing socket: %d \n", socket_fd);
    close(socket_fd);
    exit(0);
}

void main()
{

    printf("Starting server...\n");
    signal(SIGINT, stop_server);

    // Create a socket
    socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in my_addr;

    my_addr.sin_family = AF_INET;
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    my_addr.sin_port = htons(LISTEN_PORT);

    // Bind
    if (bind(socket_fd, (struct sockaddr *)&my_addr, sizeof(my_addr)) == -1)
    {
        printf("Error binding: %s \n", strerror(errno));
        exit(-1);
    }

    // Listen
    if (listen(socket_fd, BACKLOG_LEN) == -1)
    {
        printf("Error Listening: %s \n", strerror(errno));
        exit(-1);
    }

    printf("Server is listening on port %d \n", LISTEN_PORT);
    fflush(stdout);

    struct sockaddr_in peer_addr;

    for (;;)
    {
        int len = sizeof(peer_addr);
        int conn_fd = accept(socket_fd, (struct sockaddr *)&peer_addr, &len);
        if (conn_fd < 0)
        {
            printf("Accept failed: %s\n", strerror(errno));
        }
        char buf[10];
        memset(buf, 0, sizeof(buf));
        char s_addr[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &peer_addr.sin_addr, s_addr, sizeof(s_addr));

        printf("Accepted connection from %s:%d \n", s_addr, ntohs(peer_addr.sin_port));

        for (;;)
        {
            int read_size;
            read_size = read(conn_fd, buf, 10);
            if (read_size == 0)
            {
                break;
            }
            printf("%s", buf);
            fflush(stdout);
            write(conn_fd, buf, 10);
        }
        close(conn_fd);
    }
}
