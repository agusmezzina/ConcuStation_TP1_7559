#include "Log.h"
#include "LockSem.h"
#include <unistd.h>
#include <string>
#include <ctime>
using std::string;

Log::Log(const string& file, int initValSem): fileName(file),sem(file,0,initValSem){
	this->file.open(file.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
}

Log::Log(const string& file): fileName(file),sem(file,0){
	this->file.open(file.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
}

void Log::eliminarSemaforo(){
    sem.eliminar();
}

Log::~Log(){
    this->file.close();
}

const std::string getTime(){
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf,sizeof(buf),"%Y-%m-%d.%X",&tstruct);
    return buf;
}

void Log::loggear(const string& mensaje){
    LockSem l(sem);
    file << getTime() << " - " << getpid() << " - ";
    file << mensaje << std::endl;
}
