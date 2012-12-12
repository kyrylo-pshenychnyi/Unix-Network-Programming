#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NTHREADS 4
#define N 1000
#define MEGEXTRA 1000000
 
pthread_attr_t attr; // Setting the threads attributes
 
void *dowork(void *threadid)
{
    size_t mystacksize;

    /* Getting Stack size */
    pthread_attr_getstacksize (&attr, &mystacksize);

    printf("Thread %ld: stack size = %li bytes \n", *(long*)&threadid, mystacksize);

    pthread_exit(NULL);
}
 
int main(int argc, char *argv[])
{
    pthread_t threads[NTHREADS];
    size_t stacksize;
    int rc;
    long t;
    void *dummy_ptr;
    int j;

    /*Setting initial attributes of thread */
    pthread_attr_init(&attr);

    /*Getting default stack size */
    pthread_attr_getstacksize (&attr, &stacksize);

    printf("Default stack size = %li\n", stacksize);

    /* Setting desired Stact size (16777215) */
    stacksize = 0xFFFFFF; 

    printf("Amount of stack needed per thread = %li\n",stacksize);

    pthread_attr_setstacksize (&attr, stacksize);

    printf("Creating threads with stack size = %li bytes\n",stacksize);
    for(t=0; t<NTHREADS; t++){
        rc = pthread_create(&threads[t], &attr, dowork, (void *)t);
        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }
    
    for (j =0; j< NTHREADS ; j++){
        pthread_join(threads[j],&dummy_ptr);
    }

    printf("Created %ld threads.\n", t);
    
}
