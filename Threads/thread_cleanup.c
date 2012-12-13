/*
    This is a simple thread program with thread cleanup handler 
    example. 

*/



#define _MULTI_THREADED
#include <pthread.h>
#include <stdio.h>

void cleanupHandler1(void *arg)
{
    printf("In the cleanup handler1\n");
}

void cleanupHandler2(void *arg)
{
    printf("In the cleanup handler2\n");
}

void *threadfunc(void *parm)
{
    printf("Entered secondary thread\n");

    /* The clean up handlers . Just pushing it on the stack 
       The handler functioned at the last will be called at the first*/

    pthread_cleanup_push(cleanupHandler1, NULL);
    pthread_cleanup_push(cleanupHandler2, NULL);
    pthread_testcancel();

    /* One dummy loop used for just doing something in thread */

    int i = 5;
    while (i) {
        printf("prakash\n");
        sleep(1);
        i--;
    }


    /* When any cancel command is called it will execute these 
        function. If no cancel command is called, these functions 
        will not get called at get skipped by the program */

    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);
    return NULL;
}

int main(int argc, char **argv)
{
    pthread_t thread;
    int rc=0;

    /* Create a thread using default attributes */
    rc = pthread_create(&thread, NULL, &threadfunc, NULL);
    if( rc != -1 ){
        printf("Create thread using the NULL attributes\n");
    } else {
        printf("Error in thread creation\n");
    }

    sleep(2);
    printf("Cancel the thread\n");
    rc = pthread_cancel(thread);

    sleep(3);
    printf("Main completed\n");
    return 0;
}


