/*
 * Estacion.h
 *
 *  Created on: 05/05/2014
 *      Author: agustin
 */

#ifndef ESTACION_H_
#define ESTACION_H_

#include "Common/ProcessManager.h"
#include "Common/Semaforo.h"
#include "Common/FifoEscritura.h"
#include "Common/Caja.h"
#include "Common/Constantes.h"
#include "Common/Surtidor.h"
#include "Common/ControlEmpleados.h"
#include "Common/TransferenciaEmpleado.h"
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <unistd.h>

class Estacion {
private:
	int cantEmpleados;
	int cantSurtidores;

	Caja* caja;
	FifoEscritura* canal; //Fifo hacia el JefeEmpleados
	std::vector<Surtidor*> surtidores;
	std::vector<TransferenciaEmpleado*> transferencias;
	ControlEmpleados* controlEmpleados;
	Semaforo* semSurtidores;
	std::vector<pid_t> empleados;

	void iniciar();
	void lanzarJefeEstacion();
	void lanzarEmpleados();

public:
	Estacion(int cantidadEmpleados, int cantidadSurtidores);
	int run();
	virtual ~Estacion();
};

#endif /* ESTACION_H_ */
