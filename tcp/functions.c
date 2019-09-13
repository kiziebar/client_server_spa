#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <fcntl.h>
#include "functions.h"
#define READ_SIZE 10
#define PORT 8123
#define SA struct sockaddr


void create_set_bind(int *sockfd, struct sockaddr_in *servaddr)
{
    // Socket create and verification
    *sockfd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
    if(*sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(servaddr, sizeof(*servaddr));

    // Assign IP, PORT
    servaddr->sin_family = AF_INET;
    servaddr->sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr->sin_port = htons(PORT);

    // Binding newly created socket to given IP and verification
    if ((bind(*sockfd, (SA*)servaddr, sizeof(*servaddr))) != 0) {
        printf("Socket bind failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully binded..\n");
}

int non_block(int sockfd)
{
    int flag;
    if((flag = fcntl(sockfd, F_GETFL, 0)) == -1)
    {
        printf("Non-blocking socked failed...");
        exit(0);
    }

    flag |= O_NONBLOCK;
    if(fcntl(sockfd, F_SETFL, flag) == -1)
    {
        printf("Non-blocking socked failed...");
        exit(0);
    }
    return 0;
}

void add_event(struct epoll_event *event, int *single_event, int *epoll_fd)
{
    int new_fd;
    struct sockaddr_in client;
    socklen_t addr_size = sizeof(client);

    // Accept new file descriptor
    new_fd = accept(*single_event, (struct sockaddr *) &client, &addr_size);
    if(new_fd == -1)
        printf("New descriptor not accept...");
        exit(0);
    printf("New connection on server...\n");

    // Make new file descriptor non-blocking
    non_block(new_fd);
    event->events = EPOLLIN | EPOLLET;
    event->data.fd = new_fd;
    epoll_ctl(*epoll_fd, EPOLL_CTL_ADD, new_fd, event);
}

void chat_server(int *single_event)
{
    char read_buffer[READ_SIZE + 1];
    ssize_t count;

    // Read message from client
    count = read(*single_event, read_buffer, sizeof(read_buffer)-1);
    read_buffer[count] = '\0';
    printf("%s \n", read_buffer);
    if(strcmp(read_buffer,"exit") == 0)
    {
        printf("Event close...\n");
        close(*single_event);
    }
}