/*
 * AccesoCaja.h
 *
 *  Created on: 21/06/2014
 *      Author: agustin
 */

#ifndef ACCESOCAJA_H_
#define ACCESOCAJA_H_

#include "../Common/Cola.h"
#include "../Common/OpCaja.h"
#include "../Common/ValorCaja.h"
#include "../Common/Constantes.h"
#include "../Common/EventHandler.h"
#include "../Common/SignalHandler.h"
#include <assert.h>
#include <stdlib.h>
#include <iostream>

class AccesoCaja : EventHandler {
private:
	int caja;
	Cola<opCaja>* cola;
	Cola<valorCaja>* colaRta;
	void iniciar();
	void finalizar();
public:
	AccesoCaja();
	virtual int handleSignal ( int signum );
	int run();
	virtual ~AccesoCaja();
};

#endif /* ACCESOCAJA_H_ */
