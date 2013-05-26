/* 	Program to get the ip address of a host by its name.
  	The same functionality can be get by using nslookup
	utility from command line. This is done usin programming
*/

/* 
	For reference:
=============================================================================	
=		struct hostent {													=
=        char    *h_name;        // official name of host 					=
=        char    **h_aliases;    // alias list 								=
=        int     h_addrtype;     // host address type 						=
=        int     h_length;       // length of address 						=
=        char    **h_addr_list;  // list of addresses 						=
=		}																	=
=	#define h_addr  h_addr_list[0]  // for backward compatibility 			=
=============================================================================	
=	struct in_addr {														=
=        unsigned long int s_addr;											=
=	}																		=
=	Note that on the i80x86 the host byte order is Little Endian, 			=
=	whereas the network byte order, as used on the Internet, is Big Endian. = 
=============================================================================
*/


#include<stdio.h>
#include<stdlib.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<netinet/in.h>
int main(int argc, char * argv[]){
	printf("\nProgram to show the usage of gethostbyname() C function\n");
	printf("=======================================================\n");
	struct hostent *host;  // host entity
	struct in_addr h_addr; // Internet address
	int ret ;
	
	if(argc < 2){
		printf("Usage: ./nslookup <hostname>\n");
		printf("Example: ./nslookup www.google.co.in>\n");
		exit(0);
	}

	host = gethostbyname(argv[1]);
	if(host == NULL){
		perror("gethostbyname error\n");
		exit(1);
	} else {
		h_addr.s_addr = *((unsigned long *) host->h_addr_list[0]);
		printf("\n%s -> IP address  	%s\n",argv[1],inet_ntoa(h_addr)); /* Internet address 
																		     Network to ascii (ntoa)*/
		printf("%s -> Length      	%d\n",argv[1],host->h_length);
		printf("%s -> Address type	%d\n",argv[1],host->h_addrtype);
		printf("%s -> Name     		%s\n\n",argv[1],host->h_name);
		return 0;
	}
	return 0;
}
	
	
