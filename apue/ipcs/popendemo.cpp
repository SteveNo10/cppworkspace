/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-10-10
* Descript: 
*
============================================================================*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int, char**)
{
    FILE* pfile = popen("cat > popen.txt", "w");
    char say[] = "Hello World!";
    fwrite(say, strlen(say), 1, pfile);
    pclose(pfile);

    pfile = popen("cat popen.txt", "r");
    char buf[BUFSIZ] = {0};
    fread(buf, BUFSIZ, 1, pfile);
    printf("%s\n", buf);
    pclose(pfile);

    return 0;
}
