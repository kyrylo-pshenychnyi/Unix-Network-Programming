#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <semaphore.h>


int main()
{
	/* Declare fork variables */
	pid_t childpid;
	
	/* Declare shared memory variables */
	key_t key;
	int shmid;
	int *data;
	int prev = 345;
	
	/* Declare semaphore variables */
	sem_t sem;
	int pshared = 1;
	unsigned int value = 1;
	
	/* Initialize Shared Memory */
	key = ftok("thread1.c",'R');
	shmid = shmget(key, 1024, 0644 | IPC_CREAT);
	  
	/* Attach to Shared Memory */
	data = shmat(shmid, (void *)0, 0);
	if(data == (int *)(-1))
		perror("shmat");
	
	/* Write initial value to shared memory */
	*data = prev;
	
	/* Initialize Semaphore */
	if((sem_init(&sem, pshared, value)) == 1)
	{
		perror("Error initializing semaphore");
		exit(1);
	}
	
	if((childpid = fork()) < 0) // error occured
	{
		perror("Fork Failed");
		exit(1);
	}
	else if(childpid == 0) // child process
	{
		/* Write to Shared Memory */
		while(1)
		{
			sem_wait(&sem);
			*data = *data + 1;
			*data = *data - 1;
			if(*data != prev)
			{
				printf("%d\n",*data);
				sleep(1);
				prev = *data;
			}
			sem_post(&sem);
		}
	}
	else // parent process
	{
		/* Write to Shared Memory */
		while(1)
		{
			sem_wait(&sem);
			*data = *data + 1;
			*data = *data - 1;
			sem_post(&sem);
		}
	}
	
	/* Detach from Shared Memory */
	shmdt(data);
	
	return 0;
}
