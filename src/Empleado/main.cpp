/*
 * main.cpp
 *
 *  Created on: 14/04/2014
 *      Author: agustin
 */

#include <unistd.h>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include "../Common/TransferenciaEmpleado.h"
#include "../Common/ControlEmpleados.h"
#include "../Common/Caja.h"
#include "../Common/Surtidor.h"
#include "../Common/Log.h"
using std::cout;
using std::vector;
using std::string;

int main(int argc, char *argv[]) {
    cout << "Soy el empleado. Mi pid es:" << getpid() << std::endl;
    Log log("ConcuStation.log");
    log.loggear("Soy Empleado pid "+ getpid());
    std::fstream file;
    file.open("logEmpleados",std::fstream::out | std::fstream::app);
    file << "Soy el empleado. Mi pid es:" << getpid() << std::endl;
    file.flush();
    static const string SURTIDOR = "./surtidor";
    static const string TRANSFERENCIA = "./transferencia";
    static const string CAJA = "./caja";
	int idEmpleado = atoi(argv[1]);
    int cantSurtidores = atoi(argv[2]);
    //cout << "id: " << idEmpleado << " cantSurtidores: " << cantSurtidores << std::endl;
    file  << "id: " << idEmpleado << " cantSurtidores: " << cantSurtidores << std::endl;
    file.flush();
    TransferenciaEmpleado transf(TRANSFERENCIA,idEmpleado,idEmpleado);
    Caja caja(CAJA,0);
    vector<Surtidor*> surtidores;
    for(int i=0;i<cantSurtidores;i++){
        surtidores.push_back(new Surtidor(SURTIDOR,i,i));
    }
    file << "Inicialice recursos" << std::endl;

    for(int i=0;i<cantSurtidores;i++){
        delete surtidores[i];
    }
    file << "Termine!"<< std::endl;
    file.close();
	return 0;
}


