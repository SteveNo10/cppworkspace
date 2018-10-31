/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-10-31
* Descript: 
* 可以直接用sendto/recvfrom
* 但是先connect再send/recv能在内核中记录ip/port，提高效率
* udp connect与tcp connect有本质区别，tcp的connect会三次握手
============================================================================*/

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        printf("Usage:%s ip port\n", argv[0]);
        return 0;
    }

    string ip = argv[1];
    int port = atoi(argv[2]);

    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in addr_con;
    bzero(&addr_con, sizeof(addr_con));
    addr_con.sin_family = AF_INET;
    addr_con.sin_addr.s_addr = inet_addr(ip.c_str());
    addr_con.sin_port = htons((short)port);
    
    if(-1 == connect(sock, (struct sockaddr*)&addr_con, sizeof(addr_con)))
    {
        printf("connect to %s:%d failed, errmsg:%m\n", ip.c_str(), port);
        return -1;
    }

    printf("connect to server success! please input your msg: exit by q\n");

    string strSend;
    char buf[BUFSIZ] = {0};
    int len_recv = -1;
    while(true)
    {
        cin>>strSend;
        if("q" == strSend)
        {
            printf("quit!\n");
            break;
        }

        if(-1 == send(sock, strSend.c_str(), strSend.size(), 0))
        {
            printf("send msg %s err:%m\n", strSend.c_str());
            break;
        }

        bzero(buf, BUFSIZ);
        if(-1 == (len_recv = recv(sock, buf, BUFSIZ, 0)))
        {
            printf("recv msg err:%m\n");
            break;
        }

        printf("recv from server success:%s\n", buf);
    }

    close(sock);

    return 0;
}
