#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <mysql/mysql.h>
#include <errno.h>
#include <signal.h>

#define ProgramManagerSocket "/tmp/programManager.socket"
#define databaseSocket "/tmp/dataBase.socket"

void terminate(int sig){
	unlink(databaseSocket);
	printf("Programa finalizado.\n");
	exit(1);
}

int main(){

	int sock, peersock, bnd, lnt;			
	struct sockaddr_un my_addr, peer_addr;
	socklen_t peer_addr_size;	
	unlink(databaseSocket);
	memset(&my_addr, 0, sizeof(struct sockaddr_un));
	my_addr.sun_family = AF_UNIX;
	strncpy(my_addr.sun_path, databaseSocket, sizeof(my_addr.sun_path) - 1);
	
	int pmsock, pmcon;	
	struct sockaddr_un server_addr;		
	memset(&server_addr, 0, sizeof(struct sockaddr_un));
	server_addr.sun_family = AF_UNIX;
	strncpy(server_addr.sun_path, ProgramManagerSocket, sizeof(server_addr.sun_path) - 1);

	char buff[10];
	char cmd[3];
	char data[9];
	memset(buff,'0',10);

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

	signal(SIGINT, terminate);

	while(1){

		peersock = accept(sock, (struct sockaddr *) &peer_addr, &peer_addr_size);

		if(peersock < 0){
			printf("accept() failed: %s\n", strerror(errno));
			exit(1);
		}

		read(peersock,buff, 10);
		printf("=============================================================\n");
		printf("=============================================================\n");
		printf("Message recieved: %s.\n", buff);

		cmd[0] = buff[0];
		cmd[1] = buff[1];
		cmd[2] = '\0';
		data[0] = buff[2];
		data[1] = buff[3];
		data[2] = buff[4];
		data[3] = buff[5];
		data[4] = buff[6];
		data[5] = buff[7];
		data[6] = buff[8];
		data[7] = buff[9];
		data[8] = '\0';

		printf("Command is: %s.\n", cmd);
		printf("Data is: %s.\n", data);

		MYSQL mysql;	
		MYSQL_RES *resp;
		char query[48];
		memset(&query,'\0',48);	

		mysql_init(&mysql);
		if(mysql_real_connect(&mysql,"localhost","tcc","tcc","tccDB",0,NULL,0) < 0){
			printf("mysql_real_connect() failed: %s\n", strerror(errno));
		}
		printf("=============================================================\n");
		printf("Mysql connected\n");
		

		if((int)strtol(cmd,NULL,16) == 0x02){
			strcat(query,"select * from user where password='");
			strcat(query,data);
			strcat(query,"';");
			printf("%s\n",query);
			if(mysql_query(&mysql,query) == 0){
				printf("Query sent\n");
				resp = mysql_store_result(&mysql);
				if(resp){					
					if(mysql_fetch_row(resp) > 0){

						printf("Data found\n");
						mysql_close(&mysql);

						pmsock = socket(AF_UNIX, SOCK_STREAM, 0);
						if(sock < 0){
							printf("socket() failed: %s\n", strerror(errno));
							exit(1);
						}

						printf("Socket:%d\n",pmsock);	

						pmcon = connect(pmsock, (struct sockaddr *) &server_addr, sizeof(struct sockaddr_un));

						if(pmcon < 0){
							printf("connect() failed: %s\n", strerror(errno));
							close(pmsock);
							exit(1);
						}

						printf("Message to be sent: 04\n");	

						write(pmsock,"04",2);

						if(write < 0){
							printf("write() failed: %s\n", strerror(errno));
							close(pmsock);
							exit(1);
						}

						printf("Message sent successfuly.\n");

						close(pmsock);						
						
					}
					else{

						printf("Data not found\n");					
						mysql_close(&mysql);

						pmsock = socket(AF_UNIX, SOCK_STREAM, 0);
						if(pmsock < 0){
							printf("socket() failed: %s\n", strerror(errno));
							exit(1);
						}

						printf("Socket:%d\n",pmsock);	

						pmcon = connect(pmsock, (struct sockaddr *) &server_addr, sizeof(struct sockaddr_un));

						if(pmcon < 0){
							printf("connect() failed: %s\n", strerror(errno));
							close(pmsock);
							exit(1);
						}

						printf("Message to be sent: 05\n");	

						write(pmsock,"05",2);

						if(write < 0){
							printf("write() failed: %s\n", strerror(errno));
							close(pmsock);
							exit(1);
						}

						printf("Message sent successfuly.\n");

						close(pmsock);
						
					} 		
				}
			}
			mysql_close(&mysql);				
			
		}

		if((int)strtol(cmd,NULL,16) == 0x03){
			strcat(query,"select * from user_tag where tag_id='");
			strcat(query,data);
			strcat(query,"';");
			printf("%s\n",query);
			if(mysql_query(&mysql,query) == 0){
				printf("Query sent\n");
				resp = mysql_store_result(&mysql);
				if(resp){					
					if(mysql_fetch_row(resp) > 0){

						printf("Data found\n");
						mysql_close(&mysql);

						pmsock = socket(AF_UNIX, SOCK_STREAM, 0);
						if(pmsock < 0){
							printf("socket() failed: %s\n", strerror(errno));
							exit(1);
						}

						printf("Socket:%d\n",pmsock);	

						pmcon = connect(pmsock, (struct sockaddr *) &server_addr, sizeof(struct sockaddr_un));

						if(pmcon < 0){
							printf("connect() failed: %s\n", strerror(errno));
							close(pmsock);
							exit(1);
						}

						printf("Message to be sent: 04\n");	

						write(pmsock,"04",2);

						if(write < 0){
							printf("write() failed: %s\n", strerror(errno));
							close(pmsock);
							exit(1);
						}

						printf("Message sent successfuly.\n");

						close(pmsock);
						
					}
					else{

						printf("Data not found\n");					
						mysql_close(&mysql);

						pmsock = socket(AF_UNIX, SOCK_STREAM, 0);
						if(pmsock < 0){
							printf("socket() failed: %s\n", strerror(errno));
							exit(1);
						}

						printf("Socket:%d\n",sock);	

						pmcon = connect(pmsock, (struct sockaddr *) &server_addr, sizeof(struct sockaddr_un));

						if(pmcon < 0){
							printf("connect() failed: %s\n", strerror(errno));
							close(pmsock);
							exit(1);
						}

						printf("Message to be sent: 05\n");	

						write(pmsock,"05",2);

						if(write < 0){
							printf("write() failed: %s\n", strerror(errno));
							close(pmsock);
							exit(1);
						}

						printf("Message sent successfuly.\n");

						close(pmsock);
						
					} 		
				}
			}
			mysql_close(&mysql);
		}

		close(peersock);
	}

	unlink(databaseSocket);
	close(sock);
		
	return 0;
}
