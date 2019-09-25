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
#include <iostream>


using namespace std;

// Almacenamiento KV
KVStore db;
int id_num = 1000;

char** processCommand (char* command) { // insert(1023, 1213004) 
	char aux_cmd[100];
	strcpy(aux_cmd, command);
	char** command_args = (char **) malloc((sizeof(char * ) * 3));
	int j = 0;
	for (j = 0; j<3 ; j++){
		command_args[j] = (char *) malloc(sizeof(char) * 30);
	}
	char delimiter = '(';
	char delimiter2 = ',';
	char delimiter3 = ')';
	int num_args = 0;
	//char * start_of_arg;
	int i = 0;
	int sub_arg_char_num = 0;
	//cout << "in method"  << endl;
	//cout << aux_cmd << endl;
	for (i = 0; num_args < 3; i++){
		//cout << aux_cmd[i] << endl;
		
		if(aux_cmd[i] == ',' || aux_cmd[i] == '('){
			command_args[num_args][sub_arg_char_num + 1] = '\0';
			// cout << command_args[num_args] << endl;
			num_args++;
			sub_arg_char_num = 0;
			i++;
		}
		else if (aux_cmd[i] == ')'){
			command_args[num_args][sub_arg_char_num] = '\0';
			break;
		}
		command_args[num_args][sub_arg_char_num] = aux_cmd[i];
		sub_arg_char_num++;
		// cout << command_args[num_args][sub_arg_char_num] << endl;
	}
	cout << command_args[0] << " " << command_args[1] << " "  << command_args[2] << " " << endl;
	return command_args;
}

int nextKey()
{
	if((int) db[id_num].data.empty())
	{
		return id_num;
	}
	else
	{
		id_num++;
		return nextKey();
	}
}

int insertDB(char* key, char* value) {
	int x = atoi(value);
	char bytes[sizeof x];
	std::copy(static_cast<const char*>(static_cast<const void*>(&x)),
	          static_cast<const char*>(static_cast<const void*>(&x)) + sizeof x,
	          bytes);
	vector<byte> vdata(bytes, bytes + sizeof(bytes));
	Value val2 = {sizeof atoi(value), vdata};
	db.insert(std::pair<unsigned long, Value>(atoi(key), val2));
	cout << (int) db[atoi(key)].data[0] << endl;

	return atoi(key);
}

int insertDBNoKey(char* value) {
	int x = atoi(value);
	char bytes[sizeof x];
	std::copy(static_cast<const char*>(static_cast<const void*>(&x)),
	          static_cast<const char*>(static_cast<const void*>(&x)) + sizeof x,
	          bytes);
	vector<byte> vdata(bytes, bytes + sizeof(bytes));
	Value val2 = {sizeof atoi(value), vdata};
	int key = nextKey();
	cout << key << endl;
	db.insert(std::pair<unsigned long, Value>(key, val2));

	return key;
}

int getDB(char* key) {
	if(db.count(atoi(key)) != 0)
	{
		int value = (int) db[atoi(key)].data[0];
		cout << value << endl;
		return value;
	}
	else
	{
		return NULL;
	}
}

bool peekDB(char* key) {
	if(db.count(atoi(key)) != 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int updateDB(char* key, char* value) {
	int x = atoi(value);
	char bytes[sizeof x];
	std::copy(static_cast<const char*>(static_cast<const void*>(&x)),
	          static_cast<const char*>(static_cast<const void*>(&x)) + sizeof x,
	          bytes);
	vector<byte> vdata(bytes, bytes + sizeof(bytes));
	Value val2 = {sizeof atoi(value), vdata};
	db[atoi(key)] = (atoi(key), val2);
	cout << (int) db[atoi(key)].data[0] << endl;

	return (int) db[atoi(key)].data[0];
}
//char *socket_path = "./socket";
char *socket_path = "/tmp/db.tuples.sock";

int main(int argc, char * argv[]) {	
	struct sockaddr_un addr;
  	char buf[1024];
  	int fd,cl,rc;
	int sflag = 0;
	int opt;
	string s = "-s";
	string cmd = "";


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
	/*// Uso elemental del almacenamiento KV:
      
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
	cout << db[1000].size << " " << (int) db[1000].data[0] << endl;*/
	if (bind(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
		perror("bind error");
		exit(-1);
		}

	if (listen(fd, 5) == -1) {
		perror("listen error");
		exit(-1);
		}

	while (1) {
		if ( (cl = accept(fd, NULL, NULL)) == -1) {
			perror("accept error");
			continue;
			}
		bzero(buf, sizeof(buf));
		while ( (rc=read(cl,buf,sizeof(buf))) > 0) {
			
			cout << buf<<" tamano es : " << strlen(buf)<<endl;
			char** parse_cmd = processCommand(buf); //parse_cmd[0] = insert, parse_cmd[1] = key ,
	    		
			char* response = "";
			if(strcmp(parse_cmd[0], "insert") == 0)
			{
				if(atoi(parse_cmd[2]) != NULL)
				{
						insertDB(parse_cmd[1], parse_cmd[2]);
				}
				else
				{
						insertDBNoKey(parse_cmd[1]);
				}
			}

			else if(strcmp(parse_cmd[0], "get") == 0)
			{
				if(int value = getDB(parse_cmd[1]))
				{
					auto char_s = std::to_string(value);
					char *char_value = &char_s[0];
					response = char_value;
				}
				else
				{
					char* sending = ".";
					response = sending;
				}
			}

			else if(strcmp(parse_cmd[0], "disconnect") == 0)
			{
				response = "Disconnecting";
				shutdown(fd, 1);
			}

			else if(strcmp(parse_cmd[0], "peek") == 0)
			{
				char* peek = "false";
				if(peekDB(parse_cmd[1]))
				{
					peek = "true";
				}
				response = peek;
				cout << peek << endl;
			}

			else if(strcmp(parse_cmd[0], "update") == 0)
			{
				updateDB(parse_cmd[1], parse_cmd[2]);
			}

			else if(strcmp(parse_cmd[0], "delete") == 0)
			{
				db.erase(atoi(parse_cmd[1]));
				response = "Deleted.";
			}
		send(fd, response, strlen(response), 0);
	   	bzero(buf, sizeof(buf));
		bzero(parse_cmd,sizeof(parse_cmd));
		}
		//buf[0]='\0';	
		if (rc == -1) {
	      		perror("read");
	      		exit(-1);
    		}
    		else if (rc == 0) {
	      		printf("Se ha terminado conexion con el cliente\n");
	      		close(cl);
    		}
	}

	return 0;
}
