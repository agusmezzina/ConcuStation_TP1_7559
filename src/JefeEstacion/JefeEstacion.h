/*
 * JefeEstacion.h
 *
 *  Created on: 14/04/2014
 *      Author: agustin
 */

#ifndef JEFEESTACION_H_
#define JEFEESTACION_H_

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "../Common/Constantes.h"
#include "../Common/Auto.h"
#include "../Common/TransferenciaEmpleado.h"
#include "../Common/Log.h"
#include "../Common/SIGTERM_Handler.h"
#include "../Common/SignalHandler.h"
#include "../Common/Cola.h"

class JefeEstacion {
private:
	static const int BUFFSIZE = 50;
	int cantidadEmpleados;
	bool debug;

	Log* log;

	//FifoLectura* canal;
	std::vector<TransferenciaEmpleado*> transferencias;
	SIGTERM_Handler sigterm_handler;
	Cola<autoStruct>* cola;

	void iniciar();
	//Devuelve false si no encontró empleado libre
	bool asignarAEmpleado(const Auto& a);
public:
	JefeEstacion(int, bool);
	int run();
	virtual ~JefeEstacion();
};

#endif /* JEFEESTACION_H_ */
