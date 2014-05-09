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
	std::fstream file;
	file.open("logTransferencia",std::fstream::out | std::fstream::app);
	file << "[PROCESO " << this->pidEmpleado << "] Inicio método" << std::endl;
	file.flush();
	LockSem l(semMemoria);
	file << "[PROCESO " << this->pidEmpleado << "] Tomé memoria" << std::endl;
	file.flush();
	EmpleadoOcupado emp = mem.leer();
	if(! emp.estaOcupado()){
		file << "[PROCESO " << this->pidEmpleado << "] Libre!" << std::endl;
		file.flush();
		emp.ocupar(a);
		mem.escribir(emp);
		semProd.v();
		file << "[PROCESO " << this->pidEmpleado << "] Hice signal" << std::endl;
		file.flush();
		file.close();
		return true;
	}
	file << "[PROCESO " << this->pidEmpleado << "] Ocupado!" << std::endl;
	return false;
}

Auto TransferenciaEmpleado::atenderAuto(){
	std::fstream file;
	file.open("logTransferencia",std::fstream::out | std::fstream::app);
	file << "[PROCESO " << this->pidEmpleado << "] Hago wait para atender" << std::endl;
	file.flush();
    semProd.p();
    file << "[PROCESO " << this->pidEmpleado << "] Puedo atender" << std::endl;
    file.flush();
    file.close();
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
