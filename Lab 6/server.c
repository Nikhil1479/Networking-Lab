#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <fcntl.h>
// #include <winsock2.h>

int main(int argc, char *argv[])
{
    printf("Server Status: Online\n");
    int sockfd, newSockFd, n, portNo;
    struct sockaddr_in server_add, client_add;

    char buffer[1024];

    socklen_t len;

    if (argc < 2)
    {
        printf("provide command line input: <PortNo>");
        exit(1);
    }

    portNo = atoi(argv[1]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
    {
        perror("Socket not created");
        exit(1);
    }
    server_add.sin_family = AF_INET;
    server_add.sin_addr.s_addr = INADDR_ANY;
    server_add.sin_port = htons(portNo);

    if (bind(sockfd, (struct sockaddr *)&server_add, sizeof(server_add)) < 0)
    {
        perror("Bind failed");
    }
    listen(sockfd, 5);
    len = sizeof(client_add);

    newSockFd = accept(sockfd, (struct sockaddr *)&client_add, &len);
    if (newSockFd < 0)
    {
        perror("Error in accepting request");
        exit(1);
    }

    while (1)
    {
        bzero(buffer, 1024);
        n = read(newSockFd, buffer, 1024);
        if (n < 0)
        {
            perror("Error in reading data");
            exit(1);
        }
        printf("Client: %s", buffer);

        bzero(buffer, 1024);

        fgets(buffer, 1024, stdin);
        n = write(newSockFd, buffer, 1024);

        if (n < 0)
        {
            perror("Error in writing data");
            exit(1);
        }

        if (!strncmp("exit", buffer, 4))
        {
            break;
        }
    }
    close(sockfd);
    close(newSockFd);
    printf("Server Status: Offline");
    return 0;
}