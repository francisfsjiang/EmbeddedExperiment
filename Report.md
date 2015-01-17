#嵌入式基础实验
----
13120031 蒋方朔


&#160;

&#160;


##IPC实验

###Unix Socket

Socket，中文名套接字，在Unix系统中主要用于实现进程间通讯，
在计算机网络通讯方面被广泛使用。

在进程通信中，主要使用本地套接字来实现进程间双向通信。

要使用套接字，首先要使用如下函数创建一个套接字端点，返回文件描述符。

    socket_fd = socket(AF_UNIX, SOCK_STREAM, 0);

其中`AF_UNIX`表示使用Unix 本地套接字，`SOCK_STREAM`表示使用流的方式创建socket，最后表示省略使用的协议，而根据前两个参数自动选择。

对于服务端，使用bind函数来进行端口或sock文件的绑定

    ret = bind(socket_fd, (struct sockaddr*)&sock_addr, sizeof(sock_addr));

第一个参数


###Pipe

###System V

###Mmap

&#160;

&#160;

##驱动实验

###字符驱动实验

###Poll Device
