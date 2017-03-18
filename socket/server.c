#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main()
{
	unsigned int port = 8080;
	int error;
	struct sockaddr_in server_addr;

	memset(&server_addr, 0, sizeof(struct sockaddr_in));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	inet_pton(AF_INET, "192.168.22.135", &server_addr.sin_addr.s_addr);

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1)
	{
		printf("Get sockfd error\n");
		exit(1);
	}
	error = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
	if(error == -1)
	{
		printf("bind() error!\n");
		exit(1);
	}
	error = listen(sockfd, 10);
	if(error == -1 )
	{
		printf("listen() error\n");
		exit(1);
	}

	printf("waiting for client's request\n");
	while(1)
	{
		struct sockaddr_in client_addr;
		char client_ip[INET_ADDRSTRLEN];
		socklen_t cliaddr_len = sizeof(client_addr);
		char buf[4096];
		int nbytes;
		int connfd;

		connfd = accept(sockfd, (struct sockaddr*)&client_addr, &cliaddr_len);
		if(connfd == -1)
		{
			printf("accept() error\n");
			continue;
		}
		nbytes = recv(connfd, buf, 4096, 0);
		if(nbytes == -1)
		{
			printf("recv() error\n");
			exit(1);
		}
		else if(nbytes == 0)
		{
			printf("The connection has been closed\n");
			close(connfd);
			continue;
		}

		inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, INET_ADDRSTRLEN);
		printf("information of client\n");
		printf("client ip=%s port=%d\n", client_ip, ntohs(client_addr.sin_port));

		printf("content is:\n%s\n", buf);
		sprintf(buf, "%d", strlen(buf));

		nbytes = send(connfd, buf, strlen(buf) + 1, 0);
		if(nbytes == -1)
		{
			printf("send() error\n");
			exit(1);
		}

		if(close(connfd) == -1)
		{
			printf("close() error\n");
			exit(1);
		}

		printf("client closed\n");
	}

	close(sockfd);
	return 0;
}
