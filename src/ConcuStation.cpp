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
#include "Common/FifoEscritura.h"
using namespace std;

string getString(int number){
	string result;
	stringstream convert;
	convert << number;
	result = convert.str();
	return result;
}

int main() {
	static const string ARCHIVO_FIFO = "/tmp/fifo_init_jefe";
	FifoEscritura canal(ARCHIVO_FIFO);

	const char* path = "bin/JefeEstacion";
	char* const argv[] = { const_cast<char*>(path), (char*) 0 };
	ProcessManager::run(path, argv);

	string patente;
	bool salir = false;
	canal.abrir();

	while(!salir) {
		cin >> patente;
		if(patente == "q")
			salir = true;
		//Limito cadena de entrada para evitar desbordamientos en el canal.
		patente = patente.substr(0, 6);
		canal.escribir ( static_cast<const void*>(patente.c_str()), patente.size() );
		cout << "[Init] Escribí la patente " << patente << endl;
	}

	ProcessManager::wait();
	cout << "[Init] Final" << endl;
	canal.cerrar();
	canal.eliminar();

	return 0;
}
