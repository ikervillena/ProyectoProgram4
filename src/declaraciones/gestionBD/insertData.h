#ifndef _INSERTDATA_H_
#define _INSERTDATA_H_
#include "../logicaDeDatos/estructuras.h"

//Inserta un torneo en la base de datos.
int insertarTorneo(Fecha fecha);

//Inserta una compra en la base de datos. 
int insertCompra(int codCompra, Usuario u, Articulo a, int cantidad, char* f);

//Inserta una reserva en la base de datos.
int insertReserva(int codReserva, Usuario u,int numpista, char* fecha, char* hora, int precio);

#endif