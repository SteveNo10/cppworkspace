/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-10-20
* Descript: 
*
============================================================================*/

#include "sha256.h"
#include <stdio.h>
#include <string>
#include <string.h>
#include <unistd.h>

using namespace std;

// const int pwds_len = 11;
// const char pwds[pwds_len] = {'\0', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
const int pwds_len = 63;
const char pwds[63] = {'\0', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 
    'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

// #define LOOPHEAD(i) for(buf[i] = BEGIN; buf[i] <= END; ++buf[i]) {
#define LOOPHEAD(i) for(int idx_##i = 0; idx_##i <= pwds_len; ++idx_##i) { buf[i] = pwds[idx_##i];
// #define LOOPMID(i) for(buf[i] = (0 == buf[i+1] ? 0 : 1); buf[i] <= END; ++buf[i]) {
#define LOOPMID(i) for(int idx_##i = (0 == buf[i+1] ? 0 : 1); idx_##i <= pwds_len; ++idx_##i) { buf[i] = pwds[idx_##i];
#define LOOPTAIL(i) for(int idx_##i = 1; idx_##i <= pwds_len; ++idx_##i) { buf[i] = pwds[idx_##i];
#define ENDLOOP(i) }

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        printf("Usage: %s loginname encryptpwd\n", argv[0]);
        return 0;
    }

    string strLoginname = argv[1];
    string strIn;
    string strEncPwd = argv[2]; 
    string strKey = "GM_WLCARD_1336";

    bool bFound = false;
    char buf[7] = {0};
    LOOPHEAD(5);
    LOOPMID(4);
    LOOPMID(3);
    LOOPMID(2);
    LOOPMID(1);
    LOOPTAIL(0);

    // printf("%s\n", buf);
    // sleep(1);
    
    strIn = strLoginname + strKey;
    strIn.append(buf);
    // printf("%s\n", strIn.c_str());
    string strTestPwd = sha256(strIn);
    if(strTestPwd == strEncPwd)
    {
        bFound = true;
        printf("pwd:%s\n", buf);
        goto result;
    }

    ENDLOOP(0);
    ENDLOOP(1);
    ENDLOOP(2);
    ENDLOOP(3);
    ENDLOOP(4);
    ENDLOOP(5);


result:
    if(!bFound)
    {
        printf("not found\n");
    }

    return 0;
}
