/*
 * GeneradorAutos.cpp
 *
 *  Created on: 09/05/2014
 *      Author: agustin
 */

#include "GeneradorAutos.h"

GeneradorAutos::GeneradorAutos(int media): lambda(media) {
	srand(time(NULL));
}

Auto GeneradorAutos::next(){
	int n = rand() % 1000 + 1;
	double u = (double)n / 1000;
	double t = -lambda * log(u);

	char patente[4];
	patente[0] = rand() % 25 + 65;
	patente[1] = rand() % 25 + 65;
	patente[2] = rand() % 25 + 65;
	patente[3] = '\0';
	std::string str(patente);

	usleep(t * 1000);
	return Auto(str);
}

GeneradorAutos::~GeneradorAutos() {
}

