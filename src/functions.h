#ifndef __UDP_CLISER
#define __UDP_CLISER

// Create socket
void create_socket(int *sockfd);

// Set information
void set_info(struct sockaddr_in *servaddr);

// Bind the socket with the server address
void bind_socket(int *sockfd, struct sockaddr_in *servaddr);

// Chat client with server
void chat_client(int *sockfd, struct sockaddr_in *servaddr);

// Server request to client in chat
void chat_server(int *sockfd, struct sockaddr_in *servaddr, struct sockaddr_in *cliaddr);


#endif// __UDP_CLISER
