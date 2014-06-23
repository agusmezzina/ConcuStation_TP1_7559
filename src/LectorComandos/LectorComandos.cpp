/*
 * LectorComandos.cpp
 *
 *  Created on: 08/05/2014
 *      Author: agustin
 */

#include "LectorComandos.h"

LectorComandos::LectorComandos(){

}

void LectorComandos::consultaCaja(){
	char* const argv[] = { const_cast<char*>(Constantes::pathConsultarCaja.c_str()), (char*) 0 };
	ProcessManager::run(Constantes::pathConsultarCaja.c_str(), argv);
}
void LectorComandos::notificarFin(){
	if(kill(getppid(), SIGTERM) < 0){
		//Loguear error
	}
}

int LectorComandos::run(){
	bool salir = false;
	while(!salir){
		std::string entrada;
		std::cin >> entrada;
		if(entrada == "q")
			salir = true;
		if(entrada == "c")
			consultaCaja();
			//std::cout << "c!" << std::endl;
	}
	notificarFin();
	return 0;
}

LectorComandos::~LectorComandos() {
}

