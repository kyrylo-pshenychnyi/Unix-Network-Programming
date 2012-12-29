/*
    File: shared_memory_write.c
    Brief: This fileis used for writing a character array on shamred memory
    Author: Prakash Ranjan
    Date: 29th Dec 2012
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024*2  

int main(int argc, char *argv[])
{
	key_t key;
    int shmid;
    char *data;
    int mode;

    if (argc > 2) {
        fprintf(stderr, "usage: shared_memory_write  [data_to_write]\n");
        exit(-1);
    }

    if ((key = ftok("shared_memory_write.c", 'R')) == -1) {
        perror("ftok");
        exit(-1);
    }

    if ((shmid = shmget(key, SHM_SIZE, 0644 | IPC_CREAT)) == -1) {
        perror("shmget");
        exit(1);
    }

    data = shmat(shmid, (void *)0, 0);
    if (data == (char *)(-1)) {
        perror("shmat");
        exit(1);
    }

    if (argc == 2) {
        printf("writing to segment: \"%s\"\n", argv[1]);
        strncpy(data, argv[1], SHM_SIZE); 
    } else {
        printf("segment contains: \"%s\"\n", data);
    }

    if (shmdt(data) == -1) {
        perror("shmdt");
        exit(1);
    }
    return 0;
}
