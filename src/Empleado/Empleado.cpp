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
	srand(time(NULL));
	caja = NULL;
	transferencia = NULL;
	std::stringstream ss;
	ss << "EMPLEADO ";
	ss << id;
	log.setProceso(ss.str());
}

void Empleado::iniciar(){
	SignalHandler :: getInstance()->registrarHandler ( SIGTERM, this);

	transferencia = new TransferenciaEmpleado(Constantes::TRANSFERENCIA,id,id);
	caja = new Caja(Constantes::CAJA,0);

	for(int i=0;i<cantidadSurtidores;i++){
		surtidores.push_back(new Surtidor(Constantes::SURTIDOR,i,i));
	}
	semSurtidores = new Semaforo(Constantes::SURTIDOR,cantidadSurtidores);
}

int Empleado::handleSignal ( int signum ) {
	assert ( signum == SIGTERM );
	this->finalizar();
	exit(0);
}

int Empleado::run(){
    std::stringstream ss;
    ss <<"Mi pid es:";
    ss << getpid();
	//log.loggear(ss.str());
	iniciar();
	//log.loggear("Inicialice recursos");
	while(1){
		//log.loggear("Quiero leer");
		Auto a = transferencia->atenderAuto();
		log.loggear("Intento tomar surtidor");
		semSurtidores->p();
		log.loggear("Hay Surtidor. Lo busco");
		for(int i=0; i < cantidadSurtidores; i++){
            if(surtidores[i]->ocuparSiEstaLibre(getpid())){
                std::stringstream ss;
                ss << "Encontre el surtidor ";
                ss << i;
                log.loggear(ss.str());
                int n = rand() % 100 +1;
                std::stringstream ss3;
                ss3 << "Cargo " << n << " litros";
                log.loggear(ss3.str());
                usleep(100*n);
                std::stringstream ss2;
                ss2 << "Deposito en la caja. El valor actual es: ";
                ss2 << caja->depositar(10*n);//Cambiar por un random
                log.loggear(ss2.str());
                surtidores[i]->liberarSurtidor();
                break;
            }
		}
		log.loggear("Atendí auto " + a.getPatente());
		semSurtidores->v();
		transferencia->terminarAtencion();
	}
	log.loggear("Termine!");
	return 0;
}

void Empleado::finalizar(){
	try{
	delete(caja);
	delete(transferencia);

	for(int i=0;i<cantidadSurtidores;i++){
		delete surtidores[i];
	}
	delete semSurtidores;
	}catch(char const* s){
        std::cout << s;
	}
}

Empleado::~Empleado() {
	finalizar();
}

