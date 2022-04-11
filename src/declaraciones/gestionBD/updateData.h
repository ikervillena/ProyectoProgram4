#ifndef _UPDATEDATA_H_
#define _UPDATEDATA_H_

//Cierra el periodo de inscripcion de un torneo (cod_par_gan = 0).
int cierreInscripciones(int codTorneo);


//Actualiza la pareja ganadora de un torneo guardado en la BD.
int actualizarGanador(int codTorneo, int codPareja);

#endif