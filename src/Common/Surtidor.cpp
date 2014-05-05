#include "Surtidor.h"
#include "LockSem.h"
using std::string;

Surtidor::Surtidor(const string& name, const char letra, const int id,
                const int initValSem) : name(name),letra(letra),id(id),
                                sem(name,letra,initValSem){

        mem.crear(name,letra);
        mem.escribir(0);
}

Surtidor::Surtidor(const string& name, const char letra, const int id):
                        name(name),letra(letra),id(id),sem(name,letra){
        mem.crear(name,letra);
}

Surtidor::~Surtidor(){
}

void Surtidor::eliminarSemaforo(){
    sem.eliminar();
}

bool Surtidor::ocuparSiEstaLibre(int pid){
        LockSem l(sem);
        if(! mem.leer()){
            mem.escribir(pid);
            return true;
        }
        return false;
}


