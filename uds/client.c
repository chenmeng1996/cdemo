#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/un.h>
#include<errno.h>
#include<stddef.h>
#include<unistd.h>
#define BUFFER_SIZE 1024
const char *filename="uds-tmp.sock";

int main()
{
    // 要连接的socket
    struct sockaddr_un un;
    int sock_fd;
    char buffer[BUFFER_SIZE] = {1,2,3};
    un.sun_family = AF_UNIX;
    strcpy(un.sun_path,filename); // socket文件
    // 创建fd
    sock_fd = socket(AF_UNIX,SOCK_STREAM,0);
    if(sock_fd < 0){
        printf("Request socket failed\n");
        return -1;
    }
    // 在socket fd上打开一个连接
    if(connect(sock_fd,(struct sockaddr *)&un,sizeof(un)) < 0){
        printf("connect socket failed\n");
        return -1;
    }
    // 发送数据
    send(sock_fd,buffer,BUFFER_SIZE,0);
    // 关闭fd
    close(sock_fd);
    return 0;
}