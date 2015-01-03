#include<stdio.h>
#include<fcntl.h>
int main()
{
	char buf[20];
	int fd = open("/dev/rwbuf",O_RDONLY);
	read(fd,buf,20);
	printf("%s\n",buf);
	close(fd);
	return 0;
}
