/*
 * Estacion.cpp
 *
 *  Created on: 05/05/2014
 *      Author: agustin
 */

#include "Estacion.h"
#include "Common/Log.h"
#include <sstream>

Estacion::Estacion(int cantidadEmpleados, int cantidadSurtidores, bool debug):
		cantEmpleados(cantidadEmpleados), cantSurtidores(cantidadSurtidores), debug(debug){
	//canal = NULL;
	log = NULL;
	cola = NULL;
	colaCaja = NULL;
	colaRespuesta = NULL;
	controlEmpleados = NULL;
	semSurtidores = NULL;
	accCaja = 0;
	jefe = 0;
}

void Estacion::iniciar(){
	SignalHandler :: getInstance()->registrarHandler ( SIGTERM,&sigterm_handler );
	crearArchivos();

	//canal = new FifoEscritura(Constantes::ARCHIVO_FIFO);
    cola = new Cola<autoStruct> (Constantes::COLA,0);
    colaCaja = new Cola<opCaja> (Constantes::COLA, 1);
    colaRespuesta = new Cola<valorCaja> (Constantes::COLA, 2);
    if(debug){
    	log = new Log(Constantes::LOG);
    	log->setProceso("INIT");
    }

	for(char i=0;i<cantSurtidores;i++){
		surtidores.push_back(new Surtidor(Constantes::SURTIDOR,i,i,1));
	}

	for(char i=0;i<cantEmpleados;i++){
		transferencias.push_back(new TransferenciaEmpleado(Constantes::TRANSFERENCIA,i,i,1,0));
	}

	semSurtidores = new Semaforo(Constantes::SURTIDOR,cantSurtidores,cantSurtidores);
}

void Estacion::crearArchivos(){
	std::ofstream surtidor;
	surtidor.open(Constantes::SURTIDOR.c_str());
	surtidor.close();

	std::ofstream transferencia;
	transferencia.open(Constantes::TRANSFERENCIA.c_str());
	transferencia.close();

	std::ofstream cola;
	cola.open(Constantes::COLA.c_str());
	cola.close();
}

void Estacion::lanzarLectorComandos(){
	std::string paramDebug;
	if(debug)
			paramDebug = "s";
		else
			paramDebug = "n";
	char* const argv[] = { const_cast<char*>(Constantes::pathLectorComandos.c_str()), const_cast<char*>(paramDebug.c_str()), (char*) 0 };
	ProcessManager::run(Constantes::pathLectorComandos.c_str(), argv);
}

void Estacion::lanzarJefeEstacion(){
	std::stringstream ss;
	ss << cantEmpleados;
	std::string cant = ss.str();
	std::string paramDebug;
	if(debug)
			paramDebug = "s";
		else
			paramDebug = "n";
	char* const argv[] = { const_cast<char*>(Constantes::pathJefeEstacion.c_str()), const_cast<char*>(cant.c_str()), const_cast<char*>(paramDebug.c_str()), (char*) 0 };
	jefe = ProcessManager::run(Constantes::pathJefeEstacion.c_str(), argv);
	//canal->abrir();
}

void Estacion::lanzarEmpleados(){
	std::stringstream ss2;
	ss2 << cantSurtidores;
	std::string cant = ss2.str();
	for(int i=0;i<cantEmpleados;i++){
		std::stringstream ss;
		ss << i;
		std::string id = ss.str();
		std::string paramDebug;
			if(debug)
				paramDebug = "s";
			else
				paramDebug = "n";
		char* const argvE[] = { const_cast<char*>(Constantes::pathEmpleado.c_str()),const_cast<char*>(id.c_str()),
				const_cast<char*>(cant.c_str()), const_cast<char*>(paramDebug.c_str()), (char*) NULL};
		//file.flush();
		empleados.push_back(ProcessManager::run(Constantes::pathEmpleado.c_str(), argvE));
	}
}

void Estacion::lanzarAccesoCaja(){
	char* const argv[] = { const_cast<char*>(Constantes::pathAccesoCaja.c_str()), (char*) 0 };
	accCaja = ProcessManager::run(Constantes::pathAccesoCaja.c_str(), argv);
}

int Estacion::run(){

	iniciar();

	lanzarLectorComandos();
	lanzarJefeEstacion();
	lanzarEmpleados();
	lanzarAccesoCaja();

	GeneradorAutos rcg(100); //el parámetro está en milisegundos

	while(sigterm_handler.getGracefulQuit() == 0){
		autoStruct a = rcg.next();
		/*
		std::string patente = a.getPatente();
		canal->escribir ( static_cast<const void*>(patente.c_str()), patente.size() );
		*/
		cola->escribir(a);
		if(debug){
			std::stringstream ss;
			ss << "Mandé el auto "<< a.patente << " ";
			ss <<((a.mtype ==NORMAL) ? "NORMAL" : "VIP");
			log->loggear(ss.str());
		}
	}

	kill(jefe, 15);
	for(int i = 0; i < cantEmpleados; i++){
		kill(empleados[i], 15);
	}
	kill(accCaja, 15);
	for(int i = 0; i < 2 + cantEmpleados; i++){
		ProcessManager::wait();
	}
	if(debug)
		log->loggear("Final");
	return 0;
}

Estacion::~Estacion() {
	SignalHandler::destruir();
	delete(log);

    //Libero las transferencias
	for(char i=0;i<cantEmpleados;i++){
		transferencias[i]->eliminarSemaforos();
		delete transferencias[i];
	}

	//canal->cerrar();
	//canal->eliminar();
	//delete(canal);
	//delete(controlEmpleados);

	//Libero surtidores
	for(char i=0;i<cantSurtidores;i++){
		surtidores[i]->eliminarSemaforo();
		delete surtidores[i];
	}

    cola->destruir();
    colaCaja->destruir();
    colaRespuesta->destruir();
    delete cola;
    delete colaCaja;
    delete colaRespuesta;
	//controlEmpleados->eliminarSemaforo();

	semSurtidores->eliminar();
	delete(semSurtidores);

}

