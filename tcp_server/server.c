#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    // 创建套接字
    // 参数 AF_INET 表示使用 IPv4 地址
    // SOCK_STREAM 表示使用面向连接的数据传输方式
    // IPPROTO_TCP 表示使用 TCP 协议
    int server_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // 创建ip:port
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));  //每个字节都用0填充
    server_addr.sin_family = AF_INET;  //使用IPv4地址
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
    server_addr.sin_port = htons(1234);  //端口

    // 将套接字和ip:port绑定
    bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));

    // 开始监听端口
    listen(server_sock, 20);
    
    while (1) {
        //接收客户端请求
        struct sockaddr_in client_addr;
        socklen_t client_addr_size = sizeof(client_addr);
        int client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &client_addr_size);
        printf("new connect\n");
        // 子进程处理链接
        pid_t pid = fork();
        if (pid < 0) {
            perror("error on fork");
        }
        if (pid == 0) {
            close(server_sock);
            //向客户端发送数据
            char str[] = "Hello World!";
            write(client_sock, str, sizeof(str));
            exit(0);
        }

        //关闭套接字
        close(client_sock);
    }
}