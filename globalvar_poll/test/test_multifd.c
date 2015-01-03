#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
int main()
{
	unsigned int readnum = 0;
	unsigned int writenum = 3;
	int ret;
	int fd1 = open("/dev/globalvar",O_RDWR, S_IRUSR|S_IWUSR);
	if (fd1 < 0)
	{
		printf("open1 failed.\n");
		exit(-1);
	}

	int fd2 = open("/dev/globalvar",O_RDWR, S_IRUSR|S_IWUSR);
	if (fd2 < 0)
	{
		printf("open2 failed.\n");
		exit(-1);
	}
	printf("fd1:%d\nfd2:%d\n",fd1,fd2);

	ret = read(fd1, &readnum, sizeof(readnum));
	if(ret < 0)
	{
		printf("read fd1 failed.\n");
		exit(-1);
	}
	printf("fd1 readnum is 0x%x\n", readnum);
	ret = read(fd2, &readnum, sizeof(readnum));
	if(ret < 0)
	{
		printf("read fd2 failed.\n");
		exit(-1);
	}
	printf("fd2 readnum is 0x%x\n", readnum);

	ret = write(fd1, &writenum, sizeof(writenum));
	if(ret < 0)
	{
		printf("write fd1 failed.\n");
		exit(-1);
	}
	printf("fd1 0x%x writed.\n",writenum);

	ret = read(fd1, &readnum, sizeof(readnum));
	if(ret < 0)
	{
		printf("read fd1 failed.\n");
		exit(-1);
	}
	printf("fd1 readnum is 0x%x\n", readnum);
	ret = read(fd2, &readnum, sizeof(readnum));
	if(ret < 0)
	{
		printf("read fd2 failed.\n");
		exit(-1);
	}
	printf("fd2 readnum is 0x%x\n", readnum);
	close(fd1);
	close(fd2);
	return 0;
}
