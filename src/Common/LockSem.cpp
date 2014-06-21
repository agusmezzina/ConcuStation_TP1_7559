#include "LockSem.h"

LockSem::LockSem(Semaforo& sem): semaforo(sem){
    semaforo.p();
}

LockSem::~LockSem(){
    semaforo.v();
}
