#ifndef LOCKFILE_H_INCLUDED
#define LOCKFILE_H_INCLUDED

#include <unistd.h>
#include <fcntl.h>
#include <string>

class LockFile{
    public:
        LockFile();
        void setFd(int fd);
        ~LockFile();
        int tomarLock();
        int liberarLock();
    private:
        struct flock fl;
        int fd;
};

#endif // LOCKFILE_H_INCLUDED
