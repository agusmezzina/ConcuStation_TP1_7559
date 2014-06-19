/*
 * GeneradorAutos.h
 *
 *  Created on: 09/05/2014
 *      Author: agustin
 */

#ifndef GENERADORAUTOS_H_
#define GENERADORAUTOS_H_

#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Common/Auto.h"

//Genera autos nuevos cada T milisegundos, donde T distribuye exponencialmente con media lambda
class GeneradorAutos {
private:
	int lambda;
	int mu;
	char patActual[4];
public:
	GeneradorAutos(int media);
	autoStruct next();
	virtual ~GeneradorAutos();
};

#endif /* GENERADORAUTOS_H_ */
