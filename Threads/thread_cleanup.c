#define _MULTI_THREADED
#include <pthread.h>
#include <stdio.h>
//#include "check.h"

void cleanupHandler(void *arg)
{
    printf("In the cleanup handler\n");
}

void *threadfunc(void *parm)
{
    printf("Entered secondary thread\n");
    pthread_cleanup_push(cleanupHandler, NULL);
    while (1) {
        pthread_testcancel();
        sleep(1);
    }
    pthread_cleanup_pop(0);
    return NULL;
}

int main(int argc, char **argv)
{
    pthread_t             thread;
    int                   rc=0;

    /* Create a thread using default attributes */
    rc = pthread_create(&thread, NULL, &threadfunc, NULL);

    if( rc != -1 ){
        printf("Create thread using the NULL attributes\n");
    } else {
        printf("Error in thread creation\n");
    }
        
    sleep(2);

    printf("Cancel the thread\n");
//    rc = pthread_cancel(thread);

    sleep(3);
    printf("Main completed\n");
    return 0;
}

