#include <iostream>
#include <memory>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "util.h"
#include <thread>
#include <chrono>


using namespace std;

char *socket_path = "\0hidden";

void timer(int finish) {
	 auto Start = chrono::high_resolution_clock::now();
			while(1)
			{
				auto End = chrono::high_resolution_clock::now();
				chrono::duration<double, milli> Elapsed = End - Start;
				if (Elapsed.count() >= 10000.0)
					break;
			}
			finish = 1;
}


int main(int argc, char** argv) {
	int timer_finish = 0;
	int connected = 0;
	int fd, rc; 
	string cmd = "";
	
	while (cmd != "quit") {
		cout << ">";
		cin >> cmd;
		
		if( cmd == "connect"){
			cout << "Indique ruta del socket";
			cout << ">";
			cin >> socket_path;
			if (socket_path == NULL)
			{
				socket_path = "/tmp/db.tuples.sock";
			}
			pthread_t timer;
			Pthread_create(&timer, NULL, conection, timer_finish);
			if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1){
				perror("socket error");
				continue;
			}
			if (timer_finish == 1)
			{
				perror("Out of Time");
				timer_finish = 0;
				continue;
			}
			
			memset(&addr, 0, sizeof(addr));
			addr.sun_family = AF_UNIX; //serv_addr.sin_family en geeks
			if (*socket_path == '\0') { // este if podria ser el equivalente al if(inet pron...)
				*addr.sun_path = '\0'; //serv_addr.sin_port en geeks
				strncpy(addr.sun_path+1. socket_path+1, sizeof(addr.sun_path)-2);
			} else {
				strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path)-1);
  			}
  			
  			if (timer_finish == 1)
			{
				perror("Out of Time");
				timer_finish = 0;
				continue;
			}

  			if (connect(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
    			perror("connect error");
    			continue;
  			}
  			
  			cout << "Conectado al servidor";
			
		}
		
		if( cmd == "disconnect"){
			
		}
		
		if( cmd == "quit"){
			exit(-1);
		}
		
		if( cmd == "list"){
			
		}
		
		if( cmd.find("insert") == 0){
			
		}
		
		if( cmd.find("get")==0) {
			
		}
		
		if(cmd.find("peek")==0){
			
		}
		
		if(cmd.find("update")==0){
			
		}
		
		if(cmd.find("delete")==0) {
			
		}
	}

	return 0;	
}
