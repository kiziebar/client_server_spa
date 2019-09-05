#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8080
#define MAXLINE 1024

// Driver code
int main(){

	int sockfd;
	char buffer[MAXLINE];
	char *hello = "Hello form client";
	struct sockaddr_in servaddr;

	// Creating socket file descriptor
	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	memset(&servaddr, 0, sizeof(servaddr));

	// Filling server information
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;

	int n, len;

	char *string = malloc(sizeof(char) * 1024);

	do{
		scanf("%s", string);
		sendto(sockfd, (const char*)string, strlen(string), MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
		printf("Hello message sent. \n");
		if(strcmp(string, "exit\0") == 0)
			break;
		n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *) &servaddr, &len);
		buffer[n] = '\0';
		printf("Server : %s\n", buffer);
	}while(string);
	close(sockfd);
	free(string);
	return 0;
}
