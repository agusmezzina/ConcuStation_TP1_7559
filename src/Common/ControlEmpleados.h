#ifndef CONTROLEMPLEADOS_H_INCLUDED
#define CONTROLEMPLEADOS_H_INCLUDED
#include "MemoriaCompartida2.h"
#include "Semaforo.h"
#include <string>

class ControlEmpleados{
    public:
        ControlEmpleados(const std::string& name,char letra,int initValSem);
        ControlEmpleados(const std::string& name,char letra);
        ~ControlEmpleados();
        void setEmpleadosLibres(unsigned int empleadosLibres);
        unsigned int getEmpleadosLibres();
        void ocuparEmpleado();
        void liberarEmpleado();
        void eliminarSemaforo();
    private:
        MemoriaCompartida2<int> empleadosLibres;
        Semaforo sem;
};

#endif // CONTROLEMPLEADOS_H_INCLUDED
