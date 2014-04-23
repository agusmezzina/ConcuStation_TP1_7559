//============================================================================
// Name        : ConcuStation.cpp
// Author      : 
// Version     :
// Copyright   :
// Description :
//============================================================================

#include <iostream>
#include <string>
#include <sstream>
#include "Common/ProcessManager.h"
#include "Common/Pipe.h"
using namespace std;

int main() {
	cout << "Soy Init. Mi pid es:" << getpid() << endl;

	Pipe canal;

	string result;
	stringstream convert;
	convert << canal.getFdLectura();
	result = convert.str();

	const char* path = "bin/JefeEstacion";
	char* const argv[] = { const_cast<char*>(path), const_cast<char*>(result.c_str()), (char*) 0 };
	ProcessManager::run(path, argv);

	//canal.setearModo(Pipe::ESCRITURA);
	string mensaje = "Hola jefe de estación!";
	canal.escribir ( static_cast<const void*>(mensaje.c_str()),mensaje.size() );

	cout << "CS: Escribí el mensaje: " << mensaje << endl;

	canal.cerrar();

	return 0;
}
