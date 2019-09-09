#include <stdlib.h>
#include <stdio.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include "functions.h"

#define MAX_CLIENTS 2


//Driver code
int main()
{
	// sockfd - master_socket
	int sockfd, client_socket[2], max, sd, new_socket, ready;
	struct sockaddr_in servaddr, cliaddr;
	fd_set rset;

	for(int i=0; i < MAX_CLIENTS; i++)
		client_socket[i] = 0;

	create_socket(&sockfd);
	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));
	set_info(&servaddr);
	bind_socket(&sockfd, &servaddr);
	//FD_ZERO(&rset);
	while(1){
		FD_ZERO(&rset);
		FD_SET(sockfd, &rset);
		max = sockfd;
		// add clients to list (child socket to set)

		for(int i=0; i<MAX_CLIENTS; i++){
			//socket descriptor
			sd = client_socket[i];
			//add socket descriptor to list
			if(sd > 0)
				FD_SET(sd, &rset);

			if(sd > max)
				max = sd;
		}
		ready = select(max + 1, &rset, NULL, NULL, NULL);
		if(FD_ISSET(sockfd, &rset)){
			printf("event");
			int len = sizeof(servaddr);
			if((new_socket = accept(sockfd, (struct sockaddr *) &servaddr,(socklen_t*) &len)) < 0){
				printf("%d", new_socket);
				printf("connect fail");
			}
			//chat_server(&new_socket, &servaddr, &cliaddr);
			send(new_socket, "elo", strlen("elo"), 0);
			//add new socket to array of sockets
			for(int i = 0; i < MAX_CLIENTS; i++){

				if(client_socket[i] == 0)
					client_socket[i] = new_socket;
				break;
			}

			break;
		}
	}
	return 0;
}

