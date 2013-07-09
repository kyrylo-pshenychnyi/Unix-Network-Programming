#define _XOPEN_SOURCE 600

#include <limits.h> /* For LONG_MAX */
#include <fcntl.h> /*For open()*/
#include <unistd.h> /*For close(), read(), write(), nice()*/
#include <stdlib.h> /*For exit()*/
#include <stdio.h> /*For fprintf(),perror()*/
#include <signal.h> /*For signal()*/
#include <sys/types.h> /* For pid_t */
#include <sys/wait.h> /* For wait() */
#include <string.h> /* For wait() */

static volatile sig_atomic_t sigusr1 = 0;

#define BUF_SIZE 200
void my_handler(int);
void displayUsage(FILE *, const char *);

int main(int argc, char **argv)
{
    char c[BUFSIZ]; /* To hold the string that has been read from the file */
    int fd; /* file descriptor */
    int n;
    long int nBytes; /* To hold the number of bytes to read */
    pid_t pid;
    int child_status;
    char buff[BUF_SIZE];
    /* Display usage if user use this process wrong */
    if(argc != 3){
        displayUsage(stderr, argv[0]);
        exit(1);
    }

    /* Convert argv[1] to long - number of bytes to read */
    nBytes = strtol(argv[1], NULL, 10);
    if((nBytes <= 0) || (nBytes > INT_MAX)){
        fprintf(stderr, "Bufferize %s is not a positive integer\n",
                argv[1]);
        exit(2);
    }

    /* Open a file */
    if((fd = open(argv[2],O_RDONLY,0)) < 0){
        perror(argv[2]);
        exit(3);
    }

    /* Attempt to register a signal handler */
    if(signal(SIGUSR1, my_handler) == SIG_ERR){
        perror("Could not set a handler for SIGUSR1");
        exit(4);
    }

    /* lowering the process priority */
    if(nice(40) < 0){
        perror("Cannot lower the priority");
        exit(5);
    }

    /* Create a new process */
    pid = fork();
    if(pid < 0){
        perror("fork");
        exit(6);
    }
    /* Allocating memory space for string/data to be read from the file
       if(!(c = malloc(nBytes))){
       perror("ERROR");
       exit(4);
       }*/

    if(pid == 0){
        pause();
        /* I'm the child */
        printf("Child's turn %d!\n", (int)getpid());
        lseek(fd, 0L, SEEK_SET);
        /* Read The File */
        while((n = read(fd, c, nBytes)) != 0){
            /* Write content of 'c' to the stdout */
            if(write(STDOUT_FILENO, c, n) < 0){
                perror("Write Error!\n");
                exit(7);
            }
        }
        /* Close the file */
        if(close(fd) < 0){
            perror(argv[2]);
            exit(38);
        } else {
            printf("close fd in %d\n", (int)getpid());
        }   
        printf("Child exiting (status = 0x25)\n");
        exit(37);
    }
    else{
        /* I'm the parent */
        sprintf(buff,"Parent's turn! (pid = %d, kid = %d)\n", (int)getpid(), (int)pid);
        write(1, buff, strlen(buff));
        /* Read The File */
        while((n = read(fd, c, nBytes)) != 0){
            /* Write content of 'c' to the stdout */
            if(write(STDOUT_FILENO, c, n) < 0){
                perror("Write Error!\n");
                exit(7);
            }
        }
        printf("Parent signalling Child\n");
        kill(pid, SIGUSR1);
        /* Reap the child */
        int corpse = wait(&child_status);
        printf("waiting over: pid = %d, status = 0x%.2X\n", corpse, child_status);

        /* Close the file */
        if(close(fd) < 0){
            perror(argv[2]);
            exit(8);
        } else {
            printf("close fd in %d\n", (int)getpid());
        }

        printf("%d exiting\n", (int)getpid());
        return(0);
    }
}

void displayUsage(FILE *fp, const char *arg)
{
        fprintf(fp, "Usage: %s n filename\n", arg);
        fprintf(fp, "where\n");
        fprintf(fp, 
            "\tn\tNumber of bytes to read and write in each \"block\".\n");
        fprintf(fp,"\tfilename\tName of file to be catted.\n");
}

void my_handler(int sig)
{
    printf("Caught the signal %d in %d\n",sig, getpid());
}
