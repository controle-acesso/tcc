#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define ProgramManagerSocket "/tmp/programManager.socket"

int main(){


	int sock, con, i;
	char buff[] = "03AAFF0\0";
	struct sockaddr_un server_addr;		
	
	memset(&server_addr, 0, sizeof(struct sockaddr_un));
	server_addr.sun_family = AF_UNIX;
	strncpy(server_addr.sun_path, ProgramManagerSocket, sizeof(server_addr.sun_path) - 1);			
			
	sock = socket(AF_UNIX, SOCK_STREAM, 0);

	printf("Socket:%d\n",sock);	

	con = connect(sock, (struct sockaddr *) &server_addr, sizeof(struct sockaddr_un));

	write(sock, buff, strlen(buff));					

	close(sock);
		
	return 0;
}