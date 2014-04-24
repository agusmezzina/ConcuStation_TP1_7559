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
	istringstream ss(argv[1]);
	int fd;
	if (!(ss >> fd))
	    cerr << "Invalid number " << argv[1] << '\n';

	Pipe canal;
	dup2(fd, canal.getFdLectura());
	char buffer[100];
	bool salir = false;

	while(!salir){
		ssize_t bytesLeidos = canal.leer ( static_cast<void*>(buffer),100 );
		string mensaje = buffer;
		mensaje.resize ( bytesLeidos );
		cout << "JE: Leí el mensaje " << mensaje << endl;
		if(mensaje == "q")
			salir = true;
	}

	cout << "JE: Final" << endl;
	canal.cerrar();

	return 0;
}


