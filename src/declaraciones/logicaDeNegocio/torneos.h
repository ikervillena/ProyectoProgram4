#ifndef _TORNEOS_H_
#define _TORNEOS_H_
#include "../logicaDeDatos/estructuras.h"

//Declaraciones de las funciones dirigidas a gestionar los torneos de la aplicacion.

//Devuelve un 1 si hay mas inscripciones de las permitidas.
//Devuelve un 0 si hay un numero de inscripciones apropiado para organizar el torneo.
//Devuelve un -1 si no se alcanza el minimo de parejas para organizar un torneo.
int comprobarInscripciones(int codTorneo);

//Reduce el numero de inscripciones hasta el maximo permitido, realizando un sorteo entre los inscritos.
int reducirParticipantes(int codTorneo);

#endif