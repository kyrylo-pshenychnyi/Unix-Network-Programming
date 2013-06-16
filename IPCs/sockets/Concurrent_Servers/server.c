#include<stdio.h>
#include<sys/types.h>
#include<netdb.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<linux/ip.h>
#include<linux/tcp.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>




#define MAX_SIZE 200
#define MAX_QUEUE 3

int main(int argc, char * argv[]){
    int connectfd, listenfd;
    struct sockaddr_in serveraddr, clientaddr;
    char buffer[MAX_SIZE];
    int ret;
    int len;
   
    ret = getuid();
    if(ret != 0){
        printf("Permision denied: Please run the code as super user\n");
        exit(0);
    }
 
    listenfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(listenfd == -1){
        perror("Socket\n");
        return -1;
    }
    
    memset(&serveraddr, 0 , sizeof(serveraddr));
    memset(&clientaddr, 0 , sizeof(clientaddr));
   
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(atoi(argv[1])); 
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);


    ret = bind(listenfd,(struct sockaddr *)&serveraddr, sizeof(serveraddr));
    if(ret == -1){
        perror("Bind\n");
        exit(-1);
    }

    listen(listenfd, MAX_QUEUE);
    
    for(;;){
        len = sizeof(clientaddr);
        printf("Waiting for connection\n");
        connectfd = accept(listenfd, (struct sockaddr *) &clientaddr, &len);
        if( connectfd == -1){
            perror("Bind\n");
            exit(-1);
        }
        ret = fork();
        if(ret == 0) {  // Child process
            printf("Got a connection\n");
            close(listenfd);
            /* 
                Do something
            */
            }
            close(connectfd);
            exit(0);
        } else if( ret != -1) {
            close(connectfd);
        } else {
            perror("Fork\n");
        }
    }
    return 0;
}       
  

