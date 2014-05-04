/*
 * ProcessManager.cpp
 *
 *  Created on: 14/04/2014
 *      Author: agustin
 */

#include "ProcessManager.h"
#include <iostream>
ProcessManager::ProcessManager() {
}

pid_t ProcessManager::run(const char* path, char* const argv[]){
	pid_t id = fork ();
        if(id<0){
            std::cout << "BARDIO EL FORK";
            throw "JOJO";
        }else if ( id == 0 ) {
			execv(path, argv);
			std::cout << "Bardio el exec";
            exit(1);
		} else {
			return id;
		}
}

void ProcessManager::wait(){
	::wait(NULL);
}

ProcessManager::~ProcessManager() {
}

