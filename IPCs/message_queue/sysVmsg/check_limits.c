/*
	File:limits.c
	Brief: Finds the limits of system V message queue
	Date: 11th Jan 2013
	Author: Prakash ranjan
*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>


#define MAX_DATA 64 * 1024 
#define MAX_NMESG 4096
#define MAX_NIDS  4096

#define SVMSG_MODE (MSG_R | MSG_W | MSG_R >> 3 | MSG_R >> 6)

int max_mesg ;
struct my_mesg{
	long type;
	char data[MAX_DATA];
}mesg;

int main(int argc , char**argv){
	int ret;
	int i;
	int j;
	int msqid;
	int qid[MAX_NIDS];

	msqid = msgget(IPC_PRIVATE,0775|IPC_CREAT);
	if(msqid == -1){
		printf("Error in getting message queue id \n");
		exit(1);
	} else {
		printf("Success in getting message queue id => %d \n",msqid);
	}
	mesg.type = 1;
	
	for (i = 0; ; i++){
		ret = msgsnd(msqid, &mesg, 1 , IPC_NOWAIT);
		if(ret == -1 ){
			printf("Error in sending message number  => %d\n",i);
			break;
		} else {
			printf("Message number = %d\n", i);
			max_mesg = i;
		}
	}
	printf("Maximum number of bytes on a message queue %d\n", (i - 1 ));
		
	ret = msgctl(msqid,IPC_RMID,NULL);
	if(ret == -1){
		printf("Error in removing message queue id \n");
		exit(1);
	} else {
		printf("Success in removing message queue id => %d \n",msqid);
	}

	return 0;
}
