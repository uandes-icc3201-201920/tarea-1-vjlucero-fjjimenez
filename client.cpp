#include <iostream>
#include <memory>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "util.h"
#include <thread>
#include <chrono>
#include <stdio.h>
#include <pthread.h>




using namespace std;

char *socket_path = "\0hidden";

void* timer(void* finish) {
	 //auto Start = chrono::high_resolution_clock::now();
	//		while(1)
		//	{
			//	auto End = chrono::high_resolution_clock::now();
				//chrono::duration<double, milli> Elapsed = End - Start;
				//if (Elapsed.count() >= 10000.0)
				//	break;
			//}
			//finish = 1;
			return NULL;
}


int main(int argc, char** argv) {
	struct sockaddr_un addr;
	string by_default = "/tmp/db.tuples.sock";
	int timer_finish = 0;
	int fd; 
	string cmd = "";
	char buffer[100];
	char ruta[100];
	
	while (cmd != "quit") {
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
			pthread_create(&time,NULL,&timer,(void*)&timer_finish);
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
			addr.sun_family = AF_UNIX; //serv_addr.sin_family en geeks
			if (*socket_path == '\0') { // este if podria ser el equivalente al if(inet pron...)
				*addr.sun_path = '\0'; //serv_addr.sin_port en geeks
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
  			
  			cout << "Conectado al servidor";
			
		}
		
		if( cmd == "disconnect"){
			close(fd);
			continue;
		}
		
		if( cmd == "list"){
			strcpy(buffer, cmd.c_str());
			send(fd, buffer, strlen(buffer), 0);
			//comando para que el client espere respuesta del servidor aqui
			
		}
		
		if( cmd.find("insert") == 0){
		
			if( cmd.find(",") == 0){
				string value, key;
			}
		
			//if( write(fd, ) == -1){
			//	perror("Failed insert request")
			//}
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
