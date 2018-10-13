/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-10-13
* Descript: 
*
============================================================================*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#ifndef __SEMDEMO_H__
#define __SEMDEMO_H__

//如果传key则优先使用key，否则使用pathname生成，pathname默认为当前目录"."
int sem_create(int nsems, key_t key = 0, const char* pathname = ".");
int sem_get(key_t key = 0, const char* pathname = ".");
int sem_destroy(int semid);
int sem_init(int semid, int semnum, int val);
int sem_p(int semid, int sem_num);
int sem_v(int semid, int sem_num);

#endif
