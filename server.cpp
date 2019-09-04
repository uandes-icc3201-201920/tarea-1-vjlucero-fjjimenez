#include <iostream>
#include <memory>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "util.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

// Almacenamiento KV
KVStore db;
//char *socket_path = "./socket";
char *socket_path = "\0hidden";

int main(int argc, char * argv[]) {	
	
	int sflag = 0;
	int opt;
	string s = "-s";
	/*if (argc > 1){
		cout <<argv[1];
		if ( s.compare( argv[1]) == 0){//condición de cambio de ruta
			*socket_path = *argv[2];
			cout<< "\nRuta De escucha acualizada, ahora sera: "<< *socket_path <<endl;
		}
		else{
			//ruta = /tmp/db.tuples.sock
			cout<< "\nruta invalida, se mantiene la original"<<endl;
		}	
	}*/

	

	// Procesar opciones de linea de comando
    	while ((opt = getopt (argc, argv, "s:")) != -1) {
		switch (opt){
			/* Procesar el flag s si el usuario lo ingresa */
			case 's':
				sflag = 1;
				break;
			default:
				return EXIT_FAILURE;
          		}	    	
    		}

	if (sflag == 1){
		char *socket_path = argv[2];
		cout<< "\nRuta De escucha acualizada, ahora sera: " << socket_path<<endl;
		//paso ya el flag del -s
		}
	cout<<"SSS"<<endl;
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
