/*
 * LectorComandos.cpp
 *
 *  Created on: 08/05/2014
 *      Author: agustin
 */

#include "LectorComandos.h"

LectorComandos::LectorComandos(pid_t unProceso): procesoAsociado(unProceso) {
}

void LectorComandos::notificarConsultaCaja(){
	if(kill(procesoAsociado, SIGINT) < 0){
		//Loguear error
	}
}
void LectorComandos::notificarFin(){

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
	}
	notificarFin();
	return 0;
}

LectorComandos::~LectorComandos() {
	// TODO Auto-generated destructor stub
}

