/*
 * main.cpp
 *
 *  Created on: 14/04/2014
 *      Author: agustin
 */

#include <unistd.h>
#include <sstream>
#include <iostream>
#include "../Common/Pipe.h"
using namespace std;

int main(int argc, char *argv[]) {
	cout << "Soy el jefe de estación. Mi pid es:" << getpid() << endl;
	istringstream ss(argv[1]);
	int fd;
	if (!(ss >> fd))
	    cerr << "Invalid number " << argv[1] << '\n';

	cout << fd <<endl;
	Pipe canal;
	dup2(fd, canal.getFdLectura());
	char buffer[100];

	ssize_t bytesLeidos = canal.leer ( static_cast<void*>(buffer),100 );
	std::string mensaje = buffer;
	mensaje.resize ( bytesLeidos );

	cout << "JE: Leí el mensaje " << mensaje << endl;

	canal.cerrar();

	return 0;
	return 0;
}


