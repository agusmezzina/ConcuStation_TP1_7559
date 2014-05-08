/*
 * JefeEstacion.cpp
 *
 *  Created on: 14/04/2014
 *      Author: agustin
 */

#include "JefeEstacion.h"

JefeEstacion::JefeEstacion(int cantEmpleados): cantidadEmpleados(cantEmpleados) {
	canal = NULL;
}

const int JefeEstacion::BUFFSIZE;

void JefeEstacion::iniciar(){
	canal = new FifoLectura(Constantes::ARCHIVO_FIFO);

	for(char i=0;i<cantidadEmpleados;i++){
		transferencias.push_back(new TransferenciaEmpleado(Constantes::TRANSFERENCIA,i,i));
	}
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
		else
		{
			Auto a(mensaje);
			//Procesar auto
		}
	}

	file << "[JefeEstacion] Final" << std::endl;
	canal->cerrar();
	file.close();
	return 0;
}

JefeEstacion::~JefeEstacion() {
	delete(canal);
}

