/*
 * Empleado.cpp
 *
 *  Created on: 06/05/2014
 *      Author: agustin
 */

#include "Empleado.h"
#include <sstream>
#include <unistd.h>

Empleado::Empleado(int id, int cantSurtidores): id(id), cantidadSurtidores(cantSurtidores),
            log(Constantes::LOG){
	caja = NULL;
	transferencia = NULL;
	std::stringstream ss;
	ss << "EMPLEADO ";
	ss << id;
	log.setProceso(ss.str());
}

void Empleado::iniciar(){
	transferencia = new TransferenciaEmpleado(Constantes::TRANSFERENCIA,id,id);
	caja = new Caja(Constantes::CAJA,0);

	for(int i=0;i<cantidadSurtidores;i++){
		surtidores.push_back(new Surtidor(Constantes::SURTIDOR,i,i));
	}
}

int Empleado::run(){
    std::stringstream ss;
    ss <<"Mi pid es:";
    ss << getpid();
	log.loggear(ss.str());
	iniciar();
	log.loggear("Inicialice recursos");
	for(int i = 0; i < 2; i++){
		log.loggear("Quiero leer");
		Auto a = transferencia->atenderAuto();
		log.loggear("Atendí auto " + a.getPatente());
		transferencia->terminarAtencion();
	}
	log.loggear("Termine!");
	return 0;
}

Empleado::~Empleado() {
	delete(caja);
	delete(transferencia);

	for(int i=0;i<cantidadSurtidores;i++){
		delete surtidores[i];
	}
}

