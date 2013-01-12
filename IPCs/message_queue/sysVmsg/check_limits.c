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


#define MAX_DATA 64*1024
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

	//msqid = msgget(IPC_PRIVATE,SVMSG_MODE|IPC_CREAT);
	msqid = msgget(IPC_PRIVATE,0775|IPC_CREAT);
	if(msqid == -1){
		printf("Error in getting message queue id \n");
		exit(1);
	} else {
		printf("Success in getting message queue id => %d \n",msqid);
	}
	mesg.type = 1;
	//ret = msgsnd(msqid, &mesg, 1, 0);
	
	for (i = 0; ; i++){
		ret = msgsnd(msqid, &mesg, 1, IPC_NOWAIT);
		if(ret == -1 ){
			printf("Error in sending message on message queue => %d\n",msqid);
			break;
		} else {
			printf("Maximum amount of data per message = %d\n", i);
			max_mesg = i;
		}
	}
	
	if (i == 0){
		printf("Error quit message\n");
	}	
			
/*	ret = msgctl(msqid,IPC_RMID,NULL);
	if(ret == -1){
		printf("Error in removing message queue id \n");
		exit(1);
	} else {
		printf("Success in removing message queue id => %d \n",msqid);
	}
*/
	return 0;
}
