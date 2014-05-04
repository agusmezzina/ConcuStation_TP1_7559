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
#include <fstream>
#include <vector>
#include "Common/ProcessManager.h"
#include "Common/FifoEscritura.h"
#include "Common/Surtidor.h"
#include "Common/TransferenciaEmpleado.h"
#include "Common/ControlEmpleados.h"
#include "Common/Caja.h"
#include "Common/Log.h"
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
    Log log("ConcuStation.log",1);
    std::fstream file;
    file.open("logPrincipal",std::fstream::out | std::fstream::app);
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
    cout << "Paso1" << endl;
    log.loggear("Inicializando surtidores \n");
    file << "Inicializando surtidores";
    file.flush();
    vector<Surtidor*> surtidores;
    for(char i=0;i<cantSurtidores;i++){
        surtidores.push_back(new Surtidor(SURTIDOR,i,i,1));
    }
    //Incializo el semaforo general para los surtidores
    Semaforo semSurtidores(SURTIDOR,cantSurtidores,cantSurtidores);

    //Incializo los sectores de transferencia a empleados (mem compartida + semaforo de proteccion
    // + semaforo para productor-consumidor
    vector<TransferenciaEmpleado*> transferencias;
    for(char i=0;i<cantEmpleados;i++){
        transferencias.push_back(new TransferenciaEmpleado(TRANSFERENCIA,i,i,1,0));
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
    const char* pathEmpleado = "./Empleado/bin/Debug/empleado";
    std::stringstream ss2;
    ss2 << cantSurtidores;
    std::string cant = ss2.str();
    for(int i=0;i<cantEmpleados;i++){
        std::stringstream ss;
        ss << i;
        std::string id = ss.str();
        char* const argvE[] = { const_cast<char*>(pathEmpleado),(char*)id.c_str(), (char*)cant.c_str(),NULL};
        file << "Lanzo empleado " << i << std::endl;
        file.flush();
        ProcessManager::run(pathEmpleado, argvE);

    }

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
    file << "Destruyo recursos" << std::endl;
    file.flush();
    for (int i=0;i<cantEmpleados;i++){
        wait(NULL);
    }
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
    log.eliminarSemaforo();
	file.close();
	return 0;
}
