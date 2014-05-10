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
	return cc.run();
}


