/*
	File    : client.c
	Brief   : This file is used for making 
			  connection with the server application.
	Date    : 31st Dec 2012
	Author  : Prakash Ranjan
*/


/*
				Client system calls
			  =======================

					1. Socket()
					2. connect()
					3. Recv()
					4. close()

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
	int sockfd;
	char buff[1024];
	struct hostent *host;
	struct sockaddr_in server, client;
	
	memset(&server, 0, sizeof(server));
	memset(&client, 0, sizeof(client));
	memset(buff, 0, sizeof(buff));
	
 
	if( argc < 3 ) {
		printf("Usage: ./cli < Port Number > < Server iP address >\n");
		printf("Eg: ./cli 5000 127.0.0.1\n");
		exit(1);
	}

	server.sin_family = AF_INET;
	server.sin_port = htons(atoi(argv[1]));

	ret = inet_pton(AF_INET, argv[2], &server.sin_addr);
	if( ret == -1){
        printf("\n inet_pton error occured\n");
        return 1;
    } 

	
// 1. Socket system call 

	ret = socket(AF_INET, SOCK_STREAM,0);
	if(ret == -1){
		perror("socket");
		exit(-1);
	} else {
		printf("Socket system call is success\n");
		sockfd = ret ;
	}

// 2. Connect system call

	socklen_t len = sizeof(server);
	ret = connect(sockfd, (struct sockaddr *)&server, len);
	if(ret == -1){
		perror("Connect");
		exit(-1);
	} else {
		printf("Success in connect system call\n");
	}

// 3. Send/Recv system call

	ret = recv(sockfd, buff,sizeof(buff),0);
	if(ret == -1){
		perror("recv");
		exit(-1);
	} else {
		printf("Message received from server\n");
		printf("%s\n",buff);
	}

// 4. Close system call

	close(sockfd);

	return 0;

}
