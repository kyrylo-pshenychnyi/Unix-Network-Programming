/* Showing usage of 
    1. mq_open
    2. mq_close
    3. mq_unlink

*/



#include <mqueue.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <unistd.h>        /* For mode constants */

    
int main (void) {
    mqd_t mqdes ;     // Message queue descriptors
    
    int ret ;
    int i;
    for(i = 0;; i++){
        // Open a queue with the attribute structure
        mqdes = mq_open ("/Prakash", O_RDWR | O_CREAT, 0664,NULL);
        if(mqdes == -1){
            printf("Error in opening the 'Prakash' message queue\n");
            printf("Error number = %d\n",errno);
            exit(10);;
        } else {
            printf("Success in opening 'Prakash' message queue\n");
        }

        ret = mq_close(mqdes);
        if(ret == -1){
            printf("Error in closing the  'Prakash' message queue\n");
            printf("Error number = %d\n",errno);
            exit(10);;
        } else {
            printf("Success in closing 'Prakash' message queue\n");
        }
#if 1    
        ret = mq_unlink ("/Prakash");
        if(ret == -1){
            printf("Error in removng the 'Prakash' message queue\n");
            printf("Error number = %d\n",errno);
            exit(10);;
        } else {
            printf("Success in removing the 'Prakash' message queue\n");
        }
#endif
        printf("=================[%d]=================\n",i);
        usleep(50);
    }
    return 0;
}
