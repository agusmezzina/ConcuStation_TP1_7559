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

class ProcessManager {
private:
	ProcessManager();
public:
	pid_t static run(const char* path, char* const argv[]);
	virtual ~ProcessManager();
};

#endif /* PROCESSMANAGER_H_ */
