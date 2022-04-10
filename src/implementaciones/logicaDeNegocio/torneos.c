#include "../../declaraciones/logicaDeNegocio/torneos.h"
#include "../../declaraciones/gestionBD/getData.h"
#include <string.h>
#include <stdio.h>

#define MAX_INSCRIPCIONES 32
#define MIN_INSCRIPCIONES 4

int comprobarInscripciones(int codTorneo) {
    char sql[] = "SELECT * from TORNEO where cod_torneo = ";
    char str[5];
  	sprintf(str, "%d", codTorneo);
    strcat(sql, str);
    int numInscritos = getNumFilas(sql);
    if(numInscritos < MIN_INSCRIPCIONES) {
        return -1;
    } else{
        if(numInscritos < MAX_INSCRIPCIONES){
            return 0;
        } else{
            return 1;
        }
    }
}