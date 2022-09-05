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
int main()
{
    int sockfd, fdl, i, length;
    char buf[100];
    struct sockaddr_in sa, tal;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = INADDR_ANY;
    sa.sin_port = 60018;

    i = bind(sockfd, (struct sockaddr *)&sa, sizeof(sa));
    printf("TEST %d%d\n", sockfd, i);

    listen(sockfd, 5);

    // length = sizeof(sa);
    fdl = accept(sockfd, (struct sockaddr *)&tal, &length);

    for (i = 0; i < 100; i++)
    {
        buf[i] = '\0';
        strcpy(buf, "Message from Server");
        send(fdl, buf, 100, 0);
    }

    for (i = 0; i < 100; i++)
    {
        buf[i] = '\0';
    }
    recv(fdl, buf, 100, 0);
    printf("%s\n", buf);

    close(sockfd);
    return 0;
}