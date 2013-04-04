#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#define KEY 0x100

typedef union semun
{
    int val;
    struct semid_ds *st;
    ushort * array;
}semun_t;

int main(void)
{
    int semid,count;
    struct sembuf op;

    semid = semget((key_t)KEY,10,0666|IPC_CREAT);
    if(semid==-1)
    {
        perror("error in creating semaphore, Reason:");
        exit(-1);
    }

    count = semctl(semid,0,GETVAL);
    if(count>2)
    {
        printf("Cannot execute Process anymore\n");
        printf("Count value is %d\n",count);
        exit(1);
    } else {
        printf("Count value is %d\n",count);
    }

    //get the semaphore and proceed ahead
    op.sem_num = 0; //signifies 0th semaphore
    op.sem_op = 1; //reduce the semaphore count to lock
    op.sem_flg = 0; //wait till we get lock on semaphore
    if( semop(semid,&op,1)==-1)
    {
        perror("semop failed : Reason");
        if(errno==EAGAIN)
        printf("Max allowed process exceeded\n");
    }

    //start the actual work here
    sleep(10);
    return 1;
}
