#include "TransferenciaEmpleado.h"
#include "EmpleadoOcupado.h"
#include "LockSem.h"
using std::string;

TransferenciaEmpleado::TransferenciaEmpleado(const string& name, const char letra, const int id,
                const int initSemMem, const int initSemProd) :semMemoria(name,letra,initSemMem),
                        semProd(name, letra+128,initSemProd), pidEmpleado(id){
        mem.crear(name,letra);
        EmpleadoOcupado emp;
        mem.escribir(emp);
}

TransferenciaEmpleado::TransferenciaEmpleado(const string& name, const char letra, const int id) :
        semMemoria(name,letra),semProd(name, letra+128), pidEmpleado(id){
        mem.crear(name,letra);
}

TransferenciaEmpleado::~TransferenciaEmpleado(){
}

void TransferenciaEmpleado::setEmpleado(int pid){
    this->pidEmpleado=pid;
}

void TransferenciaEmpleado::eliminarSemaforos(){
    semProd.eliminar();
    semMemoria.eliminar();
}

bool TransferenciaEmpleado::ocuparSiEstaLibre(const Auto& a){
        LockSem l(semMemoria);
        EmpleadoOcupado emp = mem.leer();
        if(! emp.estaOcupado()){
            emp.ocupar(a);
            mem.escribir(emp);
            semProd.v();
            return true;
        }
        return false;
}

Auto TransferenciaEmpleado::atenderAuto(){
    semProd.p();
    LockSem l(semMemoria);
    EmpleadoOcupado emp = mem.leer();
    return emp.getAuto();
}

void TransferenciaEmpleado::terminarAtencion(){
    LockSem l(semMemoria);
    EmpleadoOcupado emp = mem.leer();
    emp.desocupar();
    mem.escribir(emp);
}
