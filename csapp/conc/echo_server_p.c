/*
 * echo_server_p.c - A concurrent echo server based on process
*/
#include "csapp.h"

void echo(int connfd);

void sigchld_handler(int sig)
{
    while(waitpid(-1, 0, WNOHANG) > 0)
    ;
    return;
}

int main(int argc, char **argv)
{
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;

    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(0);
    }

    Signal(SIGCHLD, sigchld_handler);
    listenfd = Open_listenfd(argv[1]);
    while (1) {
        clientlen = sizeof(struct sockaddr_storage);
        connfd = Accept(listenfd, (SA *) &clientaddr, &clientlen);
        // 调用fork函数创建子进程，子进程是父进程的copy。子进程从这里开始执行程序，而不是从头执行
        if (Fork() == 0) {
            Close(listenfd); // child close its listening socket
            echo(connfd); // child services client
            Close(connfd); // child closes connection with client
            exit(0); // child close
        }
        Close(connfd); // parent closes connected socket (important!)
    }
}