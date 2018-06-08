#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define ProgramManagerSocket "/tmp/programManager.socket"
#define alarmSocket "/tmp/alarm.socket"

int main(){

	int sock, peersock, bnd, lnt;			
	struct sockaddr_un my_addr, peer_addr;
	socklen_t peer_addr_size;	
	unlink(alarmSocket);
	memset(&my_addr, 0, sizeof(struct sockaddr_un));
	my_addr.sun_family = AF_UNIX;
	strncpy(my_addr.sun_path, alarmSocket, sizeof(my_addr.sun_path) - 1);

	char buff[2];
	char cmd[3];
	memset(buff,0,strlen(buff));

	int alarm_flag = 0;

	sock = socket(AF_UNIX, SOCK_STREAM, 0);

	if(sock < 0){
		printf("socket() failed: %s\n", strerror(errno));
		exit(1);
	}

	printf("Socket:%d\n",sock);	

	bnd = bind(sock, (struct sockaddr *) &my_addr, sizeof(struct sockaddr_un));

	if(bnd < 0){
		printf("bind() failed: %s\n", strerror(errno));
		exit(1);
	}

	lnt = listen(sock, 10);

	if(lnt < 0){
		printf("listen() failed: %s\n", strerror(errno));
		exit(1);
	}	
	
	peer_addr_size = sizeof(struct sockaddr_un);

	while(1){

		peersock = accept(sock, (struct sockaddr *) &peer_addr, &peer_addr_size);

		if(peersock < 0){
			printf("accept() failed: %s\n", strerror(errno));
			exit(1);
		}

		read(peersock,buff, 2*sizeof(char));
		printf("=============================================================\n");
		printf("=============================================================\n");
		printf("Message recieved: %s.\n", buff);

		cmd[0] = buff[0];
		cmd[1] = buff[1];
		cmd[2] = '\0';

		printf("Command is: %s. \n", cmd);		

		if((int)strtol(cmd,NULL,16) == 0x0B){
			alarm_flag = 0;		
			
		}

		printf("Status do alarme: %d.\n", alarm_flag);

		if((int)strtol(cmd,NULL,16) == 0x07){
			printf("Alarme desligado.\n");
			sleep(5);
			printf("Alarme ligado.\n");
		}		

		close(peersock);
	}

	unlink(alarmSocket);
	close(sock);
		
	return 0;
}