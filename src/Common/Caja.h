#ifndef CAJA_H_INCLUDED
#define CAJA_H_INCLUDED
#include "MemoriaCompartida2.h"
#include "Semaforo.h"
#include <string>

class Caja{
    public:
        Caja(const std::string& name, char letra, int initValSem);
        Caja(const std::string& name, char letra);
        ~Caja();
        void setDinero(unsigned int dinero);
        unsigned int consultarCaja();
        void depositar(unsigned int dinero);
        void eliminarSemaforo();
    private:
        MemoriaCompartida2<unsigned int> dinero;
        Semaforo sem;
};


#endif // CAJA_H_INCLUDED
