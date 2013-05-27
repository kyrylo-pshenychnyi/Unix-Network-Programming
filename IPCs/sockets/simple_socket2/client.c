/* A simple client program in socket */


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>

#define BUFFSIZE 32

#define DIE(message) { \ 
        perror(message);\
        exit(-1);\
    }

int main(int argc, char * argv[]){
    int sock;
    struct sockaddr_in echoserver;
    char buffer[BUFFSIZE];
    unsigned int echolen;
    int received=0;
    int ret;
    
    if( argc < 4){
        printf("USAGE: TCPecho <server ip> <word> <port num> \n");
        exit(0);
    }
    
    /* Create the TCP socket */
    
    sock = socket (PF_INET,SOCK_STREAM, IPPROTO_TCP);
    if( sock <0 ){
        DIE("Socket creation error\n");
    }
    
    /* Construct the server sockaddr_in structure */
    
    memset(&echoserver,0,sizeof(echoserver));
    echoserver.sin_family = AF_INET; // Any Internet address 
    echoserver.sin_addr.s_addr = inet_addr(argv[1]); // IP address 
    echoserver.sin_port = htons(atoi(argv[3]));  // Server port (Converting little endian to big endian ( Network byte order))

    /* Establish connection */

    ret = connect(sock, (struct sockaddr *)&echoserver, sizeof(echoserver));
    if(ret < 0) {
        DIE(" Connect failed \n");
    }
    
    /* Send and Receive Data */

    /* send the word to the server */
    echolen = strlen(argv[2]);
    ret = send(sock, argv[2], echolen,0);
    if( ret != echolen) {
        DIE("Send error\n");
    }
    
    /*Receive the word back from the server */

    printf("Recieved from server: ");
    while(received < echolen){
        int bytes = 0;
        if((bytes = recv(sock,buffer,BUFFSIZE -1,0)) < 0) {
            DIE("Receive failed\n");
        }
        received = bytes + received;
        buffer[bytes] = '\0'; // Assuming NULL terminated bytes
        printf("%s", buffer);
    }
    
    printf("\n");
    close(sock);
    return 0;
}
