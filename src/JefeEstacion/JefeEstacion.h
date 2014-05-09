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
#include "../Common/FifoLectura.h"
#include "../Common/Constantes.h"
#include "../Common/Auto.h"
#include "../Common/TransferenciaEmpleado.h"
#include "../Common/Log.h"

class JefeEstacion {
private:
	static const int BUFFSIZE = 50;
	int cantidadEmpleados;

	Log log;

	FifoLectura* canal;
	std::vector<TransferenciaEmpleado*> transferencias;
	void iniciar();
	//Devuelve false si no encontró empleado libre
	bool asignarAEmpleado(const Auto& a);
public:
	JefeEstacion(int);
	int run();
	virtual ~JefeEstacion();
};

#endif /* JEFEESTACION_H_ */
