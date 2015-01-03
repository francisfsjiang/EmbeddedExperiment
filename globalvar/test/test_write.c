#include<stdio.h>
#include<fcntl.h>
#include<string.h>
int main(int argv, char* argc[])
{
	if(argv<2){
		printf("mast write something.\n");
		return 0;
	}
	int fd = open("/dev/rwbuf",O_WRONLY);
	write(fd,argc[1],strlen(argc[1]));
	printf("writed %s\n",argc[1]);
	close(fd);
	return 0;
}
