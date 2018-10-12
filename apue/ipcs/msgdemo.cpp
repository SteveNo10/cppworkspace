/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-10-12
* Descript: 
* 早期主要是为了提供高于一般速度的IPC。现在已经没有优势了
* 废弃掉，用fifo代替
============================================================================*/


#include <iostream>
#include <string>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>

using namespace std;

const key_t MSG_KEY = 1;

int SendMsg(int msgid, int type, const string& str)
{
    struct msgbuf msg;
    msg.mtype = type;
    strncpy(msg.mtext, str.c_str(), str.length() + 1);
    printf("msg.mtext:%s\n", msg.mtext);
    int sendlen = str.length() + 1;
    return msgsnd(msgid, &msg, sendlen, 0);
}

int RecvMsg(int msgid, int type, string& str)
{
    struct msgbuf msg;
    memset(&msg, 0, sizeof(struct msgbuf));
    int ret = msgrcv(msgid, &msg, 1024, type, 0);
    cout<<"recv :"<<ret<<endl;
    str = msg.mtext;

    return ret;
}

int main(int , char **)
{
    int msgid = msgget(MSG_KEY, IPC_CREAT|0666);
    if(-1 == msgid)
    {
        cout<<"msgget err!"<<endl;
        return -1;
    }

    string str = "123456789";
    if(-1 == SendMsg(msgid, 1, str))
    {
        cout<<"SendMsg 123 err!"<<endl;
        return -1;
    }

    str = "abcdefghijk";
    if(-1 == SendMsg(msgid, 2, str))
    {
        cout<<"SendMsg abc err!"<<endl;
        return -1;
    }
    
    str = "45678919";
    if(-1 == SendMsg(msgid, 1, str))
    {
        cout<<"SendMsg 456 err!"<<endl;
        return -1;
    }

    str = "hijklmnopq";
    if(-1 == SendMsg(msgid, 2, str))
    {
        cout<<"SendMsg efg err!"<<endl;
        return -1;
    }

    cout<<"send success!"<<endl;

    struct msqid_ds msginfo;
    if(-1 == msgctl(msgid, IPC_STAT, &msginfo))
    {
        cout<<"msgctl err!"<<endl;
        return -1;
    }

    cout<<"uid:"<<msginfo.msg_perm.uid<<"   gid:"<<msginfo.msg_perm.gid<<"   last change time:"<<msginfo.msg_ctime<<"   msg num:"<<msginfo.msg_qnum<<endl;

    if(-1 == RecvMsg(msgid, 0, str))
    {
        cout<<"RecvMsg err!"<<endl;
        return -1;
    }

    cout<<"recv first msg:"<<str<<endl;

    if(-1 == RecvMsg(msgid, 2, str))
    {
        cout<<"RecvMsg err!"<<endl;
        return -1;
    }

    cout<<"recv char:"<<str<<endl;

    if(-1 == RecvMsg(msgid, 2, str))
    {
        cout<<"RecvMsg err!"<<endl;
    }

    cout<<"recv char:"<<str<<endl;

    if(-1 == RecvMsg(msgid, 0, str))
    {
        cout<<"RecvMsg err!"<<endl;
        return -1;
    }

    cout<<"recv char:"<<str<<endl;

    if(-1 == msgctl(msgid, IPC_RMID, NULL))
    {
        cout<<"rm err!"<<endl;
        return -1;
    }

    cout<<"remove success!"<<endl;

    return 0;
}
