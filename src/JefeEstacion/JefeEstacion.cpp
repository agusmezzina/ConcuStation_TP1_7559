/*
 * JefeEstacion.cpp
 *
 *  Created on: 14/04/2014
 *      Author: agustin
 */

#include "JefeEstacion.h"
#include <sstream>

JefeEstacion::JefeEstacion(int cantEmpleados): cantidadEmpleados(cantEmpleados),
        log(Constantes::LOG){
	canal = NULL;
	log.setProceso("JEFE ESTACION");
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
    std::stringstream ss;
    ss <<"Mi pid es:";
    ss << getpid();
	log.loggear(ss.str());
	char buffer[BUFFSIZE];
	bool salir = false;
	while(!salir){
		ssize_t bytesLeidos = canal->leer ( static_cast<void*>(buffer), 3 );
		std::string mensaje = buffer;
		mensaje.resize ( bytesLeidos );
		std::stringstream ss;
		ss << "Lei el mensaje" << mensaje;
		log.loggear(ss.str());
		if(mensaje == "q")
			salir = true;
		else
		{
			Auto a(mensaje);
			//sleep(5);
			bool libre = asignarAEmpleado(a);
			std::stringstream ss2;
            ss2 << "Descarté" << mensaje;
			if(!libre)
				log.loggear(ss2.str());
		}
	}

	log.loggear("Final");
	canal->cerrar();
	return 0;
}

JefeEstacion::~JefeEstacion() {
	delete(canal);
}

