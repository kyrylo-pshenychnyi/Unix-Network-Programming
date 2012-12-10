#include<stdio.h>
#include<pthread.h>
#include<string.h>
#include<stdlib.h>

#define PASS 0
#define FAIL -1


void * thread_func( char *dummy_ptr)
{
    printf("This is thread function\n");

    int i = 0;
    while ( i < 5){
        printf("%d\n",i);
        i++;
    }
    return 0;
}

int main (void)
{

    pthread_t thread1_id;

    int ret = PASS;
    char c;

    void *ptr;
    
    ret = pthread_create(&thread1_id, NULL,(void*)thread_func, &c);
    if( ret == FAIL ){
        printf("Error in creating the thread\n");
        exit(0);
    } else {
        printf("Successfully created the thread with id %d\n", thread1_id);
    }
    
    pthread_join(thread1_id, &ptr);

}
    

