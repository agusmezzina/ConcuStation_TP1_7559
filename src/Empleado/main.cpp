/*
 * main.cpp
 *
 *  Created on: 14/04/2014
 *      Author: agustin
 */

#include <sstream>
#include <iostream>
#include "Empleado.h"

int main(int argc, char *argv[]) {

	std::istringstream ss(argv[1]);
	int idEmpleado;
	if (!(ss >> idEmpleado))
		std::cerr << "Invalid number " << argv[1] << std::endl;

	std::istringstream ss2(argv[2]);
	int cantSurtidores;
	if (!(ss2 >> cantSurtidores))
		std::cerr << "Invalid number " << argv[2] << std::endl;

	char debug = argv[3][0];
	bool modoDebug;
	if(debug == 's')
		modoDebug = true;
	else
		modoDebug = false;

	Empleado empleado(idEmpleado, cantSurtidores, modoDebug);
	try{
	return empleado.run();
	}
	catch(const char* ex){
			std::cout << ex << std::endl;
		}
}
