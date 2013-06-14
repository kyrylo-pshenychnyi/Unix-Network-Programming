#if 0
pthread_exit is like exit. It allows your thread
to bail out early in the same way that a program 
can bail out early, and it can be called from 
any code in the thread, whereas to return you 
have to make your way back up to the thread entry 
point. The difference, of course, is that in a 
thread you will  most likely leak resources all over 
the place if you try to exit other than back out 
through the entry point.

#endif

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void other_function()
{
	int *a = malloc(sizeof(int));
	*a = 10;
    pthread_exit((void *)a);
}

void * entry_point(void *arg)
{
    printf("Hello world!\n");
    other_function();
    printf("Hello again?\n");
    return NULL;
}

int main(int argc, char **argv)
{
    pthread_t thr;
	int *ptr; 
    if(pthread_create(&thr, NULL, &entry_point, NULL))
    {
		perror("pthread_create error\n");
        printf("Could not create thread\n");
        return -1;
    }

    if(pthread_join(thr, (void *)(&ptr)))
    {
		perror("pthread_join error\n");
        printf("Could not join thread\n");
        return -1;
    } else {
		printf("The value of the *ptr %d\n", *ptr);
		free(ptr);
	}
    return 0;
}
