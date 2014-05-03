#ifndef EMPLEADOOCUPADO_H_INCLUDED
#define EMPLEADOOCUPADO_H_INCLUDED
#include "Auto.h"

class EmpleadoOcupado{
    public:
        EmpleadoOcupado();
        ~EmpleadoOcupado();
        EmpleadoOcupado& operator=(const EmpleadoOcupado& emp);
        Auto getAuto();
        bool estaOcupado();
        void ocupar(const Auto& a);
        void desocupar();
    private:
        bool ocupado;
        Auto a;
};

#endif // EMPLEADOOCUPADO_H_INCLUDED
