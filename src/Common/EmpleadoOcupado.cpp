#include "EmpleadoOcupado.h"

EmpleadoOcupado::EmpleadoOcupado() : ocupado(false),a("000") {
}

EmpleadoOcupado::~EmpleadoOcupado(){
}

EmpleadoOcupado& EmpleadoOcupado::operator=(const EmpleadoOcupado& emp){
    this->ocupado=emp.ocupado;
    this->a=emp.a;
    return *this;
}

bool EmpleadoOcupado::estaOcupado(){
    return ocupado;
}

void EmpleadoOcupado::ocupar(const Auto& a){
    this->a=a;
    ocupado=true;
}

void EmpleadoOcupado::desocupar(){
    ocupado=false;
}

Auto EmpleadoOcupado::getAuto(){
    return a;
}
