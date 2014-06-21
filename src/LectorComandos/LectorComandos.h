/*
 * LectorComandos.h
 *
 *  Created on: 08/05/2014
 *      Author: agustin
 */

#ifndef LECTORCOMANDOS_H_
#define LECTORCOMANDOS_H_

#include "../Common/ProcessManager.h"
#include "../Common/Constantes.h"
#include <iostream>
#include <string>
#include <unistd.h>
#include <signal.h>

class LectorComandos {
public:
	LectorComandos();
	int run();
	void consultaCaja();
	void notificarFin();
	virtual ~LectorComandos();
};

#endif /* LECTORCOMANDOS_H_ */
