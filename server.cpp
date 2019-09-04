#include <iostream>
#include <memory>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "util.h"
#include <cstdio>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


using namespace std;

// Almacenamiento KV
KVStore db;
//char *socket_path = "./socket";
char *socket_path = "/tmp/db.tuples.sock";

int main(int argc, char * argv[]) {	
	  struct sockaddr_un addr;
  	string buf;
  	int fd,cl,rc;
	int sflag = 0;
	int opt;
	string s = "-s";


	// Procesar opciones de linea de comando
    	while ((opt = getopt (argc, argv, "s:")) != -1) {
		switch (opt){
			/* Procesar el flag s si el usuario lo ingresa */
			case 's':
				sflag = 1;
				break;
			default:
				cout << "Ruta proporcionada no especificada o incorrecta, el programa procedera a a cerrarse"<<endl;
				return EXIT_FAILURE;
          		}	    	
    		}

	if (sflag == 1){
		char *socket_path = argv[2];
		cout<< "\nRuta De escucha acualizada, ahora sera: " << socket_path<<endl;
		//paso ya el flag del -s
		}
//conexion
	if ( (fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
		cout<<"error de socket"<<endl;
		perror("socket error");
		exit(-1);
		}

	memset(&addr, 0, sizeof(addr));
	addr.sun_family = AF_UNIX;
	if (*socket_path == '\0') {
		*addr.sun_path = '\0';
		strncpy(addr.sun_path+1, socket_path+1, sizeof(addr.sun_path)-2);
	} else {
		strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path)-1);
		unlink(socket_path);
			}

	if (bind(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
		cout<<"Error de bind"<<endl;
		perror("bind error");
		exit(-1);
		}

	if (listen(fd, 5) == -1) {
		cout<<"Error de listen"<<endl;
		perror("listen error");
		exit(-1);
		}

	while (1) {
		if ( (cl = accept(fd, NULL, NULL)) == -1) {
			cout<<"Error"<<endl;
			perror("accept error");
			continue;
			}

		while ( (rc=read(cl,buf,sizeof(buf))) > 0) {
			cout<<"s"<<strcmp(buf,"quit")<<endl;
		    	if(buf == "quit"){
		    		return 0;
				}
 			printf("read %u bytes: %.*s\n", rc, rc, buf);
			}
		if (rc == -1) {
		cout<<"Error de lectura"<<endl;
      		perror("read");
      		exit(-1);
    			}
    		else if (rc == 0) {
		cout<<"cierre"<<endl;
      		printf("EOF\n");
      		close(cl);
    			}
  		}


	// Uso elemental del almacenamiento KV:
	
	// Creamos un arreglo de bytes a mano
	byte data[] = { 0x01, 0x01, 0x01, 0x01, 0x01 };

	// Luego un vector utilizando el arreglo de bytes
	vector<byte> vdata(data, data + sizeof(data));
	
	// Creamos el valor
	Value val = { 5, vdata };
	
	// Insertamos un par clave, valor directamente
	// en el mapa KV
	
	// Nota: Debiera diseñarse una solución más robusta con una interfaz
	// adecuada para acceder a la estructura.
	db.insert(std::pair<unsigned long, Value>(1000, val));
		
	// Imprimir lo que hemos agregado al mapa KV.
	cout << db[1000].size << " " << (int) db[1000].data[0] << endl;
	
	return 0;
}
