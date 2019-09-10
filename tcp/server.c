#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/epoll.h>
#define MAX_EVENTS 5
#define READ_SIZE 10
#define MAX 80
#define PORT 8888
#define SA struct sockaddr

// Driver function
int main()
{
    int sockfd, connfd, len, event_count;
    size_t bytes_read;
    ssize_t count;
    char read_buffer[READ_SIZE + 1];
    struct sockaddr_in servaddr, cli;
    struct epoll_event event, events[MAX_EVENTS];
    int epoll_fd = epoll_create(3);

    // checking fd epoll
    if(epoll_fd == -1)
    {
        printf("epoll fd fail");
        exit(0);
    }

    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    // Binding newly created socket to given IP and verification
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
        printf("socket bind failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully binded..\n");

    // Now server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed...\n");
        exit(0);
    }
    else
        printf("Server listening..\n");
    event.events = EPOLLIN;
    event.data.fd = sockfd;

    if(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, sockfd, &event))
    {
        printf("epoll_ctl error");
        exit(0);
    }

    while(1)
    {
        event_count = epoll_wait(epoll_fd, events, MAX_EVENTS, 3000);
        for(int i = 0; i < event_count; i++)
        {
                 count = read(events[i].data.fd, read_buffer, sizeof(read_buffer)-1);
                 read_buffer[count] = '\0';
                 printf("%s \n", read_buffer);
	 	 printf("jestem");
                 //close(events[i].data.fd);
        }
    }
    // After chatting close the socket
    close(epoll_fd);
    close(sockfd);
}

