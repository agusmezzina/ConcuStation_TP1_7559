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
	static const std::string COLA;

	//Rutas de ejecutables
	static const std::string pathEmpleado;
	static const std::string pathJefeEstacion;
	static const std::string pathConsultarCaja;
	static const std::string pathLectorComandos;
	static const std::string pathAccesoCaja;

	//Ruta archivo fifo - Canal a JefeEmpleados
	static const std::string ARCHIVO_FIFO;
	static const std::string LOG;
	virtual ~Constantes();
};

#endif /* CONSTANTES_H_ */
