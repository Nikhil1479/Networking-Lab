#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#define SERVERPORT 6000
int main()
{
    int sockfd;
    struct sockaddr_in their_addr;
    int numbytes;
    char arg[30];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1)
        perror("\t Socket Error");
    else
        printf("\t Success");

    their_addr.sin_family = AF_INET;
    their_addr.sin_port = htons(SERVERPORT);
    their_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // loopback address

    printf(" Enter a Message : ");
    gets(arg);

    sendto(sockfd, arg, strlen(arg), 0, (struct sockaddr *)&their_addr, sizeof their_addr);
    printf("\n\t Sent Bytes to %s\n", inet_ntoa(their_addr.sin_addr)); // inet_ntoa -> helps to find out how many bytes are send
    close(sockfd);
    return 0;
}