#ifndef TRANSFERENCIAEMPLEADO_H_INCLUDED
#define TRANSFERENCIAEMPLEADO_H_INCLUDED
#include "Semaforo.h"
#include "MemoriaCompartida2.h"
#include "Auto.h"
#include "EmpleadoOcupado.h"
#include <fstream>

class TransferenciaEmpleado{
    public:
        TransferenciaEmpleado(const std::string& name, const char letra, const int id,
                const int initSemMem, const int initSemProd);
        TransferenciaEmpleado(const std::string& name, const char letra, const int id);
        ~TransferenciaEmpleado();
        void eliminarSemaforos();
        void setEmpleado(int pid);
        bool ocuparSiEstaLibre(const Auto& a);
        Auto atenderAuto();
        void terminarAtencion();
    private:
        MemoriaCompartida2<EmpleadoOcupado> mem;
        Semaforo semMemoria;
        Semaforo semProd;
        int pidEmpleado;
};


#endif // TRANSFERENCIAEMPLEADO_H_INCLUDED
