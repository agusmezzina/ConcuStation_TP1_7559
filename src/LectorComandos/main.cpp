/*
 * main.cpp
 *
 *  Created on: 08/05/2014
 *      Author: agustin
 */

#include "LectorComandos.h"
#include <sstream>

int main(int argc, char *argv[]){

	LectorComandos lector;
	try{
	return lector.run();
	}
	catch(const char* ex){
			std::cout << ex << std::endl;
		}
}


