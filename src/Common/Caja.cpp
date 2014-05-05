#include "Caja.h"
#include <string>
#include "LockSem.h"
using std::string;

Caja::Caja(const string& name, char letra, int initValSem):sem(name,letra,initValSem){
    dinero.crear(name,letra);
    dinero.escribir(0);
}

Caja::Caja(const string& name, char letra):sem(name,letra){
    dinero.crear(name,letra);
}

Caja::~Caja(){
}

void Caja::eliminarSemaforo(){
    sem.eliminar();
}

void Caja::setDinero(unsigned int din){
    LockSem l(sem);
    dinero.escribir(din);
}

unsigned int Caja::consultarCaja(){
    LockSem l(sem);
    return dinero.leer();
}

void Caja::depositar(unsigned int din){
    LockSem l(sem);
    unsigned int d = dinero.leer();
    dinero.escribir(d+din);
}
