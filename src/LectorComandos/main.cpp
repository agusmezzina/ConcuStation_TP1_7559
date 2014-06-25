/*
 * main.cpp
 *
 *  Created on: 08/05/2014
 *      Author: agustin
 */

#include "LectorComandos.h"
#include <sstream>

int main(int argc, char *argv[]){
	char debug = argv[1][0];
	bool modoDebug;
	if(debug == 's')
		modoDebug = true;
	else
		modoDebug = false;

	LectorComandos lector(modoDebug);
	try{
	return lector.run();
	}
	catch(const char* ex){
			std::cout << ex << std::endl;
		}
}


