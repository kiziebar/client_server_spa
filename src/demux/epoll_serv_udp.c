#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "functions.h"

#define MAX_EVENTS 100
#define MAX_BUFF 5096

//unsigned char buf[MAX_BUFF];

int non_blocking(int sockfd)
{
	int getFlag, setFlag;
	getFlag = fcntl(sockfd, F_GETFL, 0);
	if(getFlag == -1)
		printf("flag error");

	getFlag |= O_NONBLOCK;
	setFlag = fcntl(sockfd, F_GETFL, getFlag);
	return 0;
}

//Driver code
int main(){

	// Master socket, epoll file descriptor
	int sockfd, epollfd, ctlfd, numevents, buf, len;
	int val = 1;
	char buff[MAX_BUFF];
	struct sockaddr_in servaddr, cliaddr;
	// Epoll struct
	struct epoll_event ev;
	struct epoll_event events[MAX_EVENTS];
	//create_non_block_socket(&sockfd);
	sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	non_blocking(sockfd);
	if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val)) == -1)
		printf("error");
	memset(&servaddr, 0, sizeof(servaddr));
	//memset(&cliaddr, 0, sizeof(cliaddr));
	//set_info(&servaddr);
	//bind_socket(&sockfd, &servaddr);

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(8888);

	if(bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
		printf("bind error");

	// Epoll create
	//epollfd = epoll_create(6);
	epollfd = epoll_create(2);
	if(epollfd == -1)
		printf("nope");
	// Sockfd to epoll instance
	ev.data.fd = sockfd;
	ev.events = EPOLLIN |EPOLLPRI | EPOLLERR | EPOLLET;

	ctlfd = epoll_ctl(epollfd, EPOLL_CTL_ADD, sockfd, &ev);

	while(1)
	{

		numevents = epoll_wait(epollfd, events, MAX_EVENTS, 30000);
		printf("jestem");
		for(int i = 0; i < numevents; i++)
		{
			if((events[i].events & EPOLLERR) || (events[i].events & EPOLLHUP) || (!(events[i].events & EPOLLIN)))
			{
				fprintf(stderr, "epoll error\n");
				close(events[i].data.fd);
				continue;
			}
			else if ((events[i].events & EPOLLIN) && (sockfd == events[i].data.fd))
			{
				while(1)
				{
					memset(buf, 0, MAX_BUFF);
					if((len = recvfrom(sockfd, buff, MAX_BUFF, 0, NULL, NULL)) < 0)
					{
						printf("send error");
					}
					else
					{
						printf("%s", buff[1]);
					}
				}
			}
		}
	}

	close(sockfd);
	close(epollfd);
	//chat_server(&sockfd, &servaddr, &cliaddr);

	return 0;
}
