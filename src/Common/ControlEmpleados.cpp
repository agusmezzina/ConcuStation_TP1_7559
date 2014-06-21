#include "ControlEmpleados.h"
#include "LockSem.h"
using std::string;

ControlEmpleados::ControlEmpleados(const string& name, char letra, int initValSem):
                    sem(name,letra,initValSem){
        empleadosLibres.crear(name,letra);
        empleadosLibres.escribir(0);
}

ControlEmpleados::ControlEmpleados(const string& name, char letra): sem(name,letra){
    empleadosLibres.crear(name,letra);
}

ControlEmpleados::~ControlEmpleados(){
}

void ControlEmpleados::eliminarSemaforo(){
    sem.eliminar();
}

void ControlEmpleados::setEmpleadosLibres(unsigned int emp){
    LockSem l(sem);
    empleadosLibres.escribir(emp);
}

unsigned int ControlEmpleados::getEmpleadosLibres(){
    LockSem l(sem);
    unsigned int emp = empleadosLibres.leer();
    return emp;
}

void ControlEmpleados::ocuparEmpleado(){
    LockSem l(sem);
    unsigned int emp = empleadosLibres.leer();
    empleadosLibres.escribir(emp-1);
}

void ControlEmpleados::liberarEmpleado(){
    LockSem l(sem);
    unsigned int emp = empleadosLibres.leer();
    empleadosLibres.escribir(emp+1);
}
