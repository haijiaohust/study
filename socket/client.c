#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
	const max_len = 1024;
	struct sockaddr_in sin;
	int sfd;
	int port = 8080;
	char str[1024];
	char buf[max_len];
	int error;

	if(argc < 2)
	{
		printf("arguments error\n");
	}
	strcpy(str, argv[1]);

	memset(&sin, 0, sizeof(struct sockaddr_in));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	inet_pton(AF_INET, "192.168.22.135", &sin.sin_addr);

	sfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sfd == -1)
	{
		printf("socket() error\n");
		exit(1);
	}

	error = connect(sfd, (struct sockaddr*)&sin, sizeof(sin));
	if(error == -1)
	{
		printf("connect() error\n");
		exit(1);
	}

	error = send(sfd, str, strlen(str) + 1, 0);
	if(error == -1)
	{
		printf("send() error");
		exit(1);
	}

	error = recv(sfd, buf, max_len, 0);
	if(error == -1)
	{
		printf("recv() error\n");
		exit(1);
	}

	printf("the length of str is: %s\n", buf);

	if(close(sfd) == -1)
	{
		printf("close() error\n");
		exit(1);
	}

	return 0;
}