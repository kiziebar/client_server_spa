#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PORT 8123

int main()
{
    int sockfd;
    struct sockaddr_in servaddr;
    char string[222];

    // Socket create and varification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));

    // Assign IP, PORT
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

