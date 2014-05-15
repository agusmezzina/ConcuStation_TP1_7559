/*
 * ProcessManager.h
 *
 *  Created on: 14/04/2014
 *      Author: agustin
 */

#ifndef PROCESSMANAGER_H_
#define PROCESSMANAGER_H_

#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <errno.h>
#include <string>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

class ProcessManager {
private:
	ProcessManager();
public:
	pid_t static run(const char* path, char* const argv[]);
	void static wait();
	virtual ~ProcessManager();
};

#endif /* PROCESSMANAGER_H_ */
