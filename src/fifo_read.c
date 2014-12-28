#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include <sys/types.h>
#include <sys/stat.h>

const char* FIFO_FILE_PATH = "/tmp/ipc_test.fifo";

int main(int argc, char* argv[])
{
    int ret;
    int fd;
    char buf[100];
    int n;

    ret = mkfifo(FIFO_FILE_PATH, S_IRWXU);
    if(ret > 0)
    {
        printf("mkfifo error\n");
        exit(-1);
    }

    fd = open(FIFO_FILE_PATH, O_RDONLY | O_NONBLOCK);
    if(fd < 0)
    {
        printf("open fifo failed.\n");
        exit(-1);
    }

    while(1)
    {
        n = read(fd, buf, sizeof(buf));
        if(n < 0)
        {
            printf("no data yet.\n");
        }
        else if(n == 0)
        {
            printf("no opened by wriet.\n");
        }
        else
        {
            write(STDOUT_FILENO, buf, n);
        }
        sleep(2);
    }

    unlink(FIFO_FILE_PATH);
    return 0;
}