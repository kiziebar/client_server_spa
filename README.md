# client_server_spa

In dir ./tcp:

	- client.c
	- server.c

In dir ./src:

	- client.c
	- server.c
	- functions.c
	- functions.h
	- demux (dir)

In ./src/demux dir:

	- epoll_client_udp.c
	- epoll_serv_udp.c
	- select_udp.c



Files in tcp dir create tcp epoll client-server.
