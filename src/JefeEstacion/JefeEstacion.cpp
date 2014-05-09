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

bool JefeEstacion::asignarAEmpleado(const Auto& a){
	int contador = 0;
	bool encontreLibre = false;

	while((contador < cantidadEmpleados) && (!encontreLibre)){
		TransferenciaEmpleado* te = transferencias[contador];
		encontreLibre = te->ocuparSiEstaLibre(a);
		contador++;
	}
	return encontreLibre;
}

int JefeEstacion::run(){
	iniciar();

	canal->abrir();

	std::fstream file;
	file.open("logJefe",std::fstream::out);
	file << "[JEFE] Mi pid es:" << getpid() << std::endl;
	char buffer[BUFFSIZE];
	bool salir = false;
	while(!salir){
		ssize_t bytesLeidos = canal->leer ( static_cast<void*>(buffer), 3 );
		std::string mensaje = buffer;
		mensaje.resize ( bytesLeidos );
		file << "[JEFE] Leí el mensaje " << mensaje << std::endl;
		if(mensaje == "q")
			salir = true;
		else
		{
			Auto a(mensaje);
			//sleep(5);
			bool libre = asignarAEmpleado(a);
			if(!libre)
				file << "[JEFE] Descarté " << mensaje << std::endl;
		}
	}

	file << "[JEFE] Final" << std::endl;
	canal->cerrar();
	file.close();
	return 0;
}

JefeEstacion::~JefeEstacion() {
	delete(canal);
}

