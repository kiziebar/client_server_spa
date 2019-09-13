#include <netinet/in.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "functions.h"

const int MAX_EVENTS 5;

// Server function
int main()
{
    int sockfd, event_count;
    struct sockaddr_in servaddr;
    struct epoll_event event, events[MAX_EVENTS];
    int epoll_fd = epoll_create(3);

    // Checking fd epoll
    if(epoll_fd == -1)
    {
        printf("epoll fd fail");
        exit(0);
    }

    create_set_bind(&sockfd, &servaddr);

    // Now server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed...\n");
        exit(0);
    }
    else
        printf("Server listening..\n");

    event.events = EPOLLIN | EPOLLET;
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
                if(events[i].data.fd == sockfd)
                {
                    add_event(&event, &events[i].data.fd, &epoll_fd);
                }
                else
                {
                    chat_server(&events[i].data.fd);
                }
        }
    }
    // After chatting close the sockets
    close(epoll_fd);
    close(sockfd);
}

