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

int main(void)
{
	FILE * fd;
	int msgmax = 0;
	int msgmnb = 0;
	int msgmni = 0;


	fd = fopen("/proc/sys/kernel/msgmax","r");
	if(fd == NULL){
		printf("Error in opening the file\n");
		exit(1);
	}

	fscanf(fd,"%d",&msgmax);
	printf("\nThe maximum bytes per message ===========> %d\n",msgmax);

	fclose(fd);

	fd = fopen("/proc/sys/kernel/msgmnb","r");
	if(fd == NULL){
		printf("Error in opening the file\n");
		exit(1);
	}

	fscanf(fd,"%d",&msgmnb);
	printf("The maximum bytes on any message queue ==> %d\n",msgmnb);

	fclose(fd);

	fd = fopen("/proc/sys/kernel/msgmni","r");
	if(fd == NULL){
		printf("Error in opening the file\n");
		exit(1);
	}

	fscanf(fd,"%d",&msgmni);
	printf("The maximum message queue systemwide ====> %d\n\n",msgmni);

	fclose(fd);


	return 0;
}
