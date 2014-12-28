#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>

const char* FIFO_FILE_PATH = "/tmp/ipc_test.fifo";

int main(int argc, char* argv[])
{
    int ret;
    int fd;
    char buf[100];
    int n;

    fd = open(FIFO_FILE_PATH, O_WRONLY | O_NONBLOCK);
    if(fd < 0)
    {
        printf("open fifo failed.\n");
        exit(-1);
    }

    while(1)
    {
        fgets(buf, sizeof(buf), stdin);
        printf("%s\n",buf);
        n = strlen(buf);
        n = write(fd, buf, n);
        if(n < 0)
        {
            printf("write filed.\n");
        }
    }

    return 0;
}