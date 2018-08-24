#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

using namespace std;

int main(int, char**)
{
    int ret = open("", 0);
    if(-1 == ret)
    {
        cout<<strerror(errno);
        perror("open file err!");
        return -1;
    } 

    return 0;
}
