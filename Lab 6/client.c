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
    int sockfd, portNo, n;
    char buffer[1024];

    struct sockaddr_in serverAddress;

    socklen_t len;
    if (argc < 3)
    {
        printf("Provide command line input\n <server_IP_Address> <portNo>");
    }

    portNo = atoi(argv[2]);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
    {
        perror("Socket Not created");
        exit(1);
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(argv[1]);
    serverAddress.sin_port = htons(portNo);

    if (connect(sockfd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
        perror("Connection failed......");
        exit(1);
    }

    while (1)
    {
        bzero(buffer, 1024);
        fgets(buffer, 1024, stdin);

        n = write(sockfd, buffer, strlen(buffer));

        if (n < 0)
        {
            perror("Error in writing");
            exit(1);
        }
        bzero(buffer, 1024);

        n = read(sockfd, buffer, 1024);
        if (n < 0)
        {
            perror("Error in reading....");
            exit(1);
        }
        printf("Server: %s", buffer);
        if (!strncmp("exit", buffer, 4))
        {
            break;
        }
    }
    close(sockfd);
    return 0;
}