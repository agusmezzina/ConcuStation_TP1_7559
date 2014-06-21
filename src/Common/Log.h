#ifndef LOG_H_INCLUDED
#define LOG_H_INCLUDED
#include "LockFile.h"
#include <string>

class Log{
    public:
        Log(const std::string& filename);
        ~Log();
        void setProceso(const std::string& tipoProc);
        void loggear(const std::string& mensaje);
    private:
        std::string procType;
        LockFile lock;
        int fd;
};

#endif // LOG_H_INCLUDED
