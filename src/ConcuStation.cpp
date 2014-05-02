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
#include <vector>
#include "Common/ProcessManager.h"
#include "Common/FifoEscritura.h"
#include "Common/Surtidor.h"
using std::string;
using std::stringstream;
using std::cout;
using std::cin;
using std::endl;
using std::vector;

string getString(int number){
	string result;
	stringstream convert;
	convert << number;
	result = convert.str();
	return result;
}

int main(int argc, char* argv[]) {
    int cantEmpleados;
    int cantSurtidores;

    cout << "Bienvenido a la ConcuStation" << endl;
    cout << "Ingrese el nro de empleados" << endl;
    cin >> cantEmpleados;
    cout << "Ingrese el nro de surtidores" << endl;
    cin >> cantSurtidores;
    //UN ARCHIVO CON PERMISO DE LECTURO Y QUE LO ENCUENTRE
    static const string SURTIDOR = "./ConcuStation.log";

    //inicializo surtidores
    vector<Surtidor*> surtidores;
    for(char i=0;i<cantSurtidores;i++){
        surtidores.push_back(new Surtidor(SURTIDOR,i,i,1));
    }
    //No los destruyo nunca!! Hay que arreglar eso


	static const string ARCHIVO_FIFO = "/tmp/fifo_init_jefe";
	FifoEscritura canal(ARCHIVO_FIFO);

	const char* path = "bin/JefeEstacion";
	char* const argvE[] = { const_cast<char*>(path), (char*) 0 };
	ProcessManager::run(path, argvE);

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
