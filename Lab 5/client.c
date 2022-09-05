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
	int sockfd, i;
	char buf[100];
	struct sockaddr_in sa;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = inet_addr("127.0.0.1");
	sa.sin_port = 60018;

	i = connect(sockfd, (struct sockaddr *)&sa, sizeof(sa));

	for (int j = 0; j < 100; j++)
	{
		recv(sockfd, buf, 100, 0);
	}
	printf("%s\n", buf);

	for (int k = 0; k < 100; k++)
	{
		buf[k] = '\0';
	}
	strcpy(buf, "Message from Client");
	send(sockfd, buf, 100, 0);

	close(sockfd);
	return 0;
}