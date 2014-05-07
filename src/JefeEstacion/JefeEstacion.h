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
#include "../Common/FifoLectura.h"
#include "../Common/Constantes.h"

class JefeEstacion {
private:
	static const int BUFFSIZE = 50;
	FifoLectura* canal;

	void iniciar();
public:
	JefeEstacion();
	int run();
	virtual ~JefeEstacion();
};

#endif /* JEFEESTACION_H_ */
