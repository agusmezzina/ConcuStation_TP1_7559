/*
 * JefeEstacion.cpp
 *
 *  Created on: 14/04/2014
 *      Author: agustin
 */

#include "JefeEstacion.h"
#include <sstream>
#include <fstream>

JefeEstacion::JefeEstacion(int cantEmpleados, bool debug): cantidadEmpleados(cantEmpleados), debug(debug){
	//canal = NULL;
	cola = NULL;
	log = NULL;
}

const int JefeEstacion::BUFFSIZE;

void JefeEstacion::iniciar(){
	SignalHandler :: getInstance()->registrarHandler ( SIGTERM,&sigterm_handler );
	if(debug){
		log = new Log(Constantes::LOG);
		log->setProceso("JEFE ESTACION");
	}
	//canal = new FifoLectura(Constantes::ARCHIVO_FIFO);
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

	//canal->abrir();
	if(debug){
		std::stringstream ss;
		ss <<"Mi pid es:";
		ss << getpid();
		log->loggear(ss.str());
	}

	while(this->sigterm_handler.getGracefulQuit() == 0){
		usleep(200000);
		autoStruct aS;
		cola->leer(PRIORIDAD,&aS);
		if(debug){
			std::stringstream ss2;
			ss2 << "Lei la pantente: " << aS.patente << " tipo: ";
			ss2 <<(aS.mtype==NORMAL?"NORMAL":"VIP");
			log->loggear(ss2.str());
		}
		Auto a(aS.patente);
		bool libre = asignarAEmpleado(a);
		if((!libre)&&(debug)){
			std::stringstream ss3;
			ss3 << "Descarté" << aS.patente;
			log->loggear(ss3.str());
		}

	}
	if(debug)
		log->loggear("Final");
	//canal->cerrar();
	return 0;
}

JefeEstacion::~JefeEstacion() {
	//delete(canal);
	delete log;
	delete cola;
	//Libero las transferencias
	for(char i=0;i<cantidadEmpleados;i++){
		transferencias[i]->eliminarSemaforos();
		delete transferencias[i];
	}
	SignalHandler::destruir();
}

