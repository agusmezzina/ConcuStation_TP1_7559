/*
 * LectorComandos.cpp
 *
 *  Created on: 08/05/2014
 *      Author: agustin
 */

#include "LectorComandos.h"

LectorComandos::LectorComandos(){

}

void LectorComandos::notificarConsultaCaja(){
	if(kill(getppid(), SIGINT) < 0){
		//Loguear error
	}
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
			notificarConsultaCaja();
			//std::cout << "c!" << std::endl;
	}
	notificarFin();
	return 0;
}

LectorComandos::~LectorComandos() {
	// TODO Auto-generated destructor stub
}

