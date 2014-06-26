/*
 * AccesoCaja.cpp
 *
 *  Created on: 21/06/2014
 *      Author: agustin
 */

#include "AccesoCaja.h"

AccesoCaja::AccesoCaja(bool debug) {
	this->cola = NULL;
	this->colaRta = NULL;
	this->log = NULL;
	this->caja = 0;
	this->debug = debug;
}

void AccesoCaja::iniciar(){
	SignalHandler :: getInstance()->registrarHandler ( SIGTERM, this);
	cola = new Cola<opCaja> (Constantes::COLA, 1);
	colaRta = new Cola<valorCaja> (Constantes::COLA, 2);
	if(debug){
		log = new Log(Constantes::LOG);
		log->setProceso("ACCESO CAJA");
		std::stringstream logInicio;
		logInicio << "Inicia Acceso Caja. " << "Mi pid es: " << getpid() << ".";
		log->loggear(logInicio.str());
	}
}

int AccesoCaja::run(){
	iniciar();
	while(1){
		opCaja op;
		cola->leer(-2, &op);
		if(op.escribir == true)
			caja += op.valor;

		valorCaja rta;
		rta.mtype = op.id;
		rta.monto = caja;

		if(debug){
			std::stringstream mensaje;
			mensaje << "Se atiende la solicitud de: ";
			if(op.id == 1)
				mensaje << "CONSULTAR CAJA";
			else
				mensaje << "EMPLEADO " << op.id - 2;
			log->loggear(mensaje.str());
		}

		colaRta->escribir(rta);
	}
	return 0;
}

void AccesoCaja::finalizar(){
	delete(cola);
	delete(log);
	SignalHandler::destruir();
}

int AccesoCaja::handleSignal ( int signum ) {
	assert ( signum == SIGTERM );
	this->finalizar();
	exit(0);
}

AccesoCaja::~AccesoCaja() {
	finalizar();
}

