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

	if(sfd < 0)
	{
		printf("socket() error\n");
		exit(-1);
	}

	connect(sfd, (struct sockaddr*)&sin, sizeof(sin));

	write(sfd, str, strlen(str) + 1);

	read(sfd, buf, max_len);

	printf("%s\n", buf);

	close(sfd);
	return 0;
}