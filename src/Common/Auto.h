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
	char patente[4];
public:
	Auto(std::string patente);
	Auto(const Auto& a);
	Auto& operator=(const Auto& a);
	std::string getPatente();
	virtual ~Auto();
};

#endif /* AUTO_H_ */
