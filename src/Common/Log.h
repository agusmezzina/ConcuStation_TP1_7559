#ifndef LOG_H_INCLUDED
#define LOG_H_INCLUDED
#include "Semaforo.h"
#include <fstream>
#include <iostream>

class Log{
    public:
        Log(const std::string& filename, int initValSem);
        Log(const std::string& filename);
        ~Log();
        void eliminarSemaforo();
        void loggear(const std::string& mensaje);
    private:
        std::string fileName;
        std::fstream file;
        Semaforo sem;
};

#endif // LOG_H_INCLUDED
