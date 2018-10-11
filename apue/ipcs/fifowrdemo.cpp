/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-10-11
* Descript: 
*
============================================================================*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

void sig_handle(int signo)
{
    printf("receive signo:%d\n", signo);
}

int main(int, char**)
{
    struct sigaction act;
    act.sa_handler = sig_handle;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGPIPE, &act, NULL);

    // raise(SIGPIPE);

    const char filename[] = "./fifo.fifo";
    int fd = open(filename, O_WRONLY);
    if(-1 == fd)
    {
        perror("open err");
        return -1;
    }

    const char say[] = "hello world!";
    while(true)
    {
        write(fd, say, strlen(say));
        sleep(1);
    }

    close(fd);

    return 0;
}
