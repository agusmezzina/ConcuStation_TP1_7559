#ifndef LOCKSEM_H_INCLUDED
#define LOCKSEM_H_INCLUDED
#include "Semaforo.h"

class LockSem{
    public:
        LockSem(Semaforo& sem);
        ~LockSem();
    private:
        Semaforo& semaforo;
};

#endif // LOCKSEM_H_INCLUDED
