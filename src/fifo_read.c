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
    ret = mkfifo(FIFO_FILE_PATH, S_IRWXU);
    if(ret > 0)
    {
        printf("mkfifo error\n");
        exit(-1);
    }
    fd = open(FIFO_FILE_PATH, o_rd)
}