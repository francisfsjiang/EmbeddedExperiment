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

	ret = read(fd, &readnum, sizeof(readnum));
	if(ret < 0)
	{
		printf("read failed.\n");
		close(fd);
		exit(-1);
	}
	printf("readnum is 0x%x\n", readnum);
	close(fd);
	return 0;
}
