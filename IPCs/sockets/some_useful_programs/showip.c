/*
	File 		: showip.c 
	Brief		: Show IP addresses for a host given on the command line
	Date		: 1st Jan 2013
	Author		: Prakash Ranjan
	
*/

/*
	TODO: Program is  getting segmentation fault at line 61 or 66 
		  when entering unknown hostname.
*/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int status;
	int ret;
    char ipstr[INET6_ADDRSTRLEN];
    struct addrinfo hints, *res, *p;
	int i = 0;

    memset(&hints, 0, sizeof hints);

    if (argc != 2) {
        fprintf(stderr,"usage: ./showip hostname\n");
        exit(-1);
    }

    hints.ai_family = AF_UNSPEC; // AF_INET or AF_INET6 to force version
    hints.ai_socktype = SOCK_STREAM;


	ret = getaddrinfo(argv[1], NULL, &hints, &res);
	if(ret == -1){
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        return 2;
    }

    printf("IP addresses for %s:\n\n", argv[1]);

    for(p = res; p != NULL; p = p->ai_next) {
		printf("========== %2d ===========\n",i++);
        void *addr;
        char *ipver;

        // get the pointer to the address itself,
        // different fields in IPv4 and IPv6:
        if (p->ai_family == AF_INET) { // IPv4
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
            addr = &(ipv4->sin_addr);
            ipver = "IPv4";
        } else { // IPv6
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
            addr = &(ipv6->sin6_addr);
            ipver = "IPv6";
        }

		// convert the IP to a string and print it:

        inet_ntop(p->ai_family, addr, ipstr, sizeof(ipstr));
        printf("  %s: %s\n", ipver, ipstr);
		if(p->ai_next == NULL){
			break;
		}
    }

    freeaddrinfo(res); // free the linked list

	printf("==========================\n",i++);
    return 0;
}
