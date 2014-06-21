/*
 * Estacion.h
 *
 *  Created on: 05/05/2014
 *      Author: agustin
 */

#ifndef ESTACION_H_
#define ESTACION_H_

#include "GeneradorAutos.h"
#include "Common/ProcessManager.h"
#include "Common/Semaforo.h"
#include "Common/FifoEscritura.h"
#include "Common/Auto.h"
#include "Common/Cola.h"
#include "Common/Constantes.h"
#include "Common/Surtidor.h"
#include "Common/ControlEmpleados.h"
#include "Common/TransferenciaEmpleado.h"
#include "Common/Log.h"
#include "Common/SIGINT_Handler.h"
#include "Common/SIGTERM_Handler.h"
#include "Common/SignalHandler.h"
#include "Common/OpCaja.h"
#include "Common/ValorCaja.h"
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <unistd.h>

class Estacion {
private:
	int cantEmpleados;
	int cantSurtidores;

    Log log;
    SIGINT_Handler sigint_handler;
    SIGTERM_Handler sigterm_handler;
	FifoEscritura* canal; //Fifo hacia el JefeEmpleados
	std::vector<Surtidor*> surtidores;
	std::vector<TransferenciaEmpleado*> transferencias;
	ControlEmpleados* controlEmpleados;
	Semaforo* semSurtidores;
	Cola<autoStruct>* cola;
	Cola<opCaja>* colaCaja;
	Cola<valorCaja>* colaRespuesta;

	std::vector<pid_t> empleados;
	pid_t jefe;
	pid_t accCaja;

	void iniciar();
	void lanzarLectorComandos();
	void lanzarJefeEstacion();
	void lanzarEmpleados();
	void lanzarAccesoCaja();
	void crearArchivos();

public:
	Estacion(int cantidadEmpleados, int cantidadSurtidores);
	int run();
	virtual ~Estacion();
};

#endif /* ESTACION_H_ */
