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
    int sock = socket(AF_INET, SOCK_DGRAM, 0);

    int val = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (void*)&val, sizeof(val));

    struct sockaddr_in addr_bind;
    bzero(&addr_bind, sizeof(addr_bind));
    addr_bind.sin_family = AF_INET;
    addr_bind.sin_port = htons(port);
    addr_bind.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(sock, (struct sockaddr*)&addr_bind, sizeof(addr_bind));

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
                        ssize_t len_recv = recvfrom(sock, buf, BUFSIZ, 0, (struct sockaddr*)&addr_cli, &addrlen_cli);
                        if(-1 == len_recv)
                        {
                            perror("recvfrom err!");
                            break;
                        }
                        else if(0 == len_recv)
                        {
                            printf("client close\n");
                            continue;
                        }

                        printf("recv from client:%s\n", buf);

                        ssize_t len_send = sendto(sock, buf, len_recv, 0, (struct sockaddr*)&addr_cli, addrlen_cli);
                        if(-1 == len_send)
                        {
                            perror("sento err!");
                            break;
                        }
                    }
                    else
                    {
                        perror("err fd");
                        break;
                    }
                }
                else
                {
                    perror("err events");
                    break;
                }
            }
        }
    }

    close(efd);
    close(sock);

    return 0;
}
