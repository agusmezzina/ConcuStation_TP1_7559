/*
 * Auto.h
 *
 *  Created on: 22/04/2014
 *      Author: agustin
 */

#ifndef AUTO_H_
#define AUTO_H_

#define	NORMAL	2
#define	VIP	1
#define PRIORIDAD -2

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



typedef struct autoStruct {
	long mtype;
	char patente[4];
} autoStruct;


#endif /* AUTO_H_ */
