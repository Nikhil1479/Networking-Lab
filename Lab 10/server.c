#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

// void delete (int *A, int);
void oddNo(int list[], int newList[], int n);
void oddNo(int list[], int newList[], int n)
{
    // int newList[n];
    for (int i = 0; i < n; i++)
    {
        if (list[i] % 2 != 0)
        {
            newList[i] = list[i];
        }
    }
}

// void delete (int *A, int index)
// {
//     int x, i;

//     x = A[index];
//     if (index >= 0 && index <= 6)
//     {
//         for (i = index; i < 6; i++)
//         {
//             A[i] = A[i + 1];
//         }
//     }
//     else
//     {
//         printf("\nInvalid Index");
//     }
// }
int main(int argc, char *argv[])
{
    int socket_desc, client_sock, c, read_size;
    struct sockaddr_in server, client;
    int message[6], newList[6], i;

    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);

    if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
    {

        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");

    listen(socket_desc, 3);

    puts("Waiting for incoming connection");
    c = sizeof(struct sockaddr_in);

    client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t *)&c);

    if (client_sock < 0)
    {
        perror("accept failed");
        return 1;
    }

    puts("Connection accepted");

    while ((read_size = recv(client_sock, &message, 6 * sizeof(int), 0)) > 0)
    {

        oddNo(&message, &newList, 6);

        write(client_sock, &newList, sizeof(int));
    }

    if (read_size == 0)
    {
        puts("Client disconnected");
    }
    else if (read_size == -1)
    {
        perror("recv failed");
    }

    return 0;
}
