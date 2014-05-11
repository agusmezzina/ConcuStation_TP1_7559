/*
 * ConsultarCaja.cpp
 *
 *  Created on: 14/04/2014
 *      Author: agustin
 */

#include "ConsultarCaja.h"
#include <sstream>

ConsultarCaja::ConsultarCaja(): log(Constantes::LOG) {
	caja = new Caja(Constantes::CAJA,0);
	log.setProceso("CONSULTAR CAJA");
}

int ConsultarCaja::run(){
	std::stringstream mensaje;
	mensaje << "La recaudación de la caja es: ";
	mensaje << caja->consultarCaja();
	std::cout << mensaje.str() << std::endl;
	log.loggear(mensaje.str());
	return 0;
}

ConsultarCaja::~ConsultarCaja() {
	delete(caja);
}

