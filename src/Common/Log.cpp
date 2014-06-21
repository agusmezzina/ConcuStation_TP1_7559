#include "Log.h"
#include "LockSem.h"
#include <unistd.h>
#include <string>
#include <sstream>
#include <ctime>
using std::string;

Log::Log(const string& file){
	fd = open (file.c_str(),O_CREAT|O_WRONLY,0777);
	lock.setFd(fd);
}

Log::~Log(){
    close(fd);
}

void Log::setProceso(const string& proc){
    procType = proc;
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
    lock.tomarLock();
    std::stringstream ss;
    ss << getTime() << " - " << procType <<" - " << getpid() << " - ";
    ss << mensaje << std::endl;
    std::string s = ss.str();
    lseek(fd,0,SEEK_END);
    write(fd,s.c_str(),s.length());
    lock.liberarLock();
}
