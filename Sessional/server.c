#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    int sockfd, newSocket, port, clientLen, n;
    char buffer[1024];
    struct sockaddr_in serverAddr;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size;
    int i;

    sockfd = socket(PF_INET, SOCK_STREAM, 0);

    port = 7891;

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

    bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

    if (listen(sockfd, 5) == 0)
        printf("Listening\n");
    else
        printf("Error\n");

    addr_size = sizeof serverStorage;

    while (1)
    {
        newSocket = accept(sockfd, (struct sockaddr *)&serverStorage, &addr_size);
        if (!fork())
        {
            n = 1;
            while (n != 0)
            {
                n = recv(newSocket, buffer, 1024, 0);

                for (i = 0; i < n - 1; i++)
                {
                    if (buffer[i] > 'a' && buffer[i] <= 'z')
                        buffer[i] = toupper(buffer[i]);

                    else
                    {
                        buffer[i] = tolower(buffer[i]);
                    }
                }

                send(newSocket, buffer, n, 0);
            }
            close(newSocket);
            exit(0);
        }
        else
        {
            close(newSocket);
        }
    }

    return 0;
}