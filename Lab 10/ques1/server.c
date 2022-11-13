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
#define MAXBUFFLEN 200 // how many bytes server can read is defined
int main()
{
    // their_addr -> server address
    // my_addr -> client address
    int sockfd;
    struct sockaddr_in my_addr;
    struct sockaddr_in their_addr;
    socklen_t addr_len;
    int numbytes;
    char buf[MAXBUFFLEN];
    char arg[30];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1)
        perror("\t Socket Creation Failed\n");
    else
        printf("\t Socket Creation Successfull\n");

    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(MYPORT);
    my_addr.sin_addr.s_addr = INADDR_ANY; // INADDR_ANY is used to get IP address of the server if both client and server are running in same host

    int b = bind(sockfd, (struct sockaddr *)&my_addr, sizeof(my_addr)); // bind -> add the port no. and IP address
    if (b == -1)
        perror("\t Binding Failed\n");
    else
        printf("\t Binding Successfull \n");

    addr_len = sizeof their_addr;

    recvfrom(sockfd, buf, MAXBUFFLEN - 1, 0, (struct sockaddr *)&their_addr, &addr_len);
    printf("\n Message Received from Client to Server\n");
    printf("\n\t Received Packet from %s\n", inet_ntoa(their_addr.sin_addr));
    // printf("\n Packet is %d bytes long\n", numbytes);
    // buf[numbytes] = '\0';
    printf("\n Packet contains \"%s\"\n", buf);

    int i, j = 0, m = 0;
    char abrevname[10];
    for (int i = 0; i < strlen(buf); i++)
    {
        abrevname[m] = buf[j];
        if (buf[i] == ' ')
        {
            m = m + 1;
            j = i;
            abrevname[m] = buf[j];
            j++;
        }
    }
    abrevname[m + 1] = '\0';

    sendto(sockfd /*created socket*/, abrevname /*message*/, strlen(abrevname) /*length*/, 0 /*flag value*/, (struct sockaddr *)&their_addr, sizeof their_addr);
    printf("\n Message Sent from Server to Client\n");
    printf("\n\t Sent Bytes to %s\n", inet_ntoa(their_addr.sin_addr)); // inet_ntoa is used to find how many bytes of data sender has passed

    close(sockfd);
    return 0;
}
