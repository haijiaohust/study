#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
	unsigned int port = 8080;
	int error;
	struct sockaddr_in server_addr;
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		printf("Get sockfd error\n");
		exit(0);
	}

	memset(&server_addr, 0, sizeof(struct sockaddr_in));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	inet_pton(AF_INET, "192.168.22.135", &server_addr.sin_addr.s_addr);

	error = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
	if(error < 0)
	{
		printf("bind() error!\n");
		exit(0);
	}

	error = listen(sockfd, 10);
	if(error < 0)
	{
		printf("listen() error\n");
		exit(0);
	}

	printf("waiting for client's request\n");
	while(1)
	{
		struct sockaddr_in client_addr;
		char client_ip[INET_ADDRSTRLEN];
		socklen_t cliaddr_len = sizeof(client_addr);
		char buf[4096];
		int buf_len;

		int connfd;
		connfd = accept(sockfd, (struct sockaddr*)&client_addr, &cliaddr_len);
		if(connfd < 0)
		{
			printf("accept() error\n");
			continue;
		}

		inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, INET_ADDRSTRLEN);
		printf("information of client\n");
		printf("client ip=%s port=%d\n", client_ip, ntohs(client_addr.sin_port));

		buf_len = read(connfd, buf, 4096);

		printf("%s\n", buf);

		write(connfd, buf, buf_len);

		close(connfd);
		printf("client closed\n");
	}

	close(sockfd);

	return 0;
}
