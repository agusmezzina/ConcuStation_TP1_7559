/*
 * ProcessManager.cpp
 *
 *  Created on: 14/04/2014
 *      Author: agustin
 */

#include "ProcessManager.h"

ProcessManager::ProcessManager() {
}

pid_t ProcessManager::run(const char* path, char* const argv[]){
	pid_t id = fork ();

		if ( id == 0 ) {
			int result = execv(path, argv);
			return result;

		} else {
			return id;
		}
}

void ProcessManager::wait(){
	::wait(NULL);
}

ProcessManager::~ProcessManager() {
}

