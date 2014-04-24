//============================================================================
// Name        : ConcuStation.cpp
// Author      : 
// Version     :
// Copyright   :
// Description :
//============================================================================

#include <iostream>
#include <string>
#include <sstream>
#include "Common/ProcessManager.h"
#include "Common/Pipe.h"
#include "Common/Auto.h"
using namespace std;

string getString(int number){
	string result;
	stringstream convert;
	convert << number;
	result = convert.str();
	return result;
}

int main() {
	Pipe canal;

	string fdArg = getString(canal.getFdLectura());
	const char* path = "bin/JefeEstacion";
	char* const argv[] = { const_cast<char*>(path), const_cast<char*>(fdArg.c_str()), (char*) 0 };
	ProcessManager::run(path, argv);

	string patente;
	bool salir = false;

	while(!salir) {
		cin >> patente;
		if(patente == "q")
			salir = true;
		//Limito cadena de entrada para evitar desbordamientos en el canal.
		patente = patente.substr(0, 6);
		canal.escribir ( static_cast<const void*>(patente.c_str()), patente.size() );
	}

	ProcessManager::wait();
	cout << "CS: Final" << endl;
	canal.cerrar();

	return 0;
}
