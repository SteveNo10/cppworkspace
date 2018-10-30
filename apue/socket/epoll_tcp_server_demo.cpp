/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-10-30
* Descript: 
*
============================================================================*/

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include "common_socket.h"

using namespace std;

const int MAX_CON = 1024;

int main(int, char**)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    //一般来说，一个端口释放后会等待两分钟之后才能再被使用，SO_REUSEADDR是让端口释放后立即就可以被再次使用
    int val = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (void*)&val, sizeof(val));

    set_nonblock(sock);

    struct sockaddr_in addr_bind;
    bzero(&addr_bind, sizeof(addr_bind));
    addr_bind.sin_family = AF_INET;
    addr_bind.sin_port = htons(port);
    addr_bind.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(sock, (struct sockaddr*)&addr_bind, sizeof(addr_bind));

    listen(sock, MAX_CON);

    int efd = epoll_create(MAX_CON);
    struct epoll_event ee;
    bzero(&ee, sizeof(ee));
    ee.events = EPOLLIN;
    ee.data.fd = sock;
    epoll_ctl(efd, EPOLL_CTL_ADD, sock, &ee);

    struct sockaddr_in addr_cli;
    socklen_t addrlen_cli = sizeof(struct sockaddr_in);
    char buf[BUFSIZ] = {0};
    struct epoll_event events[MAX_CON];
    
    while(true)
    {
        int e_num = epoll_wait(efd, events, MAX_CON, 3000);
        if(-1 == e_num)
        {
            perror("epoll_wait err!");
            return -1;
        }
        else if(0 == e_num)
        {
            printf("epoll_wait timeout!\n");
            continue;
        }
        else
        {
            for(int i = 0; i < e_num; ++i)
            {
                if(EPOLLIN == events[i].events)
                {
                    if(sock == events[i].data.fd)
                    {
                        int newfd = accept(sock, (sockaddr*)&addr_cli, &addrlen_cli);
                        set_nonblock(newfd);
                        bzero(&ee, sizeof(ee));
                        ee.events = EPOLLIN|EPOLLET;
                        ee.data.fd = newfd;
                        epoll_ctl(efd, EPOLL_CTL_ADD, newfd, &ee);
                    }
                    else
                    {
                        bzero(buf, BUFSIZ);
                        int rsize = read(events[i].data.fd, buf, BUFSIZ);
                        if(0 == rsize)
                        {
                            epoll_ctl(efd, EPOLL_CTL_DEL, events[i].data.fd, NULL);
                            printf("client %d close connection\n", events[i].data.fd);
                            close(events[i].data.fd);
                        }
                        else
                        {
                            printf("read from %d msg %s len:%d\n", events[i].data.fd, buf, rsize);
                            write(events[i].data.fd, buf, rsize);
                        }
                    }
                }
                else if(EPOLLHUP == events[i].events)
                {
                    epoll_ctl(efd, EPOLL_CTL_DEL, events[i].data.fd, NULL);
                    printf("close fd:%d\n", events[i].data.fd);
                    close(events[i].data.fd);
                }
            }
        }
    }

}
