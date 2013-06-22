/* Showing usage of 
    1. mq_open
    2. mq_getattr
    3. mq_send
    4. mq_receive
    5. mq_setattr
    6. mq_close
    7. mq_unlink

    To compile this code :
    gcc posix_message_queue.c -lrt
*/

#include <mqueue.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <unistd.h>        /* For mode constants */

#define NAME "/prakash"


char buf_send[100];     // sending buffer
char buf_recv[100];     // receivig buffer

int Mq_open(){
    int ret;
    mqd_t mqdes;
    struct mq_attr new_attr, attr;     // To store queue attributes
    
    new_attr.mq_maxmsg = 10;
    new_attr.mq_msgsize = 2046;
    new_attr.mq_flags = 0;

    /* Function used to open a posix message queue */    
    mqdes = mq_open (NAME, O_RDWR | O_CREAT, 0664, &new_attr);
    if(mqdes == -1){
        printf("Error in opening the 'Prakash' message queue\n");
        printf("Error number = %d\n",errno);
        return errno;
    } 
    return mqdes;
}



int main (int argc, char *argv[]) {
    struct mq_attr attr, old_attr, new_attr;     // To store queue attributes
    mqd_t mqdes;     // Message queue descriptors
    int ret;

    if( argc < 2){
        printf("Usage: ./a.out < string to be send through message queue >\n");
        exit(0);
    }

    strcpy(buf_send,argv[1]);

    mqdes = Mq_open();
    if(mqdes < 0){
        exit(-1);
    }

    /* Function used to get the attributes of the posix message queue */
    ret = mq_getattr(mqdes, &attr);
    if(mqdes == -1){
        printf("Error in getting attribute from 'Prakash' message queue\n");
        printf("Error number = %d\n",errno);
        exit(errno);;
    } else {
        printf("\n============================================================\n\n");
        printf("Success in getting attribute from 'Prakash' message queue\n");
        printf("Maxmsg = %ld\n",attr.mq_maxmsg);
        printf("Maxsize = %ld\n",attr.mq_msgsize);
        printf("flag = %ld\n",attr.mq_flags);
        printf("\n============================================================\n");
    }


    /* Function used to send the message on the message queue */
    ret = mq_send (mqdes, buf_send, sizeof(buf_send), 1);
    if(ret == -1){
        printf("Error in sending the buffer\n");
        printf("Error number = %d\n",errno);
        exit(errno);
    } else {
        printf(" Message send : [ %s ]\n",buf_send);
    } 


    /* Function used to receive the message from the message queue 
       The 3rd argument of the mesasage queue must be greater than mq_msgsize 
       value. If not we will get a error " Message too long" */
    ret = mq_receive(mqdes, buf_recv, attr.mq_msgsize + 1 , 0);
    if(ret == -1){
        perror("mq_receive");
        printf("Error in receiving the buffer\n");
        printf("Error number = %d\n",errno);
        exit(errno);
    } else {
        printf(" Message received : [ %s ]\n",buf_recv);
    } 

    /* Trying to change the value of the mq_attr structure using 
       mq_setattr() function call */ 

    new_attr.mq_maxmsg = 11;   // These feilds will get innored as they can't be changed.
    new_attr.mq_msgsize = 4096; // These feilds will get innored as they can't be changed.
    new_attr.mq_flags = O_NONBLOCK;   // The only flag which can be changed by mq_setattr fucntion

    ret = mq_setattr(mqdes, &new_attr,&old_attr);
    if(mqdes == -1){
        printf("Error in setting attribute to 'Prakash' message queue\n");
        printf("Error number = %d\n",errno);
        exit(errno);;
    } 

    /* Verifying the set value in the above step */
    ret = mq_getattr(mqdes, &attr);
    if(mqdes == -1){
        printf("Error in getting attribute from 'Prakash' message queue\n");
        printf("Error number = %d\n",errno);
        exit(errno);;
    } else {
        printf("\n============================================================\n\n");
        printf("Success in getting attribute from 'Prakash' message queue\n");
        printf("Maxmsg = %ld\n",attr.mq_maxmsg);
        printf("Maxsize = %ld\n",attr.mq_msgsize);
        printf("flag = %ld\n",attr.mq_flags);
        printf("mq_curmsgs %ld\n",attr.mq_curmsgs);
        printf("\n============================================================\n");
    }

    /* Closing the message queue discriptor
       Note:  Only closing the discriptor, not removing the message queue */

    ret = mq_close(mqdes);
    if(ret == -1){
        printf("Error in closing the  'Prakash' message queue\n");
        printf("Error number = %d\n",errno);
        exit(errno);
    }
    

    /* removing the message queue from the file system */
    ret = mq_unlink (NAME);
    if(ret == -1){
        printf("Error in removng the 'Prakash' message queue\n");
        printf("Error number = %d\n",errno);
        exit(errno);
    }  
    return 0;
}
