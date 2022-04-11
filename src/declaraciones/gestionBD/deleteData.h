#ifndef _DELETEDATA_H_
#define _DELETEDATA_H_

//Borra un torneo de la base de datos.
int borrarTorneo(int codTorneo);

//Borra la inscripcion de una pareja al torneo.
int borrarInscripcion(int codTorneo, int codPareja);

#endif