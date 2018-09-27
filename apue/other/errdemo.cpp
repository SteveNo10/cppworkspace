#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

using namespace std;

int main(int, char**)
{
    int ret = open("", 0);
    if(-1 == ret)
    {
        cout<<strerror(errno)<<endl;
        perror("open file err!");
        printf("%m\n");
        return -1;
    } 

    return 0;
}
