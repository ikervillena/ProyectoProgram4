#ifndef _FECHAS_H_
#define _FECHAS_H_
#include "../logicaDeDatos/estructuras.h"

//Declaraciones de las funciones dirigidas a gestionar las fechas.

//Devuelve un -1 si fec1 < fec2, un 0 si son iguales y un 1 si fec1 > fec2.
int compFecha(Fecha fec1, Fecha fec2);

//Devuelve un char* con la fecha en formato 'dd--mm-aaaa'.
char* textoFecha(Fecha fecha);

#endif