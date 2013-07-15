#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/time.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>


#define MAX_FD 10
#define BUFF_SIZE 200
#define DEFAULT_PORT 23456
int main( int argc, char * argv[]){
    int ret;
    int socketfd,connectfd;
    int serv_port;
    int client[FD_SETSIZE];
    struct sock_addr_in server_addr, client_addr;
    int i;
    fd_set allset, rset;

    socketfd =  socket(AF_INET, SOCK_STREAM, 0);
    if(socketfd == -1){
        perror("Socket\n");
        exit(1);
    }
   
    if(argv[1] == NULL){
        serv_port = DEFAULT_PORT;
    } else {
        serv_port = atoi(argv[1]);
    }
    
    bzero(&server_addr,sizeof(server_addr));
    bzero(&client_addr,sizeof(client_addr));

    server_addr.sin_faimily     = AF_INET;
    server_addr.sin_port        = htons(serv_port);
    server_addr.sin_addr.s_addr = hton(INADDR_ANY)
    
    ret = bind(socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if(ret == -1){
        perror("Bind\n");
        exit(2);
    } 

    ret = listen(socketfd, MAX_FD);
    if(ret == -1){
        perror("listen\n"); 
        exit(3);
    }

    max_fd = socketfd;
    for(i = 0; i< FD_SETSIZE ; i++){
        client[i] = -1;
    }
    FD_ZERO(&allset);
    FD_SET(socketfd, &allset);
    printf("The value of FD_SETSIZE = %d\n", sizeof(FD_SETSIZE));

    int ready;
    
    for (; ; ){
        rset = allset;
        ready = select(max_fd + 1, &rset , NULL ,NULL, NULL); 
        if(ready == -1){
            perror("Select\n");
            exit(3);
        }
        if(FD_ISSET(socketfd, &rset)){
            int clilen = sizeof(client_addr);
            connectfd =  accept(socketfd,
                                (struct sock_addr*)&(client_addr), 
                                &clilen);
            printf("new client: %s, port %d\n",
                    Inet_ntop(AF_INET, &cliaddr.sin_addr, 4, NULL),
                    ntohs(cliaddr.sin_port));
            
            for(i = 0; i< FD_SETSIZE, i++){
                if(client[i] < 0){
                    client[i] = connectfd;
                    break;
                }
            }
            if(i == FD_SETSIZE){
                printf("Max count for client reached\n");
                exit(5);
            }
            
            FD_SET(connectfd, &allset);
            if(connectfd > max_fd){
                max_fd = connectfd;
            }
            if(i > max_fd){
                max_fd = 1;
            }
            
            if( --neready <= 0){
                continue;
            }
        } 
        for (i = 0; i <= maxi; i++) {   /* check all clients for data */
            if ( (sockfd = client[i]) < 0)
                continue;
            if (FD_ISSET(sockfd, &rset)) {
                if ( (n = Read(sockfd, buf, MAXLINE)) == 0) {
                        /*4connection closed by client */
                    Close(sockfd);
                    FD_CLR(sockfd, &allset);
                    client[i] = -1;
                } else
                    Writen(sockfd, buf, n);

                if (--nready <= 0)
                    break;              /* no more readable descriptors */
            }
        }
    }
    return 0;
}





