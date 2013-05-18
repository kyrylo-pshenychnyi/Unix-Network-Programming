#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define MAX 10
pthread_mutex_t mutex_count=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_mutex= PTHREAD_COND_INITIALIZER;

int count = 0;


void * thread1(void *ptr){
	while(1){
		pthread_mutex_lock(&mutex_count);
		if((count%2) != 0){
			pthread_cond_wait(&cond_mutex,&mutex_count);
		}
		count++;
		printf("%d\n", count);
		pthread_cond_signal(&cond_mutex);
		if(count >= MAX){
			pthread_mutex_unlock(&mutex_count);
			return;
		}
		pthread_mutex_unlock(&mutex_count);
	}
	return ;
}


void *thread2(void* ptr){
	while(1){
		pthread_mutex_lock(&mutex_count);
		if(count%1 != 0){
			pthread_cond_wait(&cond_mutex,&mutex_count);
		}
		count++;
		printf("%d\n", count);
		pthread_cond_signal(&cond_mutex);
		if(count >= MAX){
			pthread_mutex_unlock(&mutex_count);
			return ;
		}
		pthread_mutex_unlock(&mutex_count);
	}
return ;
}


int main(void){
	pthread_t pid1, pid2;
	void *ptr;
	int ret;
	ret = pthread_create(&pid1,NULL,&thread1,NULL);
	ret = pthread_create(&pid2,NULL,&thread2,NULL);

	pthread_join(pid1,&ptr);
	return 0;
}


