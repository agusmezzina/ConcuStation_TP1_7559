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

pid_t ProcessManager::run(const char* path, char* const argv[]){
	pid_t id = fork ();

		if ( id == 0 ) {

			int result = execv(path, argv);
			//cout << result << endl;
			//cout << errno << endl;
			return result;

		} else {
			return id;
		    //cout << "Padre: Hola, soy el proceso padre.  Mi process ID es " << getpid() << endl;
			//cout << "Padre: El process ID de mi hijo es " << id << endl;
			//exit ( 0 );
		}
}

ProcessManager::~ProcessManager() {
	// TODO Auto-generated destructor stub
}

