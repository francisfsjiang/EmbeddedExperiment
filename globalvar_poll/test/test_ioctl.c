#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
int main()
{
	unsigned int readnum = 0;
	int ret;
	int fd = open("/dev/globalvar",O_RDWR, S_IRUSR|S_IWUSR);
	if (fd < 0)
	{
		printf("open failed.\n");
		exit(-1);
	}
	ioctl(fd, 0x11, NULL);
	close(fd);
	return 0;
}
