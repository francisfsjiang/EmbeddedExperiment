#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
int main(int argc, char* argv[])
{
	unsigned int writenum = 0;
	int ret;
	int fd = open("/dev/globalvar",O_RDWR, S_IRUSR|S_IWUSR);
	if (fd < 0)
	{
		printf("open failed.\n");
		exit(-1);
	}

	writenum = atoi(argv[1]);
	ret = write(fd, &writenum, sizeof(writenum));
	if(ret < 0)
	{
		printf("write failed.\n");
		close(fd);
		exit(-1);
	}
	printf("0x%x writed.\n",writenum);
	close(fd);
	return 0;
}
