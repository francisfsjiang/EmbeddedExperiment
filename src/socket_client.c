#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/un.h>


//#pargma pack(1)
const char* SOCKET_FILE_PATH = "/tmp/ipc_exp.sock";

static char data_buffer[256] = {1, 1, 2, 3, 5, 8, 13, 21};

struct test_s
{
    char a;
    int b;
    int c;
}test_s;

int main() {
    int socket_fd;
    int ret = 0;
    int i;
    static struct sockaddr_un sock_addr;
    printf("socket client start.\n");

    socket_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    printf("connect fd: %d\n",socket_fd);

    if(socket_fd < 0){
        perror("socket create failed.\n");
        exit(-1);
    }
    else
    {
        sock_addr.sun_family = AF_UNIX;
        strcpy(sock_addr.sun_path, SOCKET_FILE_PATH);
        ret = connect(socket_fd, (struct sockaddr*)&sock_addr, sizeof(sock_addr));
        if(ret < 0)
        {
            close(socket_fd);
            printf("connect failed\n");
            exit(-1);
        }
        else
        {
            write(socket_fd, data_buffer, 16);
            memset(data_buffer, 0, sizeof(data_buffer));
            read(socket_fd, data_buffer, sizeof(data_buffer));
            for(i = 0;i < 16;i++)
            {
                printf("%d ", data_buffer[i]);
            }
            printf("\n");
        }
    }

    return 0;
}
