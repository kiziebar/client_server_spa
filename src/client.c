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

// Create socket
void create_socket(int *sockfd){

	*sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(*sockfd < 0){
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
}

// Filling server information
void set_info_server(struct sockaddr_in *servaddr){

	servaddr->sin_family = AF_INET;
	servaddr->sin_port = htons(PORT); //htons - convert values between host and network byte order
	servaddr->sin_addr.s_addr = INADDR_ANY;

}

// Chat between client and server
void chat_client(int *sockfd, struct sockaddr_in *servaddr){

	char *string = malloc(sizeof(char) * 1024);
	int n, len;
	char *hello = "Hello from client";
	char buffer[MAXLINE];
	do{
                scanf("%s", string);
                sendto(*sockfd, (const char*)string, strlen(string), MSG_CONFIRM, (const struct sockaddr *) servaddr, sizeof(*servaddr));
                printf("Hello message sent. \n");
                if(strcmp(string, "exit\0") == 0)
                        break;
                n = recvfrom(*sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *) servaddr, &len);
                buffer[n] = '\0';
                printf("Server : %s\n", buffer);
        }while(string);
        close(*sockfd);
        free(string);

}

// Driver main
int main(){

	int sockfd;
	struct sockaddr_in servaddr;

	create_socket(&sockfd);

	memset(&servaddr, 0, sizeof(servaddr));

	set_info_server(&servaddr);

	chat_client(&sockfd, &servaddr);

	return 0;
}
