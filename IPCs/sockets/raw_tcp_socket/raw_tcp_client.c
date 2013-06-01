/* Prgram which will generate raw tcp packets and send over 
the network */
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<linux/ip.h>
#include<linux/tcp.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define BUFFER_SIZE 4096


int main(int argc, char *argv[]){
    struct iphdr *ip = NULL;
    struct tcphdr *tcp = NULL;
    int socket_fd;
    struct sockaddr_in dst_addr;
    struct sockaddr_in src_addr;
    char buffer[BUFFER_SIZE];
    int addr_len;

    if(getuid() != 0){
        printf("Permission Denied: Root prevelegde is required\n");
        exit(0);
    }

    if(argc < 3){
        printf("Usage: ./a.out <Destination_address> <port number>\n");
        return 0;
    }


    return 0;
}

