/*
 * ConsultarCaja.h
 *
 *  Created on: 14/04/2014
 *      Author: agustin
 */

#ifndef CONSULTARCAJA_H_
#define CONSULTARCAJA_H_

#include "../Common/Caja.h"
#include "../Common/Log.h"
#include "../Common/Constantes.h"
#include "../Common/Cola.h"
#include "../Common/OpCaja.h"
#include "../Common/ValorCaja.h"
#include <iostream>

class ConsultarCaja {
private:
	Log log;
	Caja* caja;
	Cola<opCaja>* cola;
	Cola<valorCaja>* colaRta;
	int solicitarValor();
public:
	ConsultarCaja();
	int run();
	virtual ~ConsultarCaja();
};

#endif /* CONSULTARCAJA_H_ */
