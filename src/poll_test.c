#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <poll.h>
#include <unistd.h>

const int POLL_DEV_NUM = 4;
int main() {
    char dev_name[21] = "/dev/globalvar_poll0";
    unsigned readnum = 0;
    struct pollfd fds[POLL_DEV_NUM];
    int i, ret;
    for (i = 0; i < POLL_DEV_NUM; ++i) {
        dev_name[19] = (char) (48 + i);
        fds[i].fd = open(dev_name, O_RDONLY);
        fds[i].events = POLLIN;
    }

    while (1)
    {
        ret = poll(fds, POLL_DEV_NUM, 5000);
        if (ret < 0 )
        {
            printf("poll error.\n");
            exit(-1);
        }
        printf("found %d fd is ready to read.\n", ret);
        for (i=0;i<POLL_DEV_NUM;++i)
        {
            if (fds[i].revents & POLLIN)
            {
                ret = (int) read(fds[i].fd, &readnum, sizeof(readnum));
                if (ret < 0)
                {
                    printf("read error.\n");
                    exit(-1);
                }
                printf("dev %d ready.\nnum is %d\n",i, readnum);
            }
        }
        //sleep(5);
    }
    return 0;
}
