#include "FifoLectura.h"

FifoLectura::FifoLectura(const std::string nombre) : Fifo(nombre) {
}

FifoLectura::~FifoLectura() {
}

void FifoLectura::abrir() {
	fd = open ( nombre.c_str(),O_RDONLY );
	if(fd==-1){
        throw "No se pudo abrir el fifo";
	}
}

ssize_t FifoLectura::leer(void* buffer,const ssize_t buffsize) const {
	int leido = read ( fd,buffer,buffsize );
	if(leido == -1){
        throw "No se pudo leer del fifo";
	}
	return leido;
}
