/*
 * main.cpp
 *
 *  Created on: 14/04/2014
 *      Author: agustin
 */

#include <unistd.h>
#include <iostream>
#include "../Common/FifoLectura.h"
using namespace std;

int main(int argc, char *argv[]) {
	static const string ARCHIVO_FIFO = "/tmp/fifo_init_jefe";
	static const int BUFFSIZE = 50;

	FifoLectura canal(ARCHIVO_FIFO);
	char buffer[BUFFSIZE];
	bool salir = false;
	canal.abrir();

	while(!salir){
		ssize_t bytesLeidos = canal.leer ( static_cast<void*>(buffer),100 );
		string mensaje = buffer;
		mensaje.resize ( bytesLeidos );
		cout << "[JefeEstación] Leí el mensaje " << mensaje << endl;
		if(mensaje == "q")
			salir = true;
	}

	cout << "[JefeEstacion] Final" << endl;
	canal.cerrar();

	return 0;
}


