#ifndef SURTIDOR_H_INCLUDED
#define SURTIDOR_H_INCLUDED
#include "Semaforo.h"
#include "MemoriaCompartida2.h"
#include <sys/types.h>
class Surtidor {
    public:
        Surtidor(const std::string& name, const char letra, const int id,
                const int initValSem);
        Surtidor(const std::string& name, const char letra, const int id);
        ~Surtidor();
        void eliminarSemaforo();
        bool ocuparSiEstaLibre(pid_t pid);
        void liberarSurtidor();
    private:
        std::string name;
        char letra;
        int id;
        MemoriaCompartida2<int> mem;
        Semaforo sem;

};


#endif // SURTIDOR_H_INCLUDED
