#ifndef __TCP_SERVER
#define __TCP_SERVER

// Create socket, set sockaddr and bind socket
void create_set_bind(int *sockfd, struct sockaddr_in *servaddr);

// Make socket non-blocking
int non_block(int sockfd);

// Add and accept new event to epoll
void add_event(struct epoll_event *event, int *single_event, int *epoll_fd);

// Chat server with clients
void chat_server(int *single_event);

#endif// __TCP_SERVER