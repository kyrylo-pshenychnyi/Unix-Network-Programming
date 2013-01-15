all: pthread_mutex_lock pthread_cond_wait pthread_cond_wait_1

pthread_mutex_lock:
	gcc pthread_mutex_lock.c -lpthread -o pthread_mutex_lock

pthread_cond_wait:
	gcc pthread_cond_wait.c -lpthread -o pthread_cond_wait

pthread_cond_wait_1:
	gcc pthread_cond_wait_1.c -lpthread -o pthread_cond_wait_1

clean:
	@echo clean
	@rm -rf pthread_mutex_lock
	@rm -rf pthread_cond_wait 
	@rm -rf pthread_cond_wait_1 

rebuild: clean all
