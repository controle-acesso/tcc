#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <mysql/mysql.h>

#define ProgramManagerSocket "/tmp/programManager.socket"
#define alarmSocket "/tmp/alarm.socket"
#define lockSocket "/tmp/lock.socket"

typedef struct {
	char *cmd;
	char *id;
	
} message;

message decode(char *m){
	message msg;
	int i=0;
	int j=0;
	char *cmd = malloc(2*sizeof(char));
	char *id = malloc(11*sizeof(char));
	memset(cmd,0,2*sizeof(char));
	memset(id,0,11*sizeof(char));

	while(m[i] != NULL){
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

int searchDBKeyboard(char *m){
	MYSQL mysql;	
	MYSQL_RES *resp;		
	char query[48];	
	mysql_init(&mysql);
	if(mysql_real_connect(&mysql,"localhost","tcc","tcc","tccDB",0,NULL,0)){
		printf("Connected\n");
		memset(&query,0,sizeof(query));
		strcat(query,"select * from user where login='");
		printf("%s\n",query);
		strcat(query,m);
		strcat(query,"';");
		printf("%s\n",query);
		if(mysql_query(&mysql,query) == 0){
			printf("Query sent\n");
			resp = mysql_store_result(&mysql);
			if(resp){
				printf("Result stored\n");	
				if(mysql_fetch_row(resp) > 0){
					printf("Data found\n");
					mysql_close(&mysql);
					return 1;
				}
				else{
					printf("Data not found\n");					
					mysql_close(&mysql);
					return -1;
				} 		
			}

		}
	}	
	mysql_close(&mysql);
}

int searchDBRFID(char *m){
	MYSQL mysql;	
	MYSQL_RES *resp;		
	char query[47];	
	mysql_init(&mysql);
	if(mysql_real_connect(&mysql,"localhost","tcc","tcc","tccDB",0,NULL,0)){
		printf("Connected\n");
		memset(&query,0,sizeof(query));
		strcat(query,"select * from user_tag where tag_id='");
		printf("%s\n",query);
		strcat(query,m);
		strcat(query,"';");
		printf("%s\n",query);
		if(mysql_query(&mysql,query) == 0){
			printf("Query sent\n");
			resp = mysql_store_result(&mysql);
			if(resp){
				printf("Result stored\n");	
				if(mysql_fetch_row(resp) > 0){
					printf("Data found\n");
					mysql_close(&mysql);
					return 1;
				}
				else{
					printf("Data not found\n");					
					mysql_close(&mysql);
					return -1;
				} 		
			}

		}
	}	
	mysql_close(&mysql);
}


int main(){	

	int pmsock, peersock, bnd, lnt, alarmsock, locksock;
	char buff[14];		
	struct sockaddr_un my_addr, peer_addr, alarm_addr, lock_addr;
	socklen_t peer_addr_size;

	memset(&alarm_addr, 0, sizeof(struct sockaddr_un));
	alarm_addr.sun_family = AF_UNIX;
	strncpy(alarm_addr.sun_path, alarmSocket, sizeof(alarm_addr.sun_path) - 1);
	memset(&lock_addr, 0, sizeof(struct sockaddr_un));
	lock_addr.sun_family = AF_UNIX;
	strncpy(lock_addr.sun_path, lockSocket, sizeof(lock_addr.sun_path) - 1);		
			
	
	pmsock = socket(AF_UNIX, SOCK_STREAM, 0);
	unlink(ProgramManagerSocket);

	memset(buff,0, 14*sizeof(char));
	puts(buff);

	memset(&my_addr, 0, sizeof(struct sockaddr_un));
	my_addr.sun_family = AF_UNIX;
	strncpy(my_addr.sun_path, ProgramManagerSocket, sizeof(my_addr.sun_path) - 1);

	bnd = bind(pmsock, (struct sockaddr *) &my_addr, sizeof(struct sockaddr_un));

	lnt = listen(pmsock, 10);

	printf("Program Manager: Socket:%d Bind:%d Listen:%d Local:%s\n",pmsock,bnd,lnt,ProgramManagerSocket);
	
	peer_addr_size = sizeof(struct sockaddr_un);

	message msg;

	while(1){		
		peersock = accept(pmsock, (struct sockaddr *) &peer_addr, &peer_addr_size);		
		read(peersock,buff,13);
		puts(buff);		
		msg = decode(buff);		
		switch((int)strtol(msg.cmd,NULL,16)){			
			case 0x02:
				if(searchDBKeyboard(msg.id) > 0){
					printf("From keyboad: User found with password %s!\n", msg.id);
					alarmsock = socket(AF_UNIX, SOCK_STREAM, 0);
					while(connect(alarmsock, (struct sockaddr *) &alarm_addr, sizeof(struct sockaddr_un)) < 0){
						sleep(1);
					}						
					write(alarmsock, "07\0", 3);
					close(alarmsock);
					locksock = socket(AF_UNIX, SOCK_STREAM, 0);
					while(connect(locksock, (struct sockaddr *) &lock_addr, sizeof(struct sockaddr_un)) < 0){
						sleep(1);
					}						
					write(locksock, "01\0", 3);
					close(locksock);

				}
				break;
			case 0x03:
				if(searchDBRFID(msg.id) > 0){
					printf("From RFID: User found with password %s!\n", msg.id);
					alarmsock = socket(AF_UNIX, SOCK_STREAM, 0);
					while(connect(alarmsock, (struct sockaddr *) &alarm_addr, sizeof(struct sockaddr_un)) < 0){
						sleep(1);
					}						
					write(alarmsock, "07\0", 3);
					close(alarmsock);
					locksock = socket(AF_UNIX, SOCK_STREAM, 0);
					while(connect(locksock, (struct sockaddr *) &lock_addr, sizeof(struct sockaddr_un)) < 0){
						sleep(1);
					}						
					write(locksock, "01\0", 3);
					close(locksock);
				}				
				break;
			default:
				printf("Comando desconhecido\n");
				break;
		}
		//memset(buff,0,13*sizeof(char));
		//printf("%s\n",buf);
		puts(msg.id);
		memset(buff,0,14*sizeof(char));
		//memset(msg.id,0,11*sizeof(char));
		free(msg.id);
		free(msg.cmd);
		//puts(msg.id);
		close(peersock);
		
	}

	close(pmsock);
	unlink(ProgramManagerSocket);
	
	return 0;
}
