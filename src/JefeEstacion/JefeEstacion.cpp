/*
 * JefeEstacion.cpp
 *
 *  Created on: 14/04/2014
 *      Author: agustin
 */

#include "JefeEstacion.h"

JefeEstacion::JefeEstacion() {
	canal = NULL;
}

const int JefeEstacion::BUFFSIZE;

void JefeEstacion::iniciar(){
	canal = new FifoLectura(Constantes::ARCHIVO_FIFO);
}

int JefeEstacion::run(){
	iniciar();

	canal->abrir();

	std::fstream file;
	file.open("logJefe",std::fstream::out);
	char buffer[BUFFSIZE];
	bool salir = false;

	while(!salir){
		ssize_t bytesLeidos = canal->leer ( static_cast<void*>(buffer),100 );
		std::string mensaje = buffer;
		mensaje.resize ( bytesLeidos );
		file << "[JefeEstación] Leí el mensaje " << mensaje << std::endl;
		if(mensaje == "q")
			salir = true;
	}

	file << "[JefeEstacion] Final" << std::endl;
	canal->cerrar();
	file.close();
	return 0;
}

JefeEstacion::~JefeEstacion() {
	delete(canal);
}

