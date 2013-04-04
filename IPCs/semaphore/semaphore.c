/* semaphore.c --- simple illustration of dijkstra's semaphore analogy
 *
 *   We fork() a  child process so that we have two processes running:
 *   Each process communicates via a semaphore.
 *   The respective process can only do its work (not much here)
 *   When it notices that the semaphore track is free when it returns to 0
 *   Each process must modify the semaphore accordingly.
     
     The key elements of this program are as follows:

     After a semaphore is created with as simple key 1234, two prcesses are forked.
     Each process (parent and child) essentially performs the same operations:
        1. Each process accesses the same semaphore track ( sops[].sem_num = 0).
        2. Each process waits for the track to become free and then attempts to take control of track

        This is achieved by setting appropriate sops[].sem_op values in the array.
        
        1. Once the process has control it sleeps for 5 seconds (in reality some processing would 
           take place in place of this simple illustration)
        2. The process then gives up control of the track sops[1].sem_op = -1
        3. an additional sleep operation is then performed to ensure that the other process has 
           time to access the semaphore before a subsequent (same process) semaphore read.

        Note: There is no synchronisation here in this simple example an we have no control 
              over how the OS will schedule the processes. 


 */
 
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
 
union semun {
    int val;
    struct semid_ds *buf;
    ushort *array;
};

int main(void){
    int i,j; 
    int pid;
    int semid; /* semid of semaphore set */
    key_t key = 1234; /* key to pass to semget() */
    int semflg = IPC_CREAT | 0666; /* semflg to pass to semget() */
    int nsems = 1; /* nsems to pass to semget() */
    int nsops; /* number of operations to do */
    struct sembuf *sops = (struct sembuf *) malloc(2*sizeof(struct sembuf)); 
    int ret_val;
    /* ptr to operations to perform */

    /* set up semaphore */
  
    printf("\nsemget: Setting up seamaphore: semget(%d, %d, %d)\n",key, nsems, semflg);

    semid = semget(key, nsems, semflg);
    if (semid == -1) {
        perror("semget: semget failed");
        exit(1);
    } else {
        printf("semget: semget succeeded: semid =%d\n", semid);
    }

    /* get child process */
    
    pid = fork(); 
  
    if (pid < 0) {
        perror("fork");
        exit(1);
    } else if (pid == 0){ /* child */
        i = 0;
        while (i < 2) {/* allow for 2 semaphore sets */
               
           nsops = 2; // Number of semaphore operation
           
           /* wait for semaphore to reach zero */
           
           sops[0].sem_num = 0; /* We only use one track */
           sops[0].sem_op = 0; /* wait for semaphore flag to become zero */
           sops[0].sem_flg = SEM_UNDO; /* take off semaphore asynchronous  */
           
           
           sops[1].sem_num = 0;
           sops[1].sem_op = 1; /* increment semaphore -- take control of track */
           sops[1].sem_flg = SEM_UNDO | IPC_NOWAIT; /* take off semaphore */
  
           /* Make the semop() call and report the results. */
            ret_val = semop(semid, sops, nsops); 
           if (ret_val == -1) {
               perror("semop: semop failed");
           } else {
               printf("\n\n\tChild Process Taking Control of Track: %d/2 times\n", i+1);
               sleep(5); /* DO Nothing for 5 seconds */

               nsops = 1;
           
               /* wait for semaphore to reach zero */
               sops[0].sem_num = 0;
               sops[0].sem_op = -1; /* Give UP COntrol of track */
               sops[0].sem_flg = SEM_UNDO | IPC_NOWAIT; /* take off semaphore, asynchronous  */
           
               ret_val = semop(semid, sops, nsops);    
               if (ret_val == -1) {
                    perror("\tsemop: semop failed");
               } else {
                    printf("\tChild Process Giving up Control of Track: %d/2 times\n", i+1);
               }
               sleep(5); /* halt process to allow parent to catch semaphor change first */
           }
           ++i;
        }   
    } else {/* parent */
       /* pid hold id of child */
        
        i = 0;
       
        sleep(1); 
        while (i  < 2) { /* allow for 2 semaphore sets */
       
            nsops = 2; //semaphore operation
       
            /* wait for semaphore to reach zero */
            sops[0].sem_num = 0;
            sops[0].sem_op = 0; /* wait for semaphore flag to become zero */
            sops[0].sem_flg = SEM_UNDO; /* take off semaphore asynchronous  */
       
       
            sops[1].sem_num = 0;
            sops[1].sem_op = 1; /* increment semaphore -- take control of track */
            sops[1].sem_flg = SEM_UNDO | IPC_NOWAIT; /* take off semaphore */
       
            /* Make the semop() call and report the results. */
            ret_val = semop(semid, sops, nsops);
            if ( ret_val == -1) {
                perror("semop: semop failed");
            } else {
                printf("Parent Process Taking Control of Track: %d/2 times\n", i+1);
                sleep(5); /* Do nothing for 5 seconds */

                nsops = 1;
       
                /* wait for semaphore to reach zero */
                sops[0].sem_num = 0;
                sops[0].sem_op = -1; /* Give UP COntrol of track */
                sops[0].sem_flg = SEM_UNDO | IPC_NOWAIT; /* take off semaphore, asynchronous  */
       
                ret_val = semop(semid, sops, nsops);
                if (ret_val == -1) {
                    perror("semop: semop failed");
                } else {
                    printf("Parent Process Giving up Control of Track: %d/2 times\n", i+1);
                }
                sleep(5); /* halt process to allow child to catch semaphor change first */
            }
            ++i;
        
        }
       
    }
    return 0;
}
