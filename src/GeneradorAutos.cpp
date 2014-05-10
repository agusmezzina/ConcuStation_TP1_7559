/*
 * GeneradorAutos.cpp
 *
 *  Created on: 09/05/2014
 *      Author: agustin
 */

#include "GeneradorAutos.h"
#include <unistd.h>

GeneradorAutos::GeneradorAutos(int media): lambda(media) {
	srand(time(NULL));
	patActual[0]='A';
	patActual[1]='A';
	patActual[2]='A';
	patActual[3]='\0';
}

Auto GeneradorAutos::next(){
	int n = rand() % 1000 + 1;
	double u = (double)n / 1000;
	double t = -lambda * log(u);

	//char patente[4];
	/*patente[0] = rand() % 25 + 65;
	patente[1] = rand() % 25 + 65;
	patente[2] = rand() % 25 + 65;
	patente[3] = '\0';*/

	// LO CAMBIE PARA QUE LAS GENERE EN ORDEN PORQUE ES MAS FACIL DEBUGGEAR
	if(patActual[2] != 'Z'){
        patActual[2]++;
	}else{
        patActual[2]='A';
        if(patActual[1]!='Z'){
            patActual[1]++;
        }else{
            patActual[1]='A';
            if(patActual[0]!='Z'){
                patActual[0]++;
            }else{
                patActual[0]='A';
            }
        }
	}
	std::string str(patActual);

	usleep(t * 1000);
	return Auto(str);
}

GeneradorAutos::~GeneradorAutos() {
}

