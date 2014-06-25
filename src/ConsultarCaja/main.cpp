/*
 * main.cpp
 *
 *  Created on: 14/04/2014
 *      Author: agustin
 */

#include <unistd.h>
#include <iostream>
#include "ConsultarCaja.h"
using namespace std;

int main(int argc, char *argv[]) {
	//cout << "Soy el consultar caja. Mi pid es:" << getpid() << endl;
	char debug = argv[1][0];
	bool modoDebug;
	if(debug == 's')
		modoDebug = true;
	else
		modoDebug = false;

	ConsultarCaja cc(modoDebug);
	try{
	return cc.run();
	}
	catch(const char* ex){
		std::cout << ex << std::endl;
	}
}


