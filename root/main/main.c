#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define localsocket "/tmp/main.socket"

int main(){


	int sock,peersock,bnd,lnt,child;
	char buff[100];
	struct sockaddr_un my_addr, peer_addr;
	socklen_t peer_addr_size;

	sock = socket(AF_UNIX, SOCK_STREAM, 0);
	unlink(localsocket);

	memset(buff,'0', sizeof(buff));

	memset(&my_addr, 0, sizeof(struct sockaddr_un));
	my_addr.sun_family = AF_UNIX;
	strncpy(my_addr.sun_path, localsocket, sizeof(my_addr.sun_path) - 1);
	bnd = bind(sock, (struct sockaddr *) &my_addr, sizeof(struct sockaddr_un));

	lnt = listen(sock, 10);

	printf("Socket:%d Bind:%d Listen:%d\n",sock,bnd,lnt);

	peer_addr_size = sizeof(struct sockaddr_un);
	while(1){		
		peersock = accept(sock, (struct sockaddr *) &peer_addr, &peer_addr_size);
		child = fork();		
		switch(child){
			case -1:
				printf("Child not created.\n");
				exit(0);
				break;				
			case 0:
				close(sock);
				printf("Child created!\n");
				read(peersock,buff,100);
				printf("%s\n",buff);
				exit(0);
				break;
			default:
				printf("Child PID:%d -- Parent FD to peersock:%d \n",child,peersock);
				close(peersock);
				break;
		}
	}

	close(sock);
	unlink(localsocket);
	
	return 0;
}
