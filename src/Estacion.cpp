/*
 * Estacion.cpp
 *
 *  Created on: 05/05/2014
 *      Author: agustin
 */

#include "Estacion.h"
#include "Common/Log.h"

Estacion::Estacion(int cantidadEmpleados, int cantidadSurtidores):
		cantEmpleados(cantidadEmpleados), cantSurtidores(cantidadSurtidores),
            log(Constantes::LOG){
	canal = NULL;
	caja = NULL;
	controlEmpleados = NULL;
	semSurtidores = NULL;
	log.setProceso("INIT");
}

void Estacion::iniciar(){
	SignalHandler :: getInstance()->registrarHandler ( SIGINT,&sigint_handler );
	SignalHandler :: getInstance()->registrarHandler ( SIGTERM,&sigterm_handler );

	caja = new Caja(Constantes::CAJA, 0, 1);
	caja->setDinero(0);

	canal = new FifoEscritura(Constantes::ARCHIVO_FIFO);

	for(char i=0;i<cantSurtidores;i++){
		surtidores.push_back(new Surtidor(Constantes::SURTIDOR,i,i,1));
	}

	for(char i=0;i<cantEmpleados;i++){
		transferencias.push_back(new TransferenciaEmpleado(Constantes::TRANSFERENCIA,i,i,1,0));
	}

	semSurtidores = new Semaforo(Constantes::SURTIDOR,cantSurtidores,cantSurtidores);
}

void Estacion::lanzarLectorComandos(){
	std::stringstream ss;
	int pid_n = getpid();
	ss << pid_n;
	std::string pid = ss.str();
	char* const argv[] = { const_cast<char*>(Constantes::pathLectorComandos.c_str()), (char*) 0 };
	ProcessManager::run(Constantes::pathLectorComandos.c_str(), argv);
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
		empleados.push_back(ProcessManager::run(Constantes::pathEmpleado.c_str(), argvE));
	}
}

int Estacion::run(){

	iniciar();

	lanzarLectorComandos();
	lanzarJefeEstacion();
	lanzarEmpleados();

	GeneradorAutos rcg(10); //el parámetro está en milisegundos

	while(sigterm_handler.getGracefulQuit() == 0){
		Auto a = rcg.next();
		std::string patente = a.getPatente();
		canal->escribir ( static_cast<const void*>(patente.c_str()), patente.size() );
		log.loggear("Escribí la patente " + patente);
	}
	std::string salir = "q";
	canal->escribir ( static_cast<const void*>(salir.c_str()), salir.size() );
	log.loggear("Escribí la patente " + salir);
	std::cout << "Chau!" << std::endl;
	for(int i = 0; i < cantEmpleados; i++){
		kill(empleados[i], 15);
	}
	for(int i = 0; i < 2 + cantEmpleados; i++){
		ProcessManager::wait();
	}
	log.loggear("Final");
	return 0;
}

Estacion::~Estacion() {
	SignalHandler::destruir();

    //Libero las transferencias
	for(char i=0;i<cantEmpleados;i++){
		transferencias[i]->eliminarSemaforos();
		delete transferencias[i];
	}

	canal->cerrar();
	canal->eliminar();
	delete(canal);
    caja->eliminarSemaforo();
	delete(caja);
	//delete(controlEmpleados);

	//Libero surtidores
	for(char i=0;i<cantSurtidores;i++){
		surtidores[i]->eliminarSemaforo();
		delete surtidores[i];
	}


	//controlEmpleados->eliminarSemaforo();

	semSurtidores->eliminar();
	delete(semSurtidores);
	//Libero la caja

}

