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
#define MAXBUFFLEN 200
int main()
{
    // their_addr -> server address
    int sockfd;
    struct sockaddr_in their_addr; // sockaddr_in is defined inside netinet.h
    socklen_t addr_len;
    int numbytes;
    char buf[MAXBUFFLEN];
    char arg[30];

    sockfd = socket(AF_INET /*address family*/, SOCK_DGRAM /*UPD type*/, 0 /*value for protocol depending on environment is assigned by udp*/); // Socket Creation

    if (sockfd == -1)
        perror("\t Socket Creation Failed\n"); // perror is defined inside sys/types.h
    else
        printf("\t Socket Creation Successfull\n");

    their_addr.sin_family = AF_INET;
    their_addr.sin_port = htons(SERVERPORT);             // htons converts host type to network type (here port no. is passed)
    their_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // IP Address (loopback address to test connection as both client and server are present in same system)

    printf(" Enter Your Full Name : ");
    gets(arg);

    sendto(sockfd /*created socket*/, arg /*message*/, strlen(arg) /*length*/, 0 /*flag value*/, (struct sockaddr *)&their_addr, sizeof their_addr);
    printf("\n Message Sent from Client to Server\n");
    printf("\n\t Sent Bytes to %s\n", inet_ntoa(their_addr.sin_addr)); // inet_ntoa is used to find how many bytes of data sender has passed

    recvfrom(sockfd, buf, MAXBUFFLEN - 1, 0, (struct sockaddr *)&their_addr, &addr_len);
    printf("\n Message Received from Server to Client\n");
    printf("\n\t Received Packet from %s\n", inet_ntoa(their_addr.sin_addr));
    // printf("\n Packet is %d bytes long\n", numbytes);
    // buf[numbytes] = '\0';
    printf("\n Short Form of Name : \"%s\"\n", buf);
    close(sockfd);
    return 0;
}
