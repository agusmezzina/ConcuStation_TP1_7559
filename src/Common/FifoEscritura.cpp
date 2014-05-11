#include "FifoEscritura.h"

FifoEscritura::FifoEscritura(const std::string nombre) : Fifo(nombre) {
}

FifoEscritura::~FifoEscritura() {
}

void FifoEscritura::abrir() {
	fd = open ( nombre.c_str(),O_WRONLY );
	if(fd==-1){
        throw "No se pudo abrir el fifo";
	}
}

ssize_t FifoEscritura::escribir(const void* buffer,const ssize_t buffsize) const {
	int escrito = write ( fd,buffer,buffsize );
	//if(escrito==-1){
    //    throw "Error en write";
    //}else if( escrito != buffsize){
    //    throw "Cantidad escrita menor a la indicada";
	//}
	return escrito;
}
