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
int main()
{
    int buf[1024];
    int len, n;
    char msg[50];
    struct sockaddr_in servaddr;
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sockfd < 0)
    {
        perror("Socket not created");
    }
    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);

    // int status;
    // status = bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    // if (status < 0)
    // {
    //     perror("Binding failed");
    // }

    printf("Enter a message: ");
    gets(msg);
    len = sizeof(servaddr);
    sendto(sockfd, msg, strlen(msg), 0, (struct sockaddr *)&servaddr, len);
    printf("Message sent from client\n");

    n = recvfrom(sockfd, (char *)buf, 1024, 0, (struct sockaddr *)&servaddr, &len);
    buf[n] = '\0';
    printf("Server: %s", buf);
    close(sockfd);
    return 0;
}