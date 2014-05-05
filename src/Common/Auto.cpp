/*
 * Auto.cpp
 *
 *  Created on: 22/04/2014
 *      Author: agustin
 */

#include "Auto.h"
#include "string.h"

Auto::Auto(std::string patente){
    strncpy(this->patente,patente.c_str(),3);
    this->patente[3] = '\0';
}

Auto::Auto(const Auto& a){
    strncpy(this->patente,a.patente,3);
    this->patente[3] = '\0';
}

Auto& Auto::operator=(const Auto& a){
    strncpy(this->patente,a.patente,3);
    this->patente[3] = '\0';
    return *this;
}

std::string Auto::getPatente(){
	return patente;
}

Auto::~Auto() {

}

