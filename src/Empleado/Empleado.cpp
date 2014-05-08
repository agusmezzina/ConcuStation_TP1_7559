/*
 * Empleado.cpp
 *
 *  Created on: 06/05/2014
 *      Author: agustin
 */

#include "Empleado.h"

Empleado::Empleado(int id, int cantSurtidores): id(id), cantidadSurtidores(cantSurtidores) {
	caja = NULL;
	transferencia = NULL;
}

void Empleado::iniciar(){
	transferencia = new TransferenciaEmpleado(Constantes::TRANSFERENCIA,id,id);
	caja = new Caja(Constantes::CAJA,0);

	for(int i=0;i<cantidadSurtidores;i++){
		surtidores.push_back(new Surtidor(Constantes::SURTIDOR,i,i));
	}
}

int Empleado::run(){
	std::fstream file;
	file.open("logEmpleados",std::fstream::out | std::fstream::app);
	file << "[EMPLEADO" << id << "]Mi pid es:" << getpid() << std::endl;
	iniciar();
	file << "[EMPLEADO" << id << "] Inicialice recursos" << std::endl;
	for(int i = 0; i < 10; i++){
		Auto a = transferencia->atenderAuto();
		file << "[EMPLEADO" << id << "] Atendí auto " << a.getPatente() << std::endl;
		transferencia->terminarAtencion();
	}
	file << "[EMPLEADO" << id << "] Termine!"<< std::endl;
	file.close();
	return 0;
}

Empleado::~Empleado() {
	delete(caja);
	delete(transferencia);

	for(int i=0;i<cantidadSurtidores;i++){
		delete surtidores[i];
	}
}

