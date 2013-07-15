#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/time.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>



#define MAX_FD 10
#define BUFF_SIZE 200
#define DEFAULT_PORT 23456

int main( int argc, char * argv[]){
    int ret;
    int socketfd,connectfd;
    int serv_port;
    int client[FD_SETSIZE];
    char buf[BUFF_SIZE];
    struct sockaddr_in server_addr, client_addr;
    int i, max_fd;
    fd_set allset, rset;

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
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

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(serv_port);
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    
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

    printf("The value of FD_SETSIZE = %d\n",FD_SETSIZE);
    printf("The value of socketfd = %d\n",socketfd);
    max_fd = socketfd;
    for(i = 0; i< FD_SETSIZE ; i++){
        client[i] = -1;
    }
    FD_ZERO(&allset);
    FD_SET(socketfd, &allset);

    int maxi = -1;
    int nready, n;
    for (; ; ){
        rset = allset;
        nready = select(max_fd + 1, &rset , NULL ,NULL, NULL);
        if(nready == -1){
            perror("Select\n");
            exit(3);
        } else {
            printf("Number of ready discriptor = %d\n", nready);
        }

#if 1
        int a = 0;
        int b = 0;
        int c = 0;
        for(a = 3; a < FD_SETSIZE; a++){
            if(FD_ISSET(a,&rset)){
                printf("1 ");
            } else {
                printf("0 ");   
            }
            b++;
            if(b == 16){
                printf("\n");
                b = 0;
                break; // Not expecting more than 16 client request at a time 
            }
        }
#endif
        if(FD_ISSET(socketfd, &rset)){
            int clilen = sizeof(client_addr);
            connectfd = accept(socketfd,
                               (struct sockaddr*)&(client_addr),
                                &clilen);
            if( connectfd == -1){
                perror("Accept:\n");
                exit(7);
            } else {
#if 1
                char str[100];
                printf("new client: %s, port %hu => Client fd - %d\n",
                    inet_ntop(AF_INET, (struct sockaddr *) &client_addr.sin_addr, str, 100),ntohs(client_addr.sin_port), connectfd);
#endif
            }
            for(i = 3; i < FD_SETSIZE; i++){
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
            if(i > maxi){
                maxi = i;
            }
            
            if( --nready <= 0){
                continue;
            }
        }
        for (i = 0; i <= maxi ; i++) { /* check all clients for data */
            printf("==================== STEP 1 =====================\n");
            if ( (socketfd = client[i]) < 0){
                printf("==================== STEP 2 =====================\n");
                continue;
            }
            if (FD_ISSET(socketfd, &rset)) {
                memset(buf, 0, sizeof(buf));
                printf("==================== STEP 3 =====================\n");
                n = read(socketfd, buf, BUFF_SIZE);
                if ((n == 0) || ( n == -1)  ) {
                    perror("Read:\n");
                    printf("==================== STEP 4 =====================\n");
                        /*4connection closed by client */
                    close(socketfd);
                    FD_CLR(socketfd, &allset);
                    client[i] = -1;
                } else
                    printf("==================== STEP 5 =====================\n");
                    printf("Data read from client [ %s ] with socket %d\n", buf, socketfd); 
                    if(write(socketfd, buf, n) == -1){
                        printf("==================== STEP 6 =====================\n");
                        perror("Write:\n");
                        exit(6);
                } 
                printf("==================== STEP 7 =====================\n");

                if (--nready <= 0)
                    break; /* no more readable descriptors */
            }
        }
    }
    return 0;
}
