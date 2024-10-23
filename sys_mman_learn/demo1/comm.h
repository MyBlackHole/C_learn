//comm.h
#ifndef _COMM_H__
#define _COMM_H__

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define PATHNAME "/tmp/sys_mman_learn_ipc"
#define PROJ_ID 0x6666

int CreateShm(int size);
int DestroyShm(int shmid);
int GetShm(int size);
#endif
