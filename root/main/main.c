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
#define lockSocket "/tmp/lock.socket"
#define databaseSocket "/tmp/dataBase.socket"

int main(){	

	int pmsock, peersock, bnd, lnt, alarmsock, locksock, databasesock, con;			
	struct sockaddr_un my_addr, peer_addr, alarm_addr, lock_addr, database_addr;
	socklen_t peer_addr_size;
	memset(&alarm_addr, 0, sizeof(struct sockaddr_un));
	memset(&lock_addr, 0, sizeof(struct sockaddr_un));
	memset(&database_addr, 0, sizeof(struct sockaddr_un));
	memset(&my_addr, 0, sizeof(struct sockaddr_un));
	alarm_addr.sun_family = AF_UNIX;
	lock_addr.sun_family = AF_UNIX;
	database_addr.sun_family = AF_UNIX;
	my_addr.sun_family = AF_UNIX;
	strncpy(alarm_addr.sun_path, alarmSocket, sizeof(alarm_addr.sun_path) - 1);	
	strncpy(lock_addr.sun_path, lockSocket, sizeof(lock_addr.sun_path) - 1);
	strncpy(database_addr.sun_path, databaseSocket, sizeof(database_addr.sun_path) - 1);	
	strncpy(my_addr.sun_path, ProgramManagerSocket, sizeof(my_addr.sun_path) - 1);		
	
	unlink(ProgramManagerSocket);

	char buff[11];
	char cmd[3];
	int alarm_flag = 0;
	memset(buff,0, 11);
	memset(cmd, 0, 11);
	
	pmsock = socket(AF_UNIX, SOCK_STREAM, 0);

	if(pmsock < 0){
		printf("socket() failed: %s\n", strerror(errno));
		exit(1);
	}	

	bnd = bind(pmsock, (struct sockaddr *) &my_addr, sizeof(struct sockaddr_un));

	if(bnd < 0){
		printf("bind() failed: %s\n", strerror(errno));
		exit(1);
	}

	lnt = listen(pmsock, 10);

	if(lnt < 0){
		printf("listen() failed: %s\n", strerror(errno));
		exit(1);
	}	

	printf("Program Manager: Socket:%d .\n",pmsock);
	
	peer_addr_size = sizeof(struct sockaddr_un);

	while(1){

		peersock = accept(pmsock, (struct sockaddr *) &peer_addr, &peer_addr_size);				
		read(peersock,buff,10);
		printf("=============================================================\n");
		printf("=============================================================\n");		
		printf("Message recieved: %s.\n",buff);

		cmd[0] = buff[0];
		cmd[1] = buff[1];
		cmd[2] = '\0';

		printf("Command is: %s.\n",cmd);

		switch((int)strtol(cmd,NULL,16)){

			case 0x00: // Do nothing
								
				break;

			case 0x01: // Probrably it will be changed to another cmd code.
								
				break;
			
			case 0x02: // Request validation from keyboard

				printf("=============================================================\n");
				databasesock = socket(AF_UNIX, SOCK_STREAM, 0);

				if(databasesock < 0){
					printf("socket() failed: %s\n", strerror(errno));
					exit(1);
				}

				printf("Socket:%d\n",databasesock);	

				con = connect(databasesock, (struct sockaddr *) &database_addr, sizeof(struct sockaddr_un));

				if(con < 0){
					printf("connect() failed: %s\n", strerror(errno));
					close(databasesock);
					exit(1);
				}				

				printf("Message to be sent: %s\n",buff);	

				write(databasesock,buff,strlen(buff));

				if(write < 0){
					printf("write() failed: %s\n", strerror(errno));
					close(databasesock);
					exit(1);
				}

				printf("Message sent successfuly.\n");

				close(databasesock);
				
				break;

			case 0x03: // Request validation from RFID

				printf("=============================================================\n");
				databasesock = socket(AF_UNIX, SOCK_STREAM, 0);

				if(databasesock < 0){
					printf("socket() failed: %s\n", strerror(errno));
					exit(1);
				}

				printf("Socket:%d\n",databasesock);	

				con = connect(databasesock, (struct sockaddr *) &database_addr, sizeof(struct sockaddr_un));

				if(con < 0){
					printf("connect() failed: %s\n", strerror(errno));
					close(databasesock);
					exit(1);
				}				

				printf("Message to be sent: %s\n",buff);	

				write(databasesock,buff,strlen(buff));

				if(write < 0){
					printf("write() failed: %s\n", strerror(errno));
					close(databasesock);
					exit(1);
				}

				printf("Message sent successfuly.\n");

				close(databasesock);
								
				break;

			case 0x04: // Access granted

				printf("=============================================================\n");
				alarmsock = socket(AF_UNIX, SOCK_STREAM, 0);

				if(alarmsock < 0){
					printf("socket() failed: %s\n", strerror(errno));
					exit(1);
				}

				printf("Socket:%d\n",alarmsock);	

				con = connect(alarmsock, (struct sockaddr *) &alarm_addr, sizeof(struct sockaddr_un));

				if(con < 0){
					printf("connect() failed: %s\n", strerror(errno));
					close(alarmsock);
					exit(1);
				}				

				printf("Message to be sent: 0B\n");	

				write(alarmsock,"0B", 2);

				if(write < 0){
					printf("write() failed: %s\n", strerror(errno));
					close(alarmsock);
					exit(1);
				}

				printf("Message sent successfuly.\n");

				close(alarmsock);

				printf("=============================================================\n");
				alarmsock = socket(AF_UNIX, SOCK_STREAM, 0);

				if(alarmsock < 0){
					printf("socket() failed: %s\n", strerror(errno));
					exit(1);
				}

				printf("Socket:%d\n",alarmsock);	

				con = connect(alarmsock, (struct sockaddr *) &alarm_addr, sizeof(struct sockaddr_un));

				if(con < 0){
					printf("connect() failed: %s\n", strerror(errno));
					close(alarmsock);
					exit(1);
				}				

				printf("Message to be sent: 07\n");	

				write(alarmsock,"07", 2);

				if(write < 0){
					printf("write() failed: %s\n", strerror(errno));
					close(alarmsock);
					exit(1);
				}

				printf("Message sent successfuly.\n");

				close(alarmsock);

				alarm_flag = 0;

				printf("=============================================================\n");
				locksock = socket(AF_UNIX, SOCK_STREAM, 0);

				if(locksock < 0){
					printf("socket() failed: %s\n", strerror(errno));
					exit(1);
				}

				printf("Socket:%d\n",locksock);	

				con = connect(locksock, (struct sockaddr *) &lock_addr, sizeof(struct sockaddr_un));

				if(con < 0){
					printf("connect() failed: %s\n", strerror(errno));
					close(locksock);
					exit(1);
				}				

				printf("Message to be sent: 01\n");	

				write(locksock,"01", 2);

				if(write < 0){
					printf("write() failed: %s\n", strerror(errno));
					close(locksock);
					exit(1);
				}

				printf("Message sent successfuly.\n");

				close(locksock);



								
				break;

			case 0x05: // Access denied
								
				break;

			case 0x0A: // Unauthorized access

				alarm_flag = 1;
				printf("Unauthorized access!! alarm_flag status : %d.\n", alarm_flag);
								
				break;

			case 0x0C: // Open door from inside

				printf("=============================================================\n");
				alarmsock = socket(AF_UNIX, SOCK_STREAM, 0);

				if(alarmsock < 0){
					printf("socket() failed: %s\n", strerror(errno));
					exit(1);
				}

				printf("Socket:%d\n",alarmsock);	

				con = connect(alarmsock, (struct sockaddr *) &alarm_addr, sizeof(struct sockaddr_un));

				if(con < 0){
					printf("connect() failed: %s\n", strerror(errno));
					close(alarmsock);
					exit(1);
				}				

				printf("Message to be sent: 07\n");	

				write(alarmsock,"07", 2);

				if(write < 0){
					printf("write() failed: %s\n", strerror(errno));
					close(alarmsock);
					exit(1);
				}

				printf("Message sent successfuly.\n");

				close(alarmsock);

				printf("=============================================================\n");
				locksock = socket(AF_UNIX, SOCK_STREAM, 0);

				if(locksock < 0){
					printf("socket() failed: %s\n", strerror(errno));
					exit(1);
				}

				printf("Socket:%d\n",locksock);	

				con = connect(locksock, (struct sockaddr *) &lock_addr, sizeof(struct sockaddr_un));

				if(con < 0){
					printf("connect() failed: %s\n", strerror(errno));
					close(locksock);
					exit(1);
				}				

				printf("Message to be sent: 01\n");	

				write(locksock,"01", 2);

				if(write < 0){
					printf("write() failed: %s\n", strerror(errno));
					close(locksock);
					exit(1);
				}

				printf("Message sent successfuly.\n");

				close(locksock);
								
				break;
	
			default: // Do nothing
				printf("=============================================================\n");
				printf("Unknown command.\n");
				break;
		}
		
		cmd[0] = '0';
		cmd[1] = '0';
		cmd[2] = '\0';

		memset(buff,0,14*sizeof(char));
		
		close(peersock);
		
	}

	close(pmsock);
	unlink(ProgramManagerSocket);
	
	return 0;
}
