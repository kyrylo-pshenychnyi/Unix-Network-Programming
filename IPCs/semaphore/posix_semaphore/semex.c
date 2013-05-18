#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/stat.h>
/* Without use of shared memory, the semaphore doesn't work across
   processes!  Of course it would work with threads in one process,
   since they share the process address space. */
/* uncomment the next line to start using shared memory for sem_t object */
/*#define USE_SHARED_MEMORY */
#define MAXPIDS 10
#define USE_SHARED_MEMORY
void worker(int i, void * args);

int main(int argc, char *argv[]) {
	int error;
	int i;
	int id, n;
	sem_t *semlock;
	pid_t pids[MAXPIDS];
	if (argc != 2){   /* check for valid number of command-line arguments */
		fprintf (stderr, "Usage: %s numprocesses\n", argv[0]);
		return 1;
	}
	n = atoi(argv[1]);
	if (n > MAXPIDS){
		printf("The maximun number of Process can be only 10\n");
		return 1;
	}
#ifdef USE_SHARED_MEMORY
	printf("Using shared memory\n");
	if ((id = shmget(IPC_PRIVATE, sizeof(sem_t), (S_IRUSR|S_IWUSR))) == -1) {
		perror("Failed to create shared memory segment");
		return 1;
	}
	if ((semlock = (sem_t *)shmat(id, NULL, 0)) == (void *)-1) {
		perror("Failed to attach memory segment");
		return 1;
	}
#else
/* try using ordinary process-private memory for sem_t variable */
	semlock = (sem_t *)malloc(sizeof(sem_t));
#endif
	if (sem_init(semlock, 1/*shared across processes*/, 1) == -1) {
		perror("Failed to initialize semaphore");
	} else {
		for (i = 0; i < n; i++) {
			if ((pids[i] = fork()) < 0) {
				fprintf(stderr, "Failed to create process:%s\n",
				strerror(error));
				return 1;
			}
			if (pids[i] == 0) {          /* child */
				worker(i, semlock);
				exit(0);
			}
		}
/* here in parent of all */
		for (i = 0; i < n; i++){
			wait(0);
		}
		fprintf(stderr, "workers all done\n");
	}
#ifdef USE_SHARED_MEMORY
	if (shmdt((void *)semlock) == -1) {  /* shared memory detach */
		perror("Failed to destroy shared memory segment");
		return 1;
	}
#else
	free(semlock);
#endif
	return 0;
}
