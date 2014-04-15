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
#include <string>
#include <iostream>

using namespace std;

class ProcessManager {
public:
	ProcessManager();
	void static run(string path, string filename);
	virtual ~ProcessManager();
};

#endif /* PROCESSMANAGER_H_ */
