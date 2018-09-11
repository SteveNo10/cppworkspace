/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-09-11
* Descript: 
*
============================================================================*/

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <map>
#include <string>
#include <iostream>

using namespace std;

typedef void (*run)();

char buf[BUFSIZ] = {0};

void fun_read_write()
{
    while(true)
    {
        bzero(buf, BUFSIZ);
        ssize_t readlen = read(STDIN_FILENO, buf, BUFSIZ);
        write(STDOUT_FILENO, buf, readlen);
    }
}

void fun_fgetc_fputc()
{
    while(true)
    {
        int c = fgetc(stdin);
        fputc(c, stdout);
    }
}

void fun_getchar_putchar()
{
    while(true)
    {
        int c = getchar();
        putchar((char)c);
    }
}

void fun_fgets_fputs()
{
    while(true)
    {
        bzero(buf, BUFSIZ);
        fgets(buf, BUFSIZ, stdin);
        fputs(buf, stdout); 
    }
}

void fun_gets_puts()
{
    while(true)
    {
        bzero(buf, BUFSIZ);
        gets(buf);
        puts(buf);
    }
}

void fun_fscanf_fprintf()
{
    while(true)
    {
        bzero(buf, BUFSIZ);
        fscanf(stdin, "%s", buf);
        fprintf(stdout, "%s\n", buf);
    }
}

void fun_scanf_printf()
{
    while(true)
    {
        bzero(buf, BUFSIZ);
        scanf("%s", buf);
        printf("%s\n", buf);
    }
}

void fun_cin_cout()
{
    string str;
    while(true)
    {
        cin>>str;
        cout<<str<<endl;
    }
}

struct FunInfo
{
    string msg;
    run fun;
};

typedef map<int, FunInfo> MapFun;

void AddFun(MapFun& config, int idx, const string& msg, run f)
{
    config[idx].msg = msg;
    config[idx].fun = f;
}

void Init(MapFun& config)
{
    int i = 1;
    AddFun(config, i++, "read write", fun_read_write);
    AddFun(config, i++, "fgetc fputc", fun_fgetc_fputc);
    AddFun(config, i++, "getchar putchar", fun_getchar_putchar);
    AddFun(config, i++, "fgets fputs", fun_fgets_fputs);
    AddFun(config, i++, "gets puts", fun_gets_puts);
    AddFun(config, i++, "fscanf fprintf", fun_fscanf_fprintf);
    AddFun(config, i++, "scanf printf", fun_scanf_printf);
    AddFun(config, i++, "cin cout", fun_cin_cout);
}

void Usage(MapFun& config)
{
    cout<<"Usage: ./main mode"<<endl;
    for(auto itr = config.begin(); itr != config.end(); ++itr)
    {
        cout<<"   "<<itr->first<<":"<<itr->second.msg<<endl;
    }
}

int main(int argc, char** argv)
{
    MapFun config;
    Init(config);

    if(argc != 2)
    {
        Usage(config);
        return -1;
    }

    int mode = atoi(argv[1]);
    auto itr = config.find(mode);
    if(itr == config.end())
    {
        Usage(config);
        return -2;
    }

    cout<<"mode:"<<itr->first<<"   msg:"<<itr->second.msg<<endl;
    itr->second.fun();

    return 0;
}
