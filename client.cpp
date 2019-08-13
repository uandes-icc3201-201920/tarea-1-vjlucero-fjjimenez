#include <iostream>
#include <memory>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "util.h"

using namespace std;

int main(int argc, char** argv) {
	
	string cmd = "";
	
	while (cmd != "quit") {
		cout << ">";
		cin >> cmd;
	}

	return 0;	
}