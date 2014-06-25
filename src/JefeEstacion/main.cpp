/*
 * main.cpp
 *
 *  Created on: 14/04/2014
 *      Author: agustin
 */

#include <sstream>
#include <iostream>
#include "JefeEstacion.h"
using namespace std;

int main(int argc, char *argv[]){
	std::istringstream ss(argv[1]);
	int cantEmpleados;
	if (!(ss >> cantEmpleados))
		std::cerr << "Invalid number " << argv[1] << std::endl;

	char debug = argv[2][0];
	bool modoDebug;
	if(debug == 's')
		modoDebug = true;
	else
		modoDebug = false;

	JefeEstacion jefe(cantEmpleados, modoDebug);
	try{
	return jefe.run();
	}
	catch(const char* ex){
			std::cout << ex << std::endl;
		}
}


