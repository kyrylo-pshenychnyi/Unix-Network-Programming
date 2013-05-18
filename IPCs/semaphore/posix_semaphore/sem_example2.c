/* Example to show that a semaphore blocked by one thread acn be opned by other thread.
So ownership is a problem in semaphore */

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<semaphore.h>


sem_t semid;
int count=0;
#define MAX 10
#define SEM_NAME "/test"

void *thread1(void *ptr){
	int ret;
	ret = sem_wait(&semid);
	printf("Took semaphore in thread 1\n");
	for(;;){
		sleep(5);
		break;
	}
}



void *thread2(void*ptr){
	int ret;
	ret = sem_post(&semid);
	if(ret == -1){
		printf("error on sem post function\n");
		return ;
	}

	ret = sem_wait(&semid);
	if(ret == -1){
		printf("error on sem wiat function\n");
		return ;
	}
	printf("Printing from thread 2 after taking semaphore from thread 1\n");
	
	ret =sem_post(&semid);
	if(ret == -1){
		printf("error on sem post function\n");
		return ;
	}
}


int main(void){
	pthread_t id1,id2;
	int ret;
	int *exit_code;
	
	if((ret = sem_init(&semid,0,1) ) == -1){
		perror("Error in initializing the semaphore\n");
		exit(-1);
	}
	ret = pthread_create(&id1, NULL, &thread1, NULL);
	sleep(2);
	ret = pthread_create(&id2, NULL, &thread2, NULL);
	
	
	pthread_join(id1, (void *)&exit_code);
	pthread_join(id2, (void *)&exit_code);
	
	if((ret = sem_destroy(&semid)) == -1){
		perror("Error in destroying the semaphore\n");
		exit(-1);
	}
	return 0;
}
