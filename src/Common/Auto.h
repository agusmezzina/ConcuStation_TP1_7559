/*
 * Auto.h
 *
 *  Created on: 22/04/2014
 *      Author: agustin
 */

#ifndef AUTO_H_
#define AUTO_H_

#include <string>

class Auto {
private:
	std::string patente;
public:
	Auto(std::string patente);
	std::string getPatente();
	virtual ~Auto();
};

#endif /* AUTO_H_ */
