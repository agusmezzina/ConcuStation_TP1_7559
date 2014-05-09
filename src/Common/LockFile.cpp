#include "LockFile.h"

LockFile::LockFile(){
    this->fl.l_type=F_WRLCK;
    this->fl.l_whence=SEEK_SET;
    this->fl.l_start=0;
    this->fl.l_len=0;
}

LockFile::~LockFile(){
}

void LockFile::setFd(int fd){
    this->fd=fd;
}

int LockFile::tomarLock(){
    this->fl.l_type=F_WRLCK;
    return fcntl(fd,F_SETLKW,&fl);
}

int LockFile::liberarLock(){
    this->fl.l_type=F_UNLCK;
    return fcntl(fd,F_SETLK,&fl);
}
