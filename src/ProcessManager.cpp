/*
 * ProcessManager.cpp
 *
 *  Created on: 14/04/2014
 *      Author: agustin
 */

#include "ProcessManager.h"
using namespace std;

ProcessManager::ProcessManager() {
	// TODO Auto-generated constructor stub

}

void ProcessManager::run(string binary){
	pid_t id = fork ();

		if ( id == 0 ) {

			execl(binary.c_str(), (char*)0);

		} else {

			cout << "Padre: Hola, soy el proceso padre.  Mi process ID es " << getpid() << endl;
			cout << "Padre: El process ID de mi hijo es " << id << endl;

			exit ( 0 );
		}
}

ProcessManager::~ProcessManager() {
	// TODO Auto-generated destructor stub
}

