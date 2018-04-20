#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define localsocket "/tmp/main.socket"

int main(){


	int sock, con, i;
	char buff1[] = "Door open.";
	char buff2[] = "Door closed.";
	struct sockaddr_un server_addr;		
	
	memset(&server_addr, 0, sizeof(struct sockaddr_un));
	server_addr.sun_family = AF_UNIX;
	strncpy(server_addr.sun_path, localsocket, sizeof(server_addr.sun_path) - 1);			
	
	i = 1;
	while(1){		
		sock = socket(AF_UNIX, SOCK_STREAM, 0);
		printf("Socket:%d\n",sock);	

		con = connect(sock, (struct sockaddr *) &server_addr, sizeof(struct sockaddr_un));

		if(i == 1){
			write(sock, buff1, strlen(buff1));					
			sleep(5);
			i=0;
		}
		else{
			write(sock, buff2, strlen(buff2));					
			sleep(3);
			i=1;
		}		
		
		close(sock);
	}

	close(sock);
	unlink(localsocket);
		
	return 0;
}