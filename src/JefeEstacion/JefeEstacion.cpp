/*
 * JefeEstacion.cpp
 *
 *  Created on: 14/04/2014
 *      Author: agustin
 */

#include "JefeEstacion.h"
#include <sstream>
#include <fstream>

JefeEstacion::JefeEstacion(int cantEmpleados): cantidadEmpleados(cantEmpleados),
        log(Constantes::LOG){
	canal = NULL;
	cola = NULL;
	log.setProceso("JEFE ESTACION");
}

const int JefeEstacion::BUFFSIZE;

void JefeEstacion::iniciar(){
	SignalHandler :: getInstance()->registrarHandler ( SIGTERM,&sigterm_handler );
	canal = new FifoLectura(Constantes::ARCHIVO_FIFO);
    cola = new Cola<autoStruct> (Constantes::COLA,0);
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
//	char buffer[BUFFSIZE];
//	bool salir = false;

	while(this->sigterm_handler.getGracefulQuit() == 0){
		/*ssize_t bytesLeidos = canal->leer ( static_cast<void*>(buffer), 3 );
		std::string mensaje = buffer;
		mensaje.resize ( bytesLeidos );
		std::stringstream ss;
		*/
		usleep(200000);
		std::stringstream ss2;
		autoStruct aS;
		cola->leer(PRIORIDAD,&aS);
		ss2 << "Lei la pantente: " << aS.patente << " tipo: ";
		ss2 <<(aS.mtype==NORMAL?"NORMAL":"VIP");
		log.loggear(ss2.str());
		Auto a(aS.patente);
		bool libre = asignarAEmpleado(a);
		std::stringstream ss3;
		ss3 << "Descarté" << aS.patente;
		if(!libre)
			log.loggear(ss3.str());

	}

	log.loggear("Final");
	canal->cerrar();
	return 0;
}

JefeEstacion::~JefeEstacion() {
	delete(canal);
	delete cola;
	//Libero las transferencias
	for(char i=0;i<cantidadEmpleados;i++){
		transferencias[i]->eliminarSemaforos();
		delete transferencias[i];
	}
}

