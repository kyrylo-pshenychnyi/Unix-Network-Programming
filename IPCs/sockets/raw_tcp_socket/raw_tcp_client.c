/* Prgram which will generate raw tcp packets and send over 
the network */
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

#define BUFFER_SIZE 4096

char src_addr[15];
char dst_addr[15];



void usage(void){
    printf("Usage: ./a.out <Destination_address> <Source address> <src port number> <dst port number>\n");
    exit(0);
}

unsigned short in_cksum(unsigned short *addr, int len)
{
    register int sum = 0;
    u_short answer = 0;
    register u_short *w = addr;
    register int nleft = len;
    /*
     * Our algorithm is simple, using a 32 bit accumulator (sum), we add
     * sequential 16 bit words to it, and at the end, fold back all the
     * carry bits from the top 16 bits into the lower 16 bits.
     */
    while (nleft > 1){
      sum += *w++;
      nleft -= 2;
    }
    /* mop up an odd byte, if necessary */
    if (nleft == 1){
      *(u_char *) (&answer) = *(u_char *) w;
      sum += answer;
    }

}


char* getip()
{
    char buffer[256];
    struct hostent* h;

    gethostname(buffer, 256); // Gives the host name of the processor
    h = gethostbyname(buffer); // Give the ip address.

    return inet_ntoa(*(struct in_addr *)h->h_addr); // Converting the Network into assci character
}


void parse_argvs(char *argv[])
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
        strncpy(dst_addr, argv[1], 15);
        strncpy(src_addr, getip(), 15);
        return;
    } else if (argv[1] && argv[2]){
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
    struct sockaddr_in connection;
    int ret;
    int optval;
    int addr_len;

    char *packet;
    char *buffer;

    if(getuid() != 0){
        printf("Permission Denied: Root prevelegde is required\n");
        exit(0);
    }

    if(argc < 5){
        usage();
        return 0;
    }

    parse_argvs(argv);        
    printf("Source address:         %s\n", src_addr);
    printf("Destination Address     %s\n", dst_addr);
    
    /* Allocating all the necessary memory allocation */

    ip = (struct iphdr *) malloc(sizeof( struct iphdr)); 
    tcp = (struct tcphdr *)malloc(sizeof(struct tcphdr));
    packet = (char*)malloc(sizeof(struct iphdr) + sizeof(struct tcphdr));
    buffer = (char *)malloc(sizeof(struct iphdr) + sizeof(struct tcphdr));
    
    
    ip = (struct iphdr*)packet;
    tcp = (struct tcphdr *)(packet + sizeof(struct iphdr)); 
    
    ip->ihl                 = 5;
    ip->version             = 4;
    ip->tos                 = 0;
    ip->tot_len             = sizeof(struct iphdr) + sizeof(struct tcphdr);
    ip->id                  = htons(100);
    ip->ttl                 = 255;
    ip->protocol            = 6; //TCP
    ip->saddr               = inet_addr(src_addr);
    ip->daddr               = inet_addr(dst_addr); 
    ip->check               = in_cksum((unsigned short *)ip, sizeof(struct iphdr));


    /* Filling TCP structure */
    tcp->source             = htons(atoi(argv[4]));
    tcp->dest               = htons(atoi(argv[5]));
    tcp->seq                = htons(1);
    tcp->ack_seq            = 0;
    tcp->window             = htons(32767);
    tcp->check              = in_cksum((unsigned short *)tcp, sizeof(struct tcphdr)); 
    tcp->urg_ptr            = 0;


    /* create the socket */
    socket_fd = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
    if(socket_fd == -1){
        perror("socket");
        exit(-1);
    }
    /* Inform kernel to not include the header. We have created or own */
    ret = setsockopt(socket_fd, IPPROTO_IP, IP_HDRINCL, &optval, sizeof(int));
    if (ret == -1){
        perror("setsockopt\n");
        exit(-1);
    }

    connection.sin_family = AF_INET;
    connection.sin_addr.s_addr = inet_addr(dst_addr);
    sendto(socket_fd,packet, ip->tot_len, 0, (struct sockaddr *)&connection, sizeof(struct sockaddr));
    printf("Sent %lu byte packets to %s\n",sizeof(packet), dst_addr);
     
    close(socket_fd);
    return 0;
}

