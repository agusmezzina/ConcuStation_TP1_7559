//============================================================================
// Name        : ConcuStation.cpp
// Author      : 
// Version     :
// Copyright   :
// Description :
//============================================================================

#include <iostream>
#include "Common/ProcessManager.h"
using namespace std;

int main() {
	cout << "Soy Init. Mi pid es:" << getpid() << endl;
	ProcessManager::run("bin/JefeEstacion", "JefeEstacion");
	return 0;
}
