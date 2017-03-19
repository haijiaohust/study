#include "web.h"

int main()
{
	struct sockaddr_in sin, cin;
	socklen_t len = sizeof(struct sockaddr_in);
	int sfd, cfd, file_fd;
	pid_t pid;
	int sock_opt = 1;
	unsigned short port;
	char path[256];
	int err;
	struct stat statbuf;
	signal(SIGCHLD, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);

	printf("initializing...\n");
	err = init(&sin, &sfd, &port, path);
	if(err == -1)
	{
		DEBUG_PRINT("init() error\n");
		exit(1);
	}

	while(1)
	{
		DEBUG_PRINT("waiting for connection...\n");
		cfd = accept(sfd, (struct sockaddr*)&cin, &len);
		if(cfd == -1)
		{
			DEBUG_PRINT("accept() error\n");
			exit(1);
		}

		pid = fork();
		if(pid < 0)
		{
			DEBUG_PRINT("fork() error\n");
			exit(1);
		}
		else if(pid == 0)
		{
			close(sfd);
			if(get_path(cfd, path) == -1)
			{
				DEBUG_PRINT("got filepath error\n");
				exit(1);
			}
			if (file_fd = open(path, O_RDONLY) < 0)
			{
				error_page(file_fd);
				printf("cannot open file\n");
				close(cfd);
				exit(0);
			}

			write_page(cfd, path, file_fd);
			close(file_fd);
			close(cfd);
			exit(0);
		}
		else close(cfd);
	}
	return 0;
}

int init(struct sockaddr_in* sin, int *fd, unsigned short *port, char *path)
{
	int err;
	*port = 8080;
	strcpy(path, "/home/haijiao/share/tmp/web_server");

	memset(sin, 0, sizeof(*sin));
	sin->sin_family = AF_INET;
	sin->sin_port = htons(*port);
	inet_pton(AF_INET, "192.168.22.135", &sin->sin_addr.s_addr);

	*fd = socket(AF_INET, SOCK_STREAM, 0);
	if(*fd == -1)
	{
		DEBUG_PRINT("socket() error\n");
		return -1;
	}
	err = bind(*fd, (struct sockaddr*)sin, sizeof(struct sockaddr));
	if(err == -1)
	{
		DEBUG_PRINT("bind() error\n");
		return -1;
	}
	err = listen(*fd, 20);
	if(err == -1)
	{
		DEBUG_PRINT("listen() error\n");
		return -1;
	}
	return 0;
}

int get_path(int fd, char *path)
{
	char buf[MAX_LEN];
	int nbytes;
	nbytes = recv(fd, buf, MAX_LEN, 0);
	if(nbytes == -1)
	{
		printf("recv() error\n");
		return -1;
	}
	else if(nbytes == 0)
	{
		printf("The connection has been closed\n");
		return -1;
	}
	
	if(strstr(buf, "GET") != buf)
	{
		printf("wrong request\n");
		return -1;
	}
	if(buf[4] == '/' && buf[5] == ' ')
		strcat(path, "/index.html");
	else
	{
		strtok(&buf[4], " ");
		strcat(path, &buf[4]);
	}

	return 0;
}

int error_page(int fd)
{
	char buf[MAX_LEN];
	sprintf(buf, "HTTP/1.1 404 Not Exist\r\n");
	sprintf(buf, "%sContent-type: text/html\r\n\r\n", buf);
	sprintf(buf, "%s<html><body> the file does not exist </body></html>", buf);
	send(fd, buf, strlen(buf) + 1, 0);
	return 0;
}

int write_page(int fd, char *path, int file_fd)
{
	int n;
	char buf[MAX_LEN];
	sprintf(buf, "HTTP/1.0 200 OK\r\n");
	sprintf(buf, "%sContent-type: ", buf);
	
	n = strlen(path);
	if(strcasecmp(&path[n - 3], "jpg") == 0 || strcasecmp(&path[n - 4], "jpeg") == 0)
		sprintf(buf, "%simage/jpeg", buf);
	else if(strcasecmp(&path[n - 3], "gif") == 0 )
		sprintf(buf, "%simage/gif", buf);
	else if(strcasecmp(&path[n - 3], "png") == 0 )
		sprintf(buf, "%simage/png", buf);
	else sprintf(buf, "%stext/html", buf);
	sprintf(buf, "%s\r\n\r\n", buf);

	printf("%s\n",buf);

	send(fd, buf, strlen(buf) + 1, 0);

	while((n = read(file_fd, buf, MAX_LEN)) > 0)
		send(fd, buf, strlen(buf) + 1, 0);

	return 0;
}