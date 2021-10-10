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

#define MAX_CONNECT_NUM 2
#define BUFFER_SIZE 1024
const char *filename="uds-tmp.sock";

/*
监听socket
*/
int main()
{
    int fd,new_fd,len,i;
    struct sockaddr_un un;
    // 创建fd
    // AF_UNIX是unix socket
    // SOCK_STREAM是流式数据包
    fd = socket(AF_UNIX,SOCK_STREAM,0);
    if(fd < 0){
        printf("Request socket failed!\n");
        return -1;
    }
    // 创建socket文件
    un.sun_family = AF_UNIX;
    unlink(filename);
    strcpy(un.sun_path,filename);
    // 给socket fd一个本地地址（即socket文件）
    if(bind(fd,(struct sockaddr *)&un,sizeof(un)) <0 ){
        printf("bind failed!\n");
        return -1;
    }
    // 开始监听socket fd
    if(listen(fd,MAX_CONNECT_NUM) < 0){
        printf("listen failed!\n");
        return -1;
    }
    while(1){
        struct sockaddr_un client_addr;
        char buffer[BUFFER_SIZE];
        bzero(buffer,BUFFER_SIZE);
        len = sizeof(client_addr);
        //new_fd = accept(fd,(struct sockaddr *)&client_addr,&len);
        // 等待接受socket fd上的新连接
        new_fd = accept(fd,NULL,NULL);
        if(new_fd < 0){
            printf("accept failed\n");
            return -1;
        }
        // 连接成功，创建子进程处理新连接
        pid_t pid = fork();
        if (pid < 0) {
            perror("error on fork");
        }
        // 子进程逻辑
        if (pid == 0) {
            close(fd);
            int ret = recv(new_fd,buffer,BUFFER_SIZE,0);
            if(ret < 0){
                printf("recv failed\n");
            }
            for(i=0; i<10; i++){
                printf(" %d",buffer[i]);
            }
        }
        // 关闭客户端socket fd
        close(new_fd);
    }
}