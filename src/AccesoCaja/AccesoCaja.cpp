/*
 * AccesoCaja.cpp
 *
 *  Created on: 21/06/2014
 *      Author: agustin
 */

#include "AccesoCaja.h"

AccesoCaja::AccesoCaja() {
	cola = NULL;
	colaRta = NULL;
	caja = 0;
}

void AccesoCaja::iniciar(){
	cola = new Cola<opCaja> (Constantes::COLA, 1);
	colaRta = new Cola<valorCaja> (Constantes::COLA, 2);
}

int AccesoCaja::run(){
	iniciar();
	while(1){
		opCaja op;
		cola->leer(-50, &op);
		if(op.escribir == true)
			caja += op.valor;

		valorCaja rta;
		rta.mtype = op.mtype;
		rta.monto = caja;
		colaRta->escribir(rta);
	}
	return 0;
}

void AccesoCaja::finalizar(){
	delete(cola);
}

int AccesoCaja::handleSignal ( int signum ) {
	assert ( signum == SIGTERM );
	this->finalizar();
	exit(0);
}

AccesoCaja::~AccesoCaja() {
	finalizar();
}

