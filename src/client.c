#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include "functions.h"


// Driver main
int main(){

        int sockfd;
        struct sockaddr_in servaddr;
        create_socket(&sockfd);
	memset(&servaddr, 0, sizeof(servaddr));
        set_info(&servaddr);
        chat_client(&sockfd, &servaddr);

        return 0;
}

