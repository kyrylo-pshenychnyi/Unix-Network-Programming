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
	while (1){
		ret = sem_wait(&semid);
		if(ret == -1){
			perror("sem_wait");
			return ;
		}
		count++;
		if(count >= MAX){
			ret =sem_post(&semid);
			if(ret == -1){
				printf("error on sem wiat function\n");
			}
			pthread_exit(&ret);
		}
		printf("Count from thread 1 %d\n",count);
		ret = sem_post(&semid);
		if(ret == -1){
			printf("error on sem post function\n");
			return 0;
		}
		sleep(1);
	}
}



void *thread2(void*ptr){
	int ret;
	while (1){
		ret = sem_wait(&semid);
		if(ret == -1){
			printf("error on sem wiat function\n");
			return ;
		}
		count++;
		if(count >= MAX){
			ret = sem_post(&semid);
			if(ret == -1){
				printf("error on sem post function\n");
			}
			pthread_exit(&ret);
		}
		printf("Count from thread 2 %d\n",count);
		ret =sem_post(&semid);
		if(ret == -1){
			printf("error on sem post function\n");
			return ;
		}
		sleep(1);
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
	ret = pthread_create(&id2, NULL, &thread2, NULL);
	
	
	pthread_join(id1, (void *)&exit_code);
	pthread_join(id2, (void *)&exit_code);
	
	if((ret = sem_destroy(&semid)) == -1){
		perror("Error in destroying the semaphore\n");
		exit(-1);
	}
	return 0;
}
