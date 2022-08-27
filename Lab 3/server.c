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
#define MYPORT 6000
#define MAXBUFFLEN 200
int main()
{
    int sockfd;
    struct sockaddr_in my_addr;
    struct sockaddr_in their_addr;
    socklen_t addr_len;
    int numbytes;
    char buf[MAXBUFFLEN];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1)
        perror("\t Socket Error"); // included in <sys/socket.h> header file
    else
        printf("\t Success");

    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(MYPORT); // host to network
    my_addr.sin_addr.s_addr = INADDR_ANY;

    int b = bind(sockfd, (struct sockaddr *)&my_addr, sizeof(my_addr));
    if (b == -1)
        perror("\t Bind Error");
    else
        printf("\t Success");

    addr_len = sizeof their_addr;
    recvfrom(sockfd, buf, MAXBUFFLEN - 1, 0, (struct sockaddr *)&their_addr, &addr_len);

    printf("\n\t Received Packet from %s\n", inet_ntoa(their_addr.sin_addr));
    // printf("packet is %d bytes long\n", numbytes);
    // buf[numbytes] = '\0';
    printf("\n Packet contains \"%s\"\n", buf);
    close(sockfd);
    return 0;
}