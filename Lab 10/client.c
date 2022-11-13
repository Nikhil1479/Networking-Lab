// Client code in C to sort the array
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int sock;
    struct sockaddr_in server;
    int server_reply[6];
    int number[6] = {30, 10, 50, 8, 9, 21}, i, temp;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);

    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return 1;
    }

    puts("Connected\n");

    if (send(sock, &number, 6 * sizeof(int), 0) < 0)
    {
        puts("Send failed");
        return 1;
    }

    if (recv(sock, &server_reply, sizeof(int), 0) < 0)
    {
        puts("recv failed");
        return 0;
    }

    puts("Server reply :\n");
    int n = sizeof(server_reply) / sizeof(int);
    for (i = 0; i < n; i++)
    {
        printf("%d\n", server_reply[i]);
    }

    close(sock);
    return 0;
}
