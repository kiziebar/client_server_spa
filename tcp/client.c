#include <stdlib.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#define MAX 80
#define PORT 8123
#define SA struct sockaddr

int main()
{
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;
    char string[222];
    // socket create and varification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));
    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);
    connect(sockfd, (struct sockaddr *) &servaddr, sizeof(struct sockaddr));

    while(1)
    {
        printf("Podaj stringa \n");
        scanf("%s", string);
	send(sockfd, string, strlen(string),0);
        if(strcmp(string, "exit") == 0)
            break;
    }


    // close the socket
    close(sockfd);
}

