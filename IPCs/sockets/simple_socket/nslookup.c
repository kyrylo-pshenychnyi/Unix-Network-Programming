/* 	Program to get the ip address of a host by its name.
  	The same functionality can be get by using nslookup
	utility from command line. This is done usin programming
*/

#include<stdio.h>
#include<stdlib.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<netinet/in.h>

int main(int argc, char * argv[]){
	printf("\nProgram to show the usage of gethostbyname() C function\n");
	printf("=======================================================\n");
	struct hostent *host;
	struct in_addr h_addr;
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
		printf("\n%s ->  %s\n\n",argv[1],inet_ntoa(h_addr));
		return 0;
	}
	return 0;
}
	
	
