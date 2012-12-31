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
				5. Send/Recv()
				6. Close()
*/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>


int main(int argc, char * argv[]){
	int ret;
	int socketfd, connectfd,
	char buff[1024];
	
	struct sockaddr_in server, client;
	
	memset(&server,0,sizeof(server));
	memset(&server,0,sizeof(server));

	if( argc < 2 ){
		printf("Usage: ./ser <port number>\n");
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

	ret = listen();
	if(ret == -1){
		perror("listen");
		exit(-1);
	} else {
		printf("Success in listen system call\n");
	}

// 4. Bind system call

	ret = accept();
	if(ret == -1){
		perror("accept");
		exit(-1);
	} else {
		printf("Success on accept system call\n");
	}

// 5. Send/Recv System call

	ret = send();
	if( ret == -1 ){
		perror("send");
		exit(-1);
	} else {
		printf("Send buffer data is successfull\n");
	}

// 6. Close system call.

	close(socketfd);

	return 0;
}
