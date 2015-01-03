#include<stdio.h>
#include<fcntl.h>
#define req 0x909090
int main()
{
	char buf[200];
	int fd = open("/dev/rwbuf",O_RDONLY);
	ioctl(fd,req);
	printf("rwbuf cleaned\n");
	close(fd);
	return 0;
}
