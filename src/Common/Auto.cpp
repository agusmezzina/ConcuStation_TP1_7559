/*
 * Auto.cpp
 *
 *  Created on: 22/04/2014
 *      Author: agustin
 */

#include "Auto.h"

Auto::Auto(std::string patente):patente(patente) {
}

std::string Auto::getPatente(){
	return patente;
}

Auto::~Auto() {

}

