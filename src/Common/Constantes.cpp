/*
 * Constantes.cpp
 *
 *  Created on: 05/05/2014
 *      Author: agustin
 */

#include "Constantes.h"

const std::string Constantes::SURTIDOR = "./surtidor";
const std::string Constantes::TRANSFERENCIA = "./transferencia";
const std::string Constantes::CAJA = "./caja";

/*
const std::string Constantes::pathEmpleado = "bin/Empleado";
const std::string Constantes::pathJefeEstacion = "bin/JefeEstacion";
const std::string Constantes::pathConsultarCaja = "bin/ConsultarCaja";
const std::string Constantes::pathLectorComandos = "bin/LectorComandos";
*/

//PATHS DE PABLO. NO ME LAS BORREN PLEASE, COMENTENLAS
const std::string Constantes::pathEmpleado = "./Empleado/bin/Debug/empleado";
const std::string Constantes::pathJefeEstacion = "./JefeEstacion/bin/Debug/jefeEstacion";
const std::string Constantes::pathConsultarCaja = "./ConsultarCaja/bin/Debug/consultarCaja";
const std::string Constantes::pathLectorComandos = "./LectorComandos/bin/Debug/lectorComandos";


const std::string Constantes::ARCHIVO_FIFO = "/tmp/fifo_init_jefe";

const std::string Constantes::LOG = "./ConcuStation.log";

Constantes::Constantes() {

}

Constantes::~Constantes() {
}

