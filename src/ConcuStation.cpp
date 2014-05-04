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
#include "Common/TransferenciaEmpleado.h"
#include "Common/ControlEmpleados.h"
#include "Common/Caja.h"
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
    static const string SURTIDOR = "./surtidor";
    static const string TRANSFERENCIA = "./transferencia";
    static const string CAJA = "./caja";

    //inicializo surtidores
    vector<Surtidor*> surtidores;
    for(char i=0;i<cantSurtidores;i++){
        surtidores.push_back(new Surtidor(SURTIDOR,i,i,1));
    }
    //No los destruyo nunca!! Hay que arreglar eso

    //Incializo el semaforo general para los surtidores
    Semaforo semSurtidores(SURTIDOR,cantSurtidores,cantSurtidores);

    //Incializo los sectores de transferencia a empleados (mem compartida + semaforo de proteccion
    // + semaforo para productor-consumidor
    vector<TransferenciaEmpleado*> transferencias;
    for(char i=0;i<cantEmpleados;i++){
        transferencias.push_back(new TransferenciaEmpleado(TRANSFERENCIA,i,0,1,0));
    }
    ControlEmpleados controlEmpleados(TRANSFERENCIA,cantEmpleados,1);
    controlEmpleados.setEmpleadosLibres(cantEmpleados);

    //Creo e inicializo la Caja (mem compartida + semaforo)
    Caja caja(CAJA,0,1);
    caja.setDinero(0);

    //creo el fifo para la comunicacion jefeEstacion-init
    static const string ARCHIVO_FIFO = "/tmp/fifo_init_jefe";
	FifoEscritura canal(ARCHIVO_FIFO);

    //lanzo jefeEstacion

    //lanzo Empleados

    //Genero autos y los paso


/*
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
*/
    //Libero surtidores
    for(char i=0;i<cantSurtidores;i++){
        surtidores[i]->eliminarSemaforo();
        delete surtidores[i];
    }
    semSurtidores.eliminar();

    //Libero las transferencias
    for(char i=0;i<cantEmpleados;i++){
        transferencias[i]->eliminarSemaforos();
        delete transferencias[i];
    }
    controlEmpleados.eliminarSemaforo();

    //Libero la caja
    caja.eliminarSemaforo();

	return 0;
}
