/*
 * ConsultarCaja.cpp
 *
 *  Created on: 14/04/2014
 *      Author: agustin
 */

#include "ConsultarCaja.h"

ConsultarCaja::ConsultarCaja(): log(Constantes::LOG) {
	caja = new Caja(Constantes::CAJA,0);
	log.setProceso("CONSULTAR CAJA");
}

int ConsultarCaja::run(){
	std::cout << "Entro" << std::endl;
	std::string mensaje = "La recaudación de la caja es: " + caja->consultarCaja();
	std::cout << "Salgo" << std::endl;
	std::cout << mensaje << std::endl;
	log.loggear(mensaje);
	return 0;
}

ConsultarCaja::~ConsultarCaja() {
	delete(caja);
}

