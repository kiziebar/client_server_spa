#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include "functions.h"


//Driver code
int main(){

	int sockfd;
	struct sockaddr_in servaddr, cliaddr;
	create_socket(&sockfd);
	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));
	set_info(&servaddr);
	bind_socket(&sockfd, &servaddr);
	chat_server(&sockfd, &servaddr, &cliaddr);

	return 0;
}
