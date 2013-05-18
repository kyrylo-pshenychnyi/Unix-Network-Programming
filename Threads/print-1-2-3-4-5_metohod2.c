#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define MAX 10
pthread_mutex_t mutex_count=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_mutex1= PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_mutex2= PTHREAD_COND_INITIALIZER;

int count = 0;


void * thread1(void *ptr){
	printf("This is thread 1\n");
	while(1){
		pthread_mutex_lock(&mutex_count);
		pthread_cond_wait(&cond_mutex1,&mutex_count);
		count++;
		printf("%d\n", count);
		if(count >= MAX){
			pthread_cond_signal(&cond_mutex2);
			pthread_mutex_unlock(&mutex_count);
			return;
		}
		pthread_cond_signal(&cond_mutex2);
		pthread_mutex_unlock(&mutex_count);
	}
	return ;
}


void *thread2(void* ptr){
	sleep(1);
	printf("This is thread 2\n");
	pthread_cond_signal(&cond_mutex1);
	while(1){
		pthread_mutex_lock(&mutex_count);
		pthread_cond_wait(&cond_mutex2,&mutex_count);
		count++;
		printf("%d\n", count);
		if(count >= MAX){
			pthread_cond_signal(&cond_mutex1);
			pthread_mutex_unlock(&mutex_count);
			return ;
		}
		pthread_cond_signal(&cond_mutex1);
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


