/*
 * Constantes.h
 *
 *  Created on: 05/05/2014
 *      Author: agustin
 */

#ifndef CONSTANTES_H_
#define CONSTANTES_H_

#include <string>

class Constantes {
private:
	Constantes();

public:
	//Deben ser archivos existentes de antemano, con permisos de lectura.
	static const std::string SURTIDOR;
	static const std::string TRANSFERENCIA;
	static const std::string CAJA;

	//Rutas de ejecutables
	static const std::string pathEmpleado;
	static const std::string pathJefeEstacion;
	static const std::string pathConsultarCaja;

	//Ruta archivo fifo - Canal a JefeEmpleados
	static const std::string ARCHIVO_FIFO;
	virtual ~Constantes();
};

#endif /* CONSTANTES_H_ */