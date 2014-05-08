/*
 * Estacion.cpp
 *
 *  Created on: 05/05/2014
 *      Author: agustin
 */

#include "Estacion.h"

Estacion::Estacion(int cantidadEmpleados, int cantidadSurtidores):
		cantEmpleados(cantidadEmpleados), cantSurtidores(cantidadSurtidores){

	canal = NULL;
	caja = NULL;
	controlEmpleados = NULL;
	semSurtidores = NULL;
}

void Estacion::iniciar(){
	caja = new Caja(Constantes::CAJA, 0, 1);
	caja->setDinero(0);

	canal = new FifoEscritura(Constantes::ARCHIVO_FIFO);

	for(char i=0;i<cantSurtidores;i++){
		surtidores.push_back(new Surtidor(Constantes::SURTIDOR,i,i,1));
	}

	for(char i=0;i<cantEmpleados;i++){
		transferencias.push_back(new TransferenciaEmpleado(Constantes::TRANSFERENCIA,i,i,1,0));
	}

	controlEmpleados = new ControlEmpleados(Constantes::TRANSFERENCIA,cantEmpleados,1);
	controlEmpleados->setEmpleadosLibres(cantEmpleados);

	semSurtidores = new Semaforo(Constantes::SURTIDOR,cantSurtidores,cantSurtidores);
}

void Estacion::lanzarJefeEstacion(){
	std::stringstream ss;
	ss << cantEmpleados;
	std::string cant = ss.str();
	char* const argv[] = { const_cast<char*>(Constantes::pathJefeEstacion.c_str()), const_cast<char*>(cant.c_str()), (char*) 0 };
	ProcessManager::run(Constantes::pathJefeEstacion.c_str(), argv);
	canal->abrir();
}

void Estacion::lanzarEmpleados(){
	std::stringstream ss2;
	ss2 << cantSurtidores;
	std::string cant = ss2.str();
	for(int i=0;i<cantEmpleados;i++){
		std::stringstream ss;
		ss << i;
		std::string id = ss.str();
		char* const argvE[] = { const_cast<char*>(Constantes::pathEmpleado.c_str()),const_cast<char*>(id.c_str()), const_cast<char*>(cant.c_str()),(char*) NULL};
		//file.flush();
		ProcessManager::run(Constantes::pathEmpleado.c_str(), argvE);

	    }
}

int Estacion::run(){

	iniciar();

	std::fstream file;
	file.open("logPrincipal",std::fstream::out);

	lanzarJefeEstacion();
	lanzarEmpleados();

	std::string patente;
	bool salir = false;

	while(!salir) {
		std::cin >> patente;
		if(patente == "q")
			salir = true;
		//Limito cadena de entrada para evitar desbordamientos en el canal.
		patente = patente.substr(0, 6);
		canal->escribir ( static_cast<const void*>(patente.c_str()), patente.size() );
		file << "[Init] Escribí la patente " << patente << std::endl;
		file.flush();
	}

	ProcessManager::wait();
	file << "[Init] Final" << std::endl;
	file.flush();
	canal->cerrar();
	canal->eliminar();
	file.close();
	return 0;
}

Estacion::~Estacion() {
	canal->cerrar();
	canal->eliminar();
	delete(canal);
	delete(caja);
	delete(controlEmpleados);

	//Libero surtidores
	for(char i=0;i<cantSurtidores;i++){
		surtidores[i]->eliminarSemaforo();
		delete surtidores[i];
	}

	//Libero las transferencias
	for(char i=0;i<cantEmpleados;i++){
		transferencias[i]->eliminarSemaforos();
		delete transferencias[i];
	}
	controlEmpleados->eliminarSemaforo();

	semSurtidores->eliminar();
	delete(semSurtidores);
	//Libero la caja
	caja->eliminarSemaforo();
}

