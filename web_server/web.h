#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

#define MAX_LEN 4096

#define DEBUG 1

#ifdef DEBUG
#define DEBUG_PRINT(str) printf(str)
#else
#define DEBUG_PRINT(str)
#endif

extern int init(struct sockaddr_in *sin, int *fd, unsigned short *port, char *path);
extern int error_page(int fd);
extern int get_path(int fd, char *path);
extern int write_page(int fd, char *path, int file_fd);