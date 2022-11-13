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

#define PORT 6080
#define MAXLINE 1024

int main()
{
    char msg[100];

    char buf[MAXLINE];
    struct sockaddr_in servaddr, cliaddr;

    int sockfd;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sockfd < 0)
    {
        perror("Socket not created");
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    int status;
    status = bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    if (status < 0)
    {
        perror("Binding Failed");
        // exit(EXIT_FAILURE);
    }

    int len, n;

    len = sizeof(cliaddr);
    n = recvfrom(sockfd, (char *)buf, 1024, 0, (struct sockaddr *)&cliaddr, &len);

    buf[n] = '\0';

    printf("Client: %s\n", buf);

    printf("Enter a Message: ");
    gets(msg);

    sendto(sockfd, msg, strlen(msg), 0, (struct sockaddr *)&cliaddr, len);
    printf("\nMessage sent from server");
    close(sockfd);
    return 0;
}