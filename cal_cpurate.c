#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

struct cpustat{
	unsigned int user;
	unsigned int nice;
	unsigned int system;
	unsigned int idle;
	unsigned int iowait;
	unsigned int irq;
	unsigned int softirq;
	unsigned int x;			//steal
	unsigned int y;			//guest
	unsigned int z;			//guest_nice
};

int dir_filenum(char *path)
{
	int sum = 0;
	DIR *d = NULL;
	struct dirent *file;
	int i = 0;
	if((d = opendir(path)) == NULL){
		printf("open dirent error: %s\n", path);
		return;
	}
	while((file = readdir(d)) != NULL){
		if((strcmp(file->d_name, ".") == 0) || (strcmp(file->d_name, "..") == 0))
			continue;
		else if(file->d_type == 8)		//file
			sum++;
		else if(file->d_type == 4)		//dir
			continue;
	}
	return sum;
}

void change_filename(char *file, int n)
{
	char str_n[6];
	int file_len = strlen(file);
	int n_len;
	int i = 0;
	do{
		str_n[i++] = (n % 10) + '0';
		n /= 10;
	}
	while(n);
	str_n[i] = '\0';
	n_len = strlen(str_n);
	file[file_len] = '/';
	for(i = 0; i < n_len; i++)
		file[file_len + 1 + i] = str_n[n_len - 1 - i];
}

void read_stat(char *file, struct cpustat *stat, int i)
{
	int fd;
	char buf[256];
	change_filename(file, i);
	fd = open(file, O_RDONLY);
	if(fd < 0){
		printf("read_stat open file error\n");
		return;
	}
	read(fd, buf, sizeof(buf));
	sscanf(buf, "cpu %u %u %u %u %u %u %u %u %u %u", 
		&stat->user, &stat->nice, &stat->system,
		&stat->idle, &stat->iowait, &stat->irq, 
		&stat->softirq, &stat->x, &stat->y, &stat->z);
	close(fd);
}

int main()
{
	char statname[10] = "abc";
	char str_out[128];
	int sum;
	int i;
	int file_len;
	int fd_out;
	struct cpustat stat;
	sum = dir_filenum(statname);
	file_len = strlen(statname);
	fd_out = open("crate", O_WRONLY | O_CREAT | O_TRUNC, 0755);
	if(fd_out < 0){
		printf("print out file error\n");
		return 0;
	}
	for(i = 0; i < sum; i++){
		read_stat(statname, &stat, i);
		sprintf(str_out, "%u\t%u\t%u\t%u\t%u\t%u\t%u\t%u\t%u\t%u\n",
			stat.user, stat.nice, stat.system,
			stat.idle, stat.iowait, stat.irq, stat.softirq, 
			stat.x, stat.y, stat.z);
		write(fd_out, str_out, strlen(str_out));
		statname[file_len] = '\0';
	}
	close(fd_out);

	return 0;
}