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

// Function designed for chat between client and server.
void func(int sockfd)
{
    char buff[MAX];
    int n;
    // infinite loop for chat
    for (;;) {
        bzero(buff, MAX);

        // read the message from client and copy it in buffer
        read(sockfd, buff, sizeof(buff));
        // print buffer which contains the client contents
        printf("From client: %s\t To client : ", buff);
        bzero(buff, MAX);
        n = 0;
        // copy server message in the buffer
        while ((buff[n++] = getchar()) != '\n')
            ;

        // and send that buffer to client
        write(sockfd, buff, sizeof(buff));

        // if msg contains "Exit" then server exit and chat ended.
        if (strncmp("exit", buff, 4) == 0) {
            printf("Server Exit...\n");
            break;
        }
    }
}

// Driver function
int main()
{
    int sockfd, connfd, len, event_count;
    size_t bytes_read;
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
    //len = sizeof(cli);

    // Accept the data packet from client and verification
    //connfd = accept(sockfd, (SA*)&cli, &len);
    //if (connfd < 0) {
    //    printf("server acccept failed...\n");
    //    exit(0);
    //}
    //else
    //    printf("server acccept the client...\n");
    printf("tutaj");
    event.events = EPOLLIN;
    event.data.fd = sockfd;

    if(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, sockfd, &event))
    {
        printf("epoll_ctl error");
        exit(0);
    }

    while(1)
    {
        //printf("dziala");
        event_count = epoll_wait(epoll_fd, events, MAX_EVENTS, 3000);

        for(int i = 0; i < event_count; i++)
        {
            printf("Reading file descriptor '%d' -- ", events[i].data.fd);
            bytes_read = read(events[i].data.fd, read_buffer, READ_SIZE);
            printf("%zd bytes read.\n", bytes_read);
            read_buffer[bytes_read] = '\0';
            printf("Read '%s'\n", read_buffer);
        }
    }
    // Function for chatting between client and server
    //func(connfd);

    // After chatting close the socket
    close(epoll_fd);
    close(sockfd);
}

