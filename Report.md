#嵌入式基础实验实验报告
----
13120031 蒋方朔


&#160;

&#160;


##IPC实验

###Unix Socket

Socket，中文名套接字，在Unix系统中主要用于实现进程间通讯，
在计算机网络通讯方面被广泛使用。

在进程通信中，主要使用本地套接字来实现进程间双向通信。

要使用套接字，首先要使用系统调用`socket`来创建一个套接字端点，返回文件描述符。

    socket_fd = socket(AF_UNIX, SOCK_STREAM, 0);

其中`AF_UNIX`表示使用Unix 本地套接字，`SOCK_STREAM`表示使用流的方式创建socket，最后表示省略使用的协议，而根据前两个参数自动选择。

对于服务端，首先使用bind函数来进行端口或sock文件的绑定

    ret = bind(socket_fd, (struct sockaddr*)&sock_addr, sizeof(sock_addr));

第一个参数表示要绑定的socket，第二个参数是一个结构体，包括了协议及其对应的文件地址。

    listen(socket_fd, 0);

当绑定成功后，就可以用`listen`来开始监听。

    coon = accept(socket_fd, NULL, 0);

之后调用`accept`，`accept`函数会阻塞进程，当有传入连接的时候，就会返回该连接对应的描述符，并从监听队列中将该连接移除。

    read(coon, data_buffer, sizeof(data_buffer));

    write(coon, data_buffer, (size_t)num);

`read`,`write`函数则用来对指定的连接进行数据接收与发送。

对于客户端，可以在socket创建成功后使用`connect`函数来进行连接，并可以对使用返回的文件描述符调用`read`,`wirte`来进行数据发送与接收。

    connect(socket_fd, (struct sockaddr*)&sock_addr, sizeof(sock_addr));


###Pipe

Pipe,管道，是在Unix中广泛使用的一种进程间通信方式。

使用系统调用`pipe`来创建一个管道，参数为一个长为2的文件描述符数组。

    ret = pipe(pipe_fd);

其中`pipe_fd[0]`是写端，`pipe_fd[1]`是读端。在fork之后，为了避免死锁，需要在写进程中关闭读端，在读进程中要关闭写端。

之后可以使用`read`,`write`系统调用来对pipe进行读写操作。

    read(pipe_fd[0], r_buf, sizeof(r_buf));

    write(pipe_fd[1], w_buf, strlen(w_buf)+1);

###System V

本实验主要是通过共享内存来实现进程间通信。

首先使用`ftok`来将新创建的文件转换为`key_t`值。

    key = ftok(SHM_FILE_PATH, 0);

然后使用`shmget`来共享内存的描述符

    shm_id = shmget(key, 4096, IPC_CREAT);

使用`shmat`来进行共享内存的映射

    p_map  = (struct people*)shmat(shm_id, NULL, 0);

然后可以使用`memcpy`来将进程空间的内存拷贝到共享内存中，最后使用`shmdt`来关闭共享内存映射

    ret = shmdt(p_map);

之后在读取时，可以采用相同的步骤来对文件进行读取。

###Mmap

mmap将一个文件或者其它对象映射进内存，来进行内存共享。

首先是通过`open`调用来打开将要进行映射的文件，之后使用`mmap`函数来进行映射

    p_map = mmap(0, sizeof(people), PROT_READ, MAP_SHARED, fd, 0);

然后通过`memcpy`来写入共享内存，最后调用`umap`来结束映射

    munmap(p_map, sizeof(people));

&#160;

&#160;

##驱动实验

###字符驱动实验



###Poll Device

&#160;

&#160;

##实验总结及感想

通过以上所述的几个实验
