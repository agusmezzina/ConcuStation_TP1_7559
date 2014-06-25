/*
 * ConsultarCaja.cpp
 *
 *  Created on: 14/04/2014
 *      Author: agustin
 */

#include "ConsultarCaja.h"
#include <sstream>

ConsultarCaja::ConsultarCaja(bool debug): debug(debug){
	cola = new Cola<opCaja> (Constantes::COLA, 1);
	colaRta = new Cola<valorCaja> (Constantes::COLA, 2);
	log = NULL;
	if(debug)
	{
		log = new Log(Constantes::LOG);
		log->setProceso("CONSULTAR CAJA");
	}
}

int ConsultarCaja::run(){
	std::stringstream mensaje;
	mensaje << "La recaudación de la caja es: ";
	//mensaje << caja->consultarCaja();
	mensaje << this->solicitarValor();
	std::cout << mensaje.str() << std::endl;
	if(debug)
		log->loggear(mensaje.str());
	return 0;
}

int ConsultarCaja::solicitarValor(){
	opCaja op;
	op.mtype = 1;
	op.escribir = false;
	op.valor = 0;

	valorCaja valor;

	cola->escribir(op);
	colaRta->leer(1, &valor);
	return valor.monto;
}

ConsultarCaja::~ConsultarCaja() {
	delete(log);
	delete(cola);
	delete(colaRta);
}

