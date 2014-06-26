/*
 * main.cpp
 *
 *  Created on: 21/06/2014
 *      Author: agustin
 */

#include "AccesoCaja.h"

int main(int argc, char *argv[]){
	char debug = argv[1][0];
	bool modoDebug;
	if(debug == 's')
		modoDebug = true;
	else
		modoDebug = false;

	AccesoCaja acc(modoDebug);
	return acc.run();

}


