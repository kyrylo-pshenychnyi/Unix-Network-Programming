/*
	File:pthread_cond_wait.c
	Brief: Finds the limits of system V message queue
	Date: 14th Jan 2013
	Author: Prakash ranjan
*/


#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

#define NTHREADS 6



/* Sending threads */

void * thread1 (void * dummy_ptr ){


}
void * thread2 (void * dummy_ptr ){


}
void * thread3 (void * dummy_ptr ){


}

/* Receiving threads */

void * thread4 (void * dummy_ptr ){


}

void * thread5 (void * dummy_ptr ){


}

void * thread6 (void * dummy_ptr ){


}



/* Array of function pointer which will contain the threads function  */
void (*(thread(void *ptr)))[6] = {thread1,
								  thread2,
								  thread3,
								  thread4,
								  thread5,
								  thread6}; 

/* Main function starts here */

int main( int argc , char * argv[]){

	pthread_t id[NTHREAD];


	for(i = 0; i < NTHREAD ; i++){
		ret = pthread_create(&id[i], NULL; func[i] ; NULL);
		if(ret == -1){
			perror("pthread_create");
			printf("Error  in creating thread %d\n", i);
			exit(1);
		} else {
			printf("Success in creating thread %d\n" i );
		}
	}
			
	return 0;
}
