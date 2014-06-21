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

int main() {
	//cout << "Soy el consultar caja. Mi pid es:" << getpid() << endl;
	ConsultarCaja cc;
	try{
	return cc.run();
	}
	catch(const char* ex){
		std::cout << ex << std::endl;
	}
}


