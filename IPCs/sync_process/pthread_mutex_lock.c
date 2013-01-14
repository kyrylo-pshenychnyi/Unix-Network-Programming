/*
	File:limits.c
	Brief: Finds the limits of system V message queue
	Date: 14th Jan 2013
	Author: Prakash ranjan
*/


#define _MULTI_THREADED
#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#define checkResults(string, val) {             \
 if (val) {                                     \
   printf("Failed with %d at %s", val, string); \
   exit(1);                                     \
 }                                              \
}
 
#define                 NUMTHREADS   3
pthread_mutex_t         mutex = PTHREAD_MUTEX_INITIALIZER;
int                     sharedData=0;
int                     sharedData2=0;
 
void *theThread(void *parm)
{
	int   rc;
	rc = pthread_mutex_lock(&mutex);
	printf("Thread %u: Entered\n",(unsigned int ) pthread_self());
	checkResults("pthread_mutex_lock()\n", rc);

	/********** Critical Section *******************/
	printf("Thread %u: Start critical section, holding lock\n",(unsigned int ) pthread_self());

	/* Access to shared data goes here */
	sharedData++; 
	sharedData2--;
	printf("Thread %u: End critical section, release lock\n", (unsigned int )pthread_self());

	/********** Critical Section *******************/
	rc = pthread_mutex_unlock(&mutex);
	checkResults("pthread_mutex_unlock()\n", rc);
	return NULL;
}
 
int main(int argc, char **argv)
{
	pthread_t             thread[NUMTHREADS];
	int                   rc=0;
	int                   i;

	printf("Enter Testcase - %s\n", argv[0]);

	printf("Hold Mutex to prevent access to shared data\n");
	rc = pthread_mutex_lock(&mutex);
	checkResults("pthread_mutex_lock()\n", rc);

	printf("Create/start threads\n");
	for (i=0; i<NUMTHREADS; ++i) {
	  	rc = pthread_create(&thread[i], NULL, theThread, NULL);
	   	checkResults("pthread_create()\n", rc);
	}

	printf("Wait a bit until we are 'done' with the shared data\n");
	sleep(3);
	printf("Unlock shared data\n");
	rc = pthread_mutex_unlock(&mutex);
	checkResults("pthread_mutex_lock()\n",rc);

	printf("Wait for the threads to complete, and release their resources\n");
	for (i=0; i <NUMTHREADS; ++i) {
	 	rc = pthread_join(thread[i], NULL);
	   	checkResults("pthread_join()\n", rc);
	}

	printf("Clean up\n");
	rc = pthread_mutex_destroy(&mutex);
	printf("Main completed\n");
	return 0;
}
