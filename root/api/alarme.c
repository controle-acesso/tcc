#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define alarmSocket "/tmp/alarm.socket"

typedef struct {
	char *cmd;
	char *id;
	
} message;

message decode(char *m){
	message msg;
	int i=0;
	int j=0;
	char *cmd = malloc(2*sizeof(char));
	char *id = malloc(8*sizeof(char));

	while(m[i] != '\0'){
		if(i < 2){
			cmd[i] = m[i];
		}
		else{
			id[j] = m[i];
			j++;
		}
		i++;
	}
	msg.cmd = cmd;
	msg.id = id;
	return msg;
}

int main(){

	int alarmsock,peersock,bnd,lnt;		
	struct sockaddr_un my_addr, peer_addr;
	socklen_t peer_addr_size;
	char buff[8];

	alarmsock = socket(AF_UNIX, SOCK_STREAM, 0);
	unlink(alarmSocket);

	memset(buff,'0', sizeof(buff));

	memset(&my_addr, 0, sizeof(struct sockaddr_un));
	my_addr.sun_family = AF_UNIX;
	strncpy(my_addr.sun_path, alarmSocket, sizeof(my_addr.sun_path) - 1);

	bnd = bind(alarmsock, (struct sockaddr *) &my_addr, sizeof(struct sockaddr_un));

	lnt = listen(alarmsock, 10);

	printf("Socket:%d Bind:%d Listen:%d\n",alarmsock,bnd,lnt);

	peer_addr_size = sizeof(struct sockaddr_un);

	message msg;

	while(1){		
		peersock = accept(alarmsock, (struct sockaddr *) &peer_addr, &peer_addr_size);
		read(peersock,buff,2);
		msg = decode(buff);
		switch((int)strtol(msg.cmd,NULL,16)){
			case 0x06:
				printf("Alarme ON\n");				
				break;
			case 0x07:
				printf("Alarme OFF\n");
				sleep(6);
				printf("Alarme ON\n");
				break;
			default:
				printf("Comando desconhecido\n");
				break;
		}
			
		close(peersock);	
	}

	close(alarmsock);
	unlink(alarmSocket);
		
	return 0;
}