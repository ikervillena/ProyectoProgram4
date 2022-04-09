#ifndef _RESERVA_H_
#define _RESERVA_H_
#include "../logicaDeDatos/estructuras.h"

//Declaraciones de las funciones dirigidas a gestionar las reservas de la aplicacion.

//Comprueba que la hora de reserva es correcta , ya que solo se puede reservar a en punto.
void horareserva (char* hora);

//Comprueba el numero pistas disponibles a una hora.
int numpist (char*nompist,char*fecha, char*hora);



}
#endif