#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define alarmSocket "/tmp/alarm.socket"

int main(int argc, char *argv[]){


	int sock, con;
	
	struct sockaddr_un server_addr;		
	memset(&server_addr, 0, sizeof(struct sockaddr_un));
	server_addr.sun_family = AF_UNIX;
	strncpy(server_addr.sun_path, alarmSocket, sizeof(server_addr.sun_path) - 1);
	
	sock = socket(AF_UNIX, SOCK_STREAM, 0);

	char buff[2];
	memset(buff,0, 2);	

	if(sock < 0){
		printf("socket() failed: %s\n", strerror(errno));
		exit(1);
	}

	printf("Socket:%d\n",sock);	

	con = connect(sock, (struct sockaddr *) &server_addr, sizeof(struct sockaddr_un));

	if(con < 0){
		printf("connect() failed: %s\n", strerror(errno));
		close(sock);
		exit(1);
	}

	strcpy(buff,argv[1]);

	printf("Message to be sent: %s\n",buff);	

	write(sock,buff,strlen(buff));

	if(write < 0){
		printf("write() failed: %s\n", strerror(errno));
		close(sock);
		exit(1);
	}

	printf("Message sent successfuly.\n");

	close(sock);
		
	return 0;
}