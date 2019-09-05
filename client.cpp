#include <iostream>
#include <memory>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "util.h"
#include <thread>
#include <stdio.h>
#include <pthread.h>




using namespace std;

char *socket_path = "\0hidden";
int timer_finish = 0;

void *timer(void *t) {
			sleep(10);
			timer_finish = 1;
}


int main(int argc, char** argv) {
	struct sockaddr_un addr;
	string by_default = "/tmp/db.tuples.sock";
	int fd, in; 
	string cmd = "";
	char buffer[1000];
	char ruta[1000];
	
	while (cmd != "quit") {
		if (in == 1){
			cout << "Estado: Conectado al servidor\n";
		} else {
			cout << "Estado: Desconectado\n";
		}
		cout << ">";
		cin >> cmd;
		
		if( cmd == "connect"){
			cout << "Indique ruta del socket (indique con una 'd' si quiere la ruta por defecto)\n";
			cin >> ruta;
			if (ruta[0] == 'd' and ruta[1]== 0)
			{
				cout << "su ruta es: /tmp/db.tuples.sock\n" ;
				socket_path = "/tmp/db.tuples.sock";
				
			}
			else {
				cout << "su ruta es: " << ruta << "\n" ;
				socket_path = ruta;
			}
			pthread_t time;
			pthread_create(&time,NULL,&timer,(void *)1);
			if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1){
				cout << "socket error\n";
				continue;
			}
			if (timer_finish == 1)
			{
				cout << "Out of Time\n";
				timer_finish = 0;
				continue;
			}
			
			memset(&addr, 0, sizeof(addr));
			addr.sun_family = AF_UNIX; 
			if (*socket_path == '\0') { 
				*addr.sun_path = '\0'; 
				strncpy(addr.sun_path+1, socket_path+1, sizeof(addr.sun_path)-2);
			} else {
				strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path)-1);
  			}
  			
  			if (timer_finish == 1)
			{
				cout << "Out of Time\n";
				timer_finish = 0;
				continue;
			}

  			if (connect(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
    			cout << "connect error\n";
    			continue;
  			}
  			in = 1;
  			cout << "Conectado al servidor\n";
			
		}
		
		if( cmd == "disconnect"){
			close(fd);
			cout << "Usted se a desconectado del servidor\n";
			strcpy(buffer, cmd.c_str());
			send(fd, buffer, strlen(buffer), 0);
			fd = NULL;
			continue;
		}
		
		if( cmd == "list"){
			strcpy(buffer, cmd.c_str());
			send(fd, buffer, strlen(buffer), 0);
			//comando para que el client espere respuesta del servidor aqui
			
		}
		
		if( cmd.find("insert") == 0){
			strcpy(buffer, cmd.c_str());
			char insert[2][20];
			if( cmd.find(",") == 0){
				
			} else {
				
			}
		
			
			//comando para que el client espere respuesta del servidor aqui
		}
		
		if( cmd.find("get")==0) {
			//if( write(fd, ) == -1){
			//	perror("Failed get request")
			//}
			//comando para que el client espere respuesta del servidor aqui
		}
		
		if(cmd.find("peek")==0){
			//if( write(fd, ) == -1){
			//	perror("Failed peek request")
			//}
			//comando para que el client espere respuesta del servidor aqui
		}
		
		if(cmd.find("update")==0){
			//if( write(fd, ) == -1){
			//	perror("Failed update request")
			//}
			//comando para que el client espere respuesta del servidor aqui
		}
		
		if(cmd.find("delete")==0) {
			//if( write(fd, ) == -1){
			//	perror("Failed delete request")
			//}
			//comando para que el client espere respuesta del servidor aqui
		}
	}

	return 0;	
}
