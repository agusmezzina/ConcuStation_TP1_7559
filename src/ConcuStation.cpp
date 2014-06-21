//============================================================================
// Name        : ConcuStation.cpp
// Author      :
// Version     :
// Copyright   :
// Description :
//============================================================================

#include <iostream>
#include "Estacion.h"
#include "GeneradorAutos.h"
#include "Common/Log.h"

int main(){
	int cantEmpleados;
	int cantSurtidores;
	std::cout << "Bienvenido a la ConcuStation" << std::endl;
	std::cout << "Ingrese el nro de empleados" << std::endl;
	std::cin >> cantEmpleados;
	std::cout << "Ingrese el nro de surtidores" << std::endl;
	std::cin >> cantSurtidores;
	Estacion estacion(cantEmpleados,cantSurtidores);
	try{
	estacion.run();
	}
	catch(const char* ex){
			std::cout << ex << std::endl;
		}
}
