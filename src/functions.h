#ifndef __UDP_CLISER
#define __UDP_CLISER

void create_socket(int *sockfd);

void set_info(struct sockaddr_in *servaddr);

void chat_client(int *sockfd, struct sockaddr_in *servaddr);


#endif// __UDP_CLISER
