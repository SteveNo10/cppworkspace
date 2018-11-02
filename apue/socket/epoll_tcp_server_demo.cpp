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
    if(-1 == sock)
    {
        perror("socket err!");
        return -1;
    }

    //一般来说，一个端口释放后会等待两分钟之后才能再被使用，SO_REUSEADDR是让端口释放后立即就可以被再次使用
    int val = 1;
    if(-1 == setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (void*)&val, sizeof(val)))
    {
        perror("setsockopt SO_REUSEADDR err!");
        return -1;
    }

    if(-1 == set_nonblock(sock))
    {
        perror("set nonblock err!");
        return -1;
    }

    set_nonblock(sock);

    struct sockaddr_in addr_bind;
    bzero(&addr_bind, sizeof(addr_bind));
    addr_bind.sin_family = AF_INET;
    addr_bind.sin_port = htons(port);
    addr_bind.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(sock, (struct sockaddr*)&addr_bind, sizeof(addr_bind));

    if(-1 == listen(sock, MAX_CON))
    {
        perror("listen err!");
        return -1;
    }

    int efd = epoll_create(MAX_CON);
    if(-1 == efd)
    {
        perror("epoll_create err!");
        return -1;
    }

    struct epoll_event ee;
    bzero(&ee, sizeof(ee));
    ee.events = EPOLLIN;
    ee.data.fd = sock;
    if(-1 == epoll_ctl(efd, EPOLL_CTL_ADD, sock, &ee))
    {
        perror("epoll_ctl err!");
        return -1;
    }

    struct sockaddr_in addr_cli;
    socklen_t addrlen_cli = sizeof(struct sockaddr_in);
    char buf[BUFSIZ] = {0};
    struct epoll_event events[MAX_CON];
    
    while(true)
    {
        int e_num = epoll_wait(efd, events, MAX_CON, 3000);
        if(-1 == e_num)
        {
            if(EINTR == errno)
            {
                continue;
            }
            else
            {
                perror("epoll_wait err!");
                return -1;
            }
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
                if(EPOLLIN & events[i].events)
                {
                    if(sock == events[i].data.fd)
                    {
                        int newfd = -1; 
                        int accept_num = 10;   //单次最多接受10个连接，防止连接过多阻塞别的消息
                        while(accept_num-- > 0)
                        {
                            newfd = accept(sock, (sockaddr*)&addr_cli, &addrlen_cli);
                            if(-1 == newfd)
                            {
                                if(EAGAIN == errno)
                                {
                                    break;
                                }
                                else if(EINTR == errno)
                                {
                                    continue;
                                }
                                else
                                {
                                    perror("accept err!");
                                    break;
                                }
                            }

                            if(-1 == set_nonblock(newfd))
                            {
                                perror("set nonblock err!");
                                close(newfd);
                                continue;
                            }

                            bzero(&ee, sizeof(ee));
                            ee.events = EPOLLIN|EPOLLET;
                            ee.data.fd = newfd;
                            if(-1 == epoll_ctl(efd, EPOLL_CTL_ADD, newfd, &ee))
                            {
                                perror("epoll_ctl err!");
                                close(newfd);
                                continue;
                            }
                        }
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
                        else if(-1 == rsize)
                        {
                            perror("read err!");
                            epoll_ctl(efd, EPOLL_CTL_DEL, events[i].data.fd, NULL);
                            close(events[i].data.fd);
                        }
                        else
                        {
                            printf("read from %d msg %s len:%d\n", events[i].data.fd, buf, rsize);
                            //TODO 非阻塞模式write可能失败，正式代码需要缓存起来重发
                            write(events[i].data.fd, buf, rsize);
                        }
                    }
                }
                else if(EPOLLHUP & events[i].events || EPOLLERR & events[i].events)
                {
                    epoll_ctl(efd, EPOLL_CTL_DEL, events[i].data.fd, NULL);
                    printf("close fd:%d\n", events[i].data.fd);
                    close(events[i].data.fd);
                }
                else
                {
                    epoll_ctl(efd, EPOLL_CTL_DEL, events[i].data.fd, NULL);
                    printf("%d err event:%u\n", events[i].data.fd, events[i].events);
                    close(events[i].data.fd);
                }
            }
        }
    }

    return 0;
}
