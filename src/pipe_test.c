#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/errno.h>

int main()
{
    pid_t pid;
    int pipe_fd[2];
    int ret;
    int n;
    char r_buf[100];
    char w_buf[100];

    ret = pipe(pipe_fd);
    if(ret < 0)
    {
        printf("pipe create failed");
    }

    pid = fork();
    if (pid < 0)
    {
        printf("fork failed.\n");
        exit(-1);
    }
    if (pid == 0)
    {
        ret = close(pipe_fd[1]);
        if (ret < 0)
        {
            printf("close pipe fd 1 failed.\n");
            exit(-1);
        }
        while (1)
        {
            n = read(pipe_fd[0], r_buf, sizeof(r_buf));
            printf("read %d:  %s\n", n, r_buf);
        }

        close(pipe_fd[0]);
    }
    else
    {
        ret = close(pipe_fd[0]);
        if (ret < 0)
        {
            printf("close pipe fd 0 failed.\n");
        }
        while (1)
        {
            scanf("%s",w_buf);
            ret = write(pipe_fd[1], w_buf, strlen(w_buf)+1);
            if (ret < 0)
            {
                printf("write failed.\n");
            }
        }

        close(pipe_fd[1]);
    }

    return 0;
}