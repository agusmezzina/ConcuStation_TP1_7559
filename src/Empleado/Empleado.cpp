/*
 * Empleado.cpp
 *
 *  Created on: 06/05/2014
 *      Author: agustin
 */

#include "Empleado.h"
#include <sstream>
#include <unistd.h>

Empleado::Empleado(int id, int cantSurtidores, bool debug): id(id), cantidadSurtidores(cantSurtidores), debug(debug){
	srand(time(NULL));
	log = NULL;
	cola = NULL;
	colaRta = NULL;
	transferencia = NULL;
	semSurtidores = NULL;
}

void Empleado::iniciar(){
	SignalHandler :: getInstance()->registrarHandler ( SIGTERM, this);

	if(debug){
		std::stringstream ss;
		ss << "EMPLEADO ";
		ss << id;
		log = new Log(Constantes::LOG);
		log->setProceso(ss.str());
		std::stringstream logInicio;
		logInicio << "Inicia Empleado " << id << ". Mi pid es: " << getpid() << ".";
		log->loggear(logInicio.str());
	}
	transferencia = new TransferenciaEmpleado(Constantes::TRANSFERENCIA,id,id);
	cola = new Cola<opCaja> (Constantes::COLA, 1);
	colaRta = new Cola<valorCaja> (Constantes::COLA, 2);

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

int Empleado::depositarEnCaja(int monto){
	opCaja op;
	memset(&op,0,sizeof(op));
	op.mtype = 2;
	op.id = this->id + 2;
	op.valor = monto;
	op.escribir = true;

	cola->escribir(op);

	valorCaja valor;
	colaRta->leer(this->id + 2, &valor);
	return valor.monto;
}

int Empleado::run(){
	iniciar();
	while(1){
		Auto a = transferencia->atenderAuto();
		if(debug){
			std::stringstream ss;
			ss << "Recibí el auto: " << a.getPatente();
			ss <<". Intento tomar surtidor.";
			log->loggear(ss.str());
		}
		semSurtidores->p();
		if(debug)
			log->loggear("Hay Surtidor. Lo busco");
		for(int i=0; i < cantidadSurtidores; i++){
            if(surtidores[i]->ocuparSiEstaLibre(getpid())){
            	if(debug){
					std::stringstream ss;
					ss << "Encontre el surtidor ";
					ss << i;
					log->loggear(ss.str());
            	}
                int n = rand() % 100 +1;
                if(debug)
                {
					std::stringstream ss3;
					ss3 << "Cargo " << n << " litros";
					log->loggear(ss3.str());
                }
                usleep(100000*n); //100*n
                if(debug){
                	std::stringstream ss;
					ss << "Cobré un valor de ";
					//ss2 << caja->depositar(10*n);//Cambiar por un random
					ss << (10*n);
					ss << ". Intento acceder a la Caja.";
					log->loggear(ss.str());
                }
                int depositado = this->depositarEnCaja(10*n);
                if(debug){
					std::stringstream ss2;
					ss2 << "Deposité en la caja. El valor actual es: ";
					//ss2 << caja->depositar(10*n);//Cambiar por un random
					ss2 << depositado;
					log->loggear(ss2.str());
                }
                surtidores[i]->liberarSurtidor();
                break;
            }
		}
		if(debug)
			log->loggear("Atendí auto " + a.getPatente());
		semSurtidores->v();
		transferencia->terminarAtencion();
	}
	if(debug)
		log->loggear("Termine!");
	return 0;
}

void Empleado::finalizar(){
	try{
		delete(log);
		delete(cola);
		delete(colaRta);
		delete(transferencia);

		for(int i=0;i<cantidadSurtidores;i++){
			delete surtidores[i];
		}
		delete semSurtidores;
		SignalHandler::destruir();
	}catch(char const* s){
        std::cout << s;
	}
}

Empleado::~Empleado() {
	finalizar();
}

