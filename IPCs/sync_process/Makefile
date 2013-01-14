all: pthread_mutex_lock pthread_cond_wait

pthread_mutex_lock:
	gcc pthread_mutex_lock.c -lpthread -o pthread_mutex_lock

pthread_cond_wait:
	gcc pthread_cond_wait.c -lpthread -o pthread_cond_wait


clean:
	@echo clean
	@rm -rf pthread_mutex_lock
	@rm -rf pthread_cond_wait 

rebuild: clean all
