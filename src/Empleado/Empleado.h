/*
 * Empleado.h
 *
 *  Created on: 06/05/2014
 *      Author: agustin
 */

#ifndef EMPLEADO_H_
#define EMPLEADO_H_

#include "../Common/Auto.h"
#include "../Common/Caja.h"
#include "../Common/Constantes.h"
#include "../Common/Surtidor.h"
#include "../Common/ControlEmpleados.h"
#include "../Common/TransferenciaEmpleado.h"
#include "../Common/Log.h"
#include "../Common/EventHandler.h"
#include "../Common/SignalHandler.h"
#include "../Common/Cola.h"
#include "../Common/OpCaja.h"
#include "../Common/ValorCaja.h"

#include <signal.h>
#include <assert.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdlib.h>

class Empleado: public EventHandler {
private:
	int id;
	int cantidadSurtidores;

    Log log;

	std::vector<Surtidor*> surtidores;
	Semaforo* semSurtidores;
	Caja* caja;
	TransferenciaEmpleado* transferencia;
	Cola<opCaja>* cola;
	Cola<valorCaja>* colaRta;

	void iniciar();
	void finalizar();
	int depositarEnCaja(int);
public:
	virtual int handleSignal ( int signum );
	Empleado(int, int);
	int run();
	virtual ~Empleado();
};

#endif /* EMPLEADO_H_ */
