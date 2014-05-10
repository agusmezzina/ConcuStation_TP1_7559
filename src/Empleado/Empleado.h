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
#include <vector>
#include <iostream>
#include <fstream>

class Empleado {
private:
	int id;
	int cantidadSurtidores;

    Log log;

	std::vector<Surtidor*> surtidores;
	Semaforo* semSurtidores;
	Caja* caja;
	TransferenciaEmpleado* transferencia;

	void iniciar();
public:
	Empleado(int, int);
	int run();
	virtual ~Empleado();
};

#endif /* EMPLEADO_H_ */
