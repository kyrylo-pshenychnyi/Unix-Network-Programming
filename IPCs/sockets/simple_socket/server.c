/*
	File  : server.c
	Brief : This file is used for accepting the 
		    connection request from client application.
	Date  : 31st Dec 2012
	Author: Prakash Ranjan
*/

/*
				Server Side system call 
			  ============================
				1. Socket()
				2. Bind()
				3. Listen()
				4. Accept()
				5. Send/Recv() // Any system call which can be used for 
				                  reading or writing on a file.eg: read, write, 
								  fput, fget
				6. Close()
*/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<errno.h>
#include<arpa/inet.h>
#include<string.h>


int main(int argc, char * argv[]){
	int ret;
	int socketfd; 
	int connectfd;
	char buff[30];
	
	struct sockaddr_in server, client;
	
	memset(&server,0,sizeof(server));
	memset(&server,0,sizeof(server));

	if( argc < 2 ){
		printf("Usage: ./srv <port number>\n");
		printf("Eg: ./srv 5000\n");
		exit(0);
	}

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(atoi(argv[1]));

// 1. Calling Socket function call 

	ret = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(ret == -1){
		perror("Socket");
		exit(-1);
	} else {
		socketfd = ret;
		printf("Success in calling socket system call\n");
	}  

// 2. Bind system call

	ret = bind(socketfd, (struct sockaddr *)&server, sizeof(struct sockaddr));
	if( ret == -1 ){
		perror("bind");
		exit(-1);
	} else {
		printf("Success in bind system call\n");
	}

// 3. Listen syatem call

	ret = listen(socketfd, 5);
	if(ret == -1){
		perror("listen");
		exit(-1);
	} else {
		printf("Success in listen system call\n");
	}

// 4. Bind system call

	printf("Waiting for a client request ... \n");

	socklen_t len = sizeof(server);
	ret = accept(socketfd,( struct sockaddr *)&server,&len);
	if(ret == -1){
		perror("accept");
		exit(-1);
	} else {
		connectfd = ret;
		printf("Success on accept system call\n");
	}

    int i = 0;
    while (i != 5){
        i++;
        sleep(3);
    }

#if 1
// 5. Send/Recv System call

	strcpy(buff,"Hi client, Welcome to server.. ");
	printf("Buffer content:\t%s\n",buff);


	/* Be carefull: Here connectfd is file discriptor which is returned by
					accept system call not by the connect system call. */


    
	ret = send(connectfd, buff, sizeof(buff), 0);
	if( ret == -1 ){
		perror("send");
		exit(-1);
	} else {
		printf("Send buffer data [%ld Bytes] is successfull\n", strlen(buff));
	}
#endif
// 6. Close system call.
    i = 0;
    while (i != 5){
        i++;
        sleep(3);
    }
	close(socketfd);

	return 0;
}
