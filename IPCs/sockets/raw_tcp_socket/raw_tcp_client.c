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

char src_addr[15];
char dst_addr[15];



void usage(void){
    printf("Usage: ./a.out <Destination_address> <Source address>\n");
    exit(0);
}

unsigned short check_sum(unsigned short *, int);



char* getip()
{
    char buffer[256];
    struct hostent* h;

    gethostname(buffer, 256); // Gives the host name of the processor
    h = gethostbyname(buffer); // Give the ip address.

    return inet_ntoa(*(struct in_addr *)h->h_addr); // Converting the Network into assci character
}


void parse_argvs(char * argv[]);
{
    int i;
    if(argv[1] == NULL){
        usage();
    }
    if ((argv[1] != NULL) && (argv[2] == NULL)){
        /*
         *   only one argument provided
         *   assume it is the destination server
         *   source address is local host
         */
        strncpy(dst, argv[1], 15);
        strncpy(src, getip(), 15);
        return;
    } else if (atgv[1] && argv[2]){
        /*
         *    both the destination and source address are defined
         *    for now only implemented is a source address and
         *    destination address
         */
        strncpy(dst_addr, argv[1], 15);
        strncpy(src_addr, argv[2], 15);
    }
}


int main(int argc, char *argv[]){
    struct iphdr *ip = NULL;
    struct tcphdr *tcp = NULL;
    int socket_fd;
    struct sockaddr_in dst_addr;
    struct sockaddr_in src_addr;
    char buffer[BUFFER_SIZE];
    int addr_len;

    char *pcaket;
    char *buffer;

    if(getuid() != 0){
        printf("Permission Denied: Root prevelegde is required\n");
        exit(0);
    }

    if(argc < 3){
        printf("Usage: ./a.out <Destination_address> <port number>\n");
        return 0;
    }

    parse_argvs(argv);        
    printf("Source address:         %s\n", src_addr);
    printf("Destination Address     %s\n", dst_addr);
    
    /* Allocating all the necessary memory allocation */

    ip = (struct iphdr *) malloc(sizeof( struct iphdr)); 
    tcp = (struct tcphdr *)malloc(sizeof(struct tcphdr));
    packet = (char *)malloc(sizeof(struct iphdr) + sizeof(struct tcphdr));
    buffer = (char *)malloc(sizeof(struct iphdr) + sizeof(struct tcphdr));
    
    
    ip = (struct iphdr*)packet;
    tcp = (struct tcp *)(packet + sizeof(struct iphdr)); 

    





    
    return 0;
}

