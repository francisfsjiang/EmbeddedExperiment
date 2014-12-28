#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>


const char* SHM_FILE_PATH = "/tmp/ipc_test.shm";

struct people
{
    char name[4];
    int age;
};

int main()
{
    int shm_id;
    key_t key;
    struct people* p_map;
    char temp[4];
    int i;
    int ret;

    key = ftok(SHM_FILE_PATH, 0);
    if (key < 0)
    {
        printf("ftok error.\n");
        exit(-1);
    }

    shm_id = shmget(key, 4096, IPC_CREAT);
    if (shm_id < 0)
    {
        printf("shmget error.\n");
        exit(-1);
    }

    p_map  = (struct people*)shmat(shm_id, NULL, 0);
    strcpy(temp, "a");

    for (i = 0; i < 10; ++i)
    {
        temp[0] += 1;
        //memcpy((*(p_map+i)).name, &temp, 2);
        strcpy((*(p_map+i)).name, temp);
        (*(p_map+i)).age = i + 20;
    }

    ret = shmdt(p_map);
    if (ret < 0)
    {
        printf("shmdt error.\n");
        exit(-1);
    }
    return 0;
}