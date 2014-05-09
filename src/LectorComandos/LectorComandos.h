/*
 * LectorComandos.h
 *
 *  Created on: 08/05/2014
 *      Author: agustin
 */

#ifndef LECTORCOMANDOS_H_
#define LECTORCOMANDOS_H_

#include <iostream>
#include <string>
#include <unistd.h>
#include <signal.h>

class LectorComandos {
	private:
	pid_t procesoAsociado;
public:
	LectorComandos(pid_t);
	int run();
	void notificarConsultaCaja();
	void notificarFin();
	virtual ~LectorComandos();
};

#endif /* LECTORCOMANDOS_H_ */
