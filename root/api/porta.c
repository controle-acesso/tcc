#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define localsocket "/tmp/main.socket"

int main(){


	int sock, con;
	char buff[] = "Hello from client.";
	struct sockaddr_un server_addr;	
	
	printf("Socket:%d\n",sock);

	memset(&server_addr, 0, sizeof(struct sockaddr_un));
	server_addr.sun_family = AF_UNIX;
	strncpy(server_addr.sun_path, localsocket, sizeof(server_addr.sun_path) - 1);		
	while(1){
		sock = socket(AF_UNIX, SOCK_STREAM, 0);
		con = connect(sock, (struct sockaddr *) &server_addr, sizeof(struct sockaddr_un));
		write(sock, buff, strlen(buff));
		close(sock);
		sleep(3);
	}
	remove(localsocket);
	close(sock);	
	return 0;
}