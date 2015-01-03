#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
int main(int argc, char* argv[])
{
	unsigned int writenum = 0;
	int dev_num = 0;
	int ret;
	int fd;
	char dev_name[]="/dev/globalvar_poll0";
	dev_num = atoi(argv[1]);
	writenum = atoi(argv[2]);
	dev_name[19] = 48 + dev_num;
	
	fd = open(dev_name,O_RDWR, S_IRUSR|S_IWUSR);
	if (fd < 0)
	{
		printf("open failed.\n");
		exit(-1);
	}

	ret = write(fd, &writenum, sizeof(writenum));
	if(ret < 0)
	{
		printf("write failed.\n");
		close(fd);
		exit(-1);
	}
	printf("%s\n0x%x writed.\n",dev_name,writenum);
	close(fd);
	return 0;
}
