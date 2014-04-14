/*
 * main.cpp
 *
 *  Created on: 14/04/2014
 *      Author: agustin
 */

#include <unistd.h>
#include <iostream>
using namespace std;

int main() {
	cout << "Soy el jefe de estación. Mi pid es:" << getpid() << endl;
	return 0;
}


