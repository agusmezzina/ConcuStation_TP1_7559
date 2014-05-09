/*
 * main.cpp
 *
 *  Created on: 08/05/2014
 *      Author: agustin
 */

#include "LectorComandos.h"
#include <sstream>

int main(int argc, char *argv[]){

	std::istringstream ss(argv[1]);
	int pid;
	if (!(ss >> pid))
		std::cerr << "Invalid number " << argv[1] << std::endl;

	LectorComandos lector(pid);
	return lector.run();
}


