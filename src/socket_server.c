#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/un.h>


//#pargma pack(1)
const char* SOCKET_FILE_PATH = "/tmp/ipc_test.sock";

static char data_buffer[256] = {0, 1, 2, 3, 4, 5, 6, 7};


int main()
{
    int socket_fd;
    int coon;
    ssize_t recv_num;
    int ret = 0;
    int i;
    static struct sockaddr_un sock_addr;
    printf("socket client start.\n");



    socket_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    printf("connect fd: %d\n",socket_fd);

    if(socket_fd < 0){
        perror("socket create failed.\n");
        unlink(SOCKET_FILE_PATH);
        exit(-1);
    }
    else
    {
        sock_addr.sun_family = AF_UNIX;
        strcpy(sock_addr.sun_path, SOCKET_FILE_PATH);
        ret = bind(socket_fd, (struct sockaddr*)&sock_addr, sizeof(sock_addr));
        chmod(SOCKET_FILE_PATH, 0777);
        if(ret < 0)
        {
            close(socket_fd);
            printf("bind failed\n");
            unlink(SOCKET_FILE_PATH);
            exit(-1);
        }
        ret = listen(socket_fd, 0);
        if (ret < 0 )
        {
            close(socket_fd);
            printf("listen failed.\n");
            unlink(SOCKET_FILE_PATH);
            exit(-1);
        }
        while (1)
        {
            coon = accept(socket_fd, NULL, 0);
            if(coon < 0)
            {
                printf("accept socket failed.\n");
                unlink(SOCKET_FILE_PATH);
                exit(-1);
            }
            memset(data_buffer, 0, sizeof(data_buffer));
            recv_num  = read(coon, data_buffer, sizeof(data_buffer));
            printf("received---------------\n");
            for(i = 0;i < recv_num; ++i)
            {
                printf("%d ", data_buffer[i]);
                data_buffer[i] *= 2;
            }
            write(coon, data_buffer, (size_t)recv_num);
            printf("\n");
        }
    }
    return 0;
}