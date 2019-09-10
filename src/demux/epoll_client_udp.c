#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netdb.h>
#include <string.h>
#include "functions.h"


// Driver main
int main(){

        int sockfd;
	int val = 1;
	char *buff = "sieeeema";
        struct sockaddr_in servaddr, cliaddr;
	struct hostent *host;
        create_socket(&sockfd);
	memset(&cliaddr, 0, sizeof(servaddr));
        set_info(&cliaddr);
	if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val)) == -1)
		printf("ERROR");
	if(bind(sockfd, (struct sockaddr *) &cliaddr, sizeof(cliaddr)) < 0)
		printf("BIND ERROR");
	host = gethostbyname("127.0.0.1");
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr = *((struct in_addr *)host->h_addr);
        servaddr.sin_port = htons(8888);

	sendto(sockfd, buff, strlen(buff), 0, (struct sockaddr *) &servaddr, sizeof(servaddr));



	//chat_client(&sockfd, &servaddr);

        return 0;
}

