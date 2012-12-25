/*
	File: fork.c
	Brief: A example of forking 
	Date: 25th Dec 2012
	Author: Prakash Ranjan 	 
*/

#include  <stdio.h>
#include  <sys/types.h>

#define   MAX_COUNT  5

void  ChildProcess(void);                /* child process prototype  */
void  ParentProcess(void);               /* parent process prototype */

int  main(void)
{
	pid_t  pid;

    pid = fork();
	if (pid == -1){
		printf("Error in forking\n");
		return -1;
	} else if (pid == 0) {
		ChildProcess();
	} else {
		ParentProcess();
	}

	return 0;
}

void  ChildProcess(void)
{
     int   i;

     for (i = 1; i <= MAX_COUNT; i++)
          printf("   This line is from child, value = %d\n", i);
     printf("*** Child process is done ***\n");
}

void  ParentProcess(void)
{
     int   i;

     for (i = 1; i <= MAX_COUNT; i++)
          printf("This line is from parent, value = %d\n", i);
     printf("*** Parent is done ***\n");
}

