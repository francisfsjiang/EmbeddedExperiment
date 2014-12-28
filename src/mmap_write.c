#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>


const char* MMAP_FILE_PAHT = "/tmp/ipc_exp.mmap";

typedef struct
{
    char name[40];
    int id;
}people;

int main()
{
    int fd;
    int offset;
    people p;
    void* p_map;

    fd = open(MMAP_FILE_PAHT, O_CREAT| O_RDWR| O_TRUNC, 00777);
    if (fd < 0)
    {
        printf("create mmap file failed.\n");
        exit(-1);
    }

    p_map = mmap(0, sizeof(people), PROT_WRITE| PROT_READ, MAP_SHARED, fd, 0);
    if (p_map < 0)
    {
        printf("mmap failed.\n");
        exit(-1);
    }

    write(fd, "", sizeof(people)); //WTF

    strcpy(p.name, "haha");
    p.id = 20;

    offset = sizeof(p.name);

    memcpy(p_map, p.name, sizeof(p.name));
    memcpy(p_map+offset, &(p.id), sizeof(p.id));


//    people d;
//    memcpy(d.name, p_map, sizeof(d.name));
//    memcpy(&(d.id), p_map+offset, sizeof(d.id));
//    printf("%s\n",p.name);
//    printf("%d\n",p.id);

    munmap(p_map, sizeof(people));
    close(fd);

    return 0;
}