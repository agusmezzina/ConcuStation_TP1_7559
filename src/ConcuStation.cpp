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
	char debug;
	std::cout << "Bienvenido a la ConcuStation" << std::endl;
	std::cout << "Ingrese el nro de empleados" << std::endl;
	std::cin >> cantEmpleados;
	std::cout << "Ingrese el nro de surtidores" << std::endl;
	std::cin >> cantSurtidores;
	std::cout << "¿Desea ejecutar en modo Debug? (s/n)" << std::endl;
	std::cin >> debug;
	bool modoDebug;
	if(debug == 's')
		modoDebug = true;
	else
		modoDebug = false;
	Estacion estacion(cantEmpleados,cantSurtidores, modoDebug);
	try{
	std::cout << "Simulación iniciada!" << std::endl;
	estacion.run();
	std::cout << "Simulación finalizada!" << std::endl;
	}
	catch(const char* ex){
			std::cout << ex << std::endl;
		}
}


