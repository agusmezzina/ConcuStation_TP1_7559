/*
 * ConsultarCaja.h
 *
 *  Created on: 14/04/2014
 *      Author: agustin
 */

#ifndef CONSULTARCAJA_H_
#define CONSULTARCAJA_H_

#include "../Common/Log.h"
#include "../Common/Constantes.h"
#include "../Common/Cola.h"
#include "../Common/OpCaja.h"
#include "../Common/ValorCaja.h"
#include <iostream>

class ConsultarCaja {
private:
	bool debug;
	Log* log;
	Cola<opCaja>* cola;
	Cola<valorCaja>* colaRta;
	int solicitarValor();
public:
	ConsultarCaja(bool);
	int run();
	virtual ~ConsultarCaja();
};

#endif /* CONSULTARCAJA_H_ */
