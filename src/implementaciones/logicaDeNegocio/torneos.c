#include "../../declaraciones/logicaDeNegocio/torneos.h"
#include "../../declaraciones/gestionBD/deleteData.h"
#include "../../declaraciones/gestionBD/getData.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_INSCRIPCIONES 32
#define MIN_INSCRIPCIONES 4

int comprobarInscripciones(int codTorneo) {
    int numInscritos = getNumInscripciones(codTorneo);
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

//Devuelve un 1 si el indice es valido (los indices no se pueden repetir), y un 0 si no lo es.
int indiceValido(int *lista, int tamanyo, int indice) {
    int valido = 1;
    for(int i = 0; i < tamanyo; i++) {
        if(lista[i] == indice) valido = 0;
    }
    return valido;
}

//Devuelve una lista de indices no repetidos y limitados por el numero maximo provisto por parametro.
int *elegirIndices(int numIndices, int numMax) {
    int contador = 0;
    int *indicesElegidos = (int *) malloc(numIndices * sizeof(int));
    while(contador < numIndices) {
        int indice = rand() % (numMax + 1);
        if(indiceValido(indicesElegidos, contador, indice) == 1){
            indicesElegidos[contador] = indice;
            contador++;
        }
    }
    return indicesElegidos;
}

int reducirParticipantes(int codTorneo) {
    int *parejasInscritas = getInscripciones(codTorneo);
    int numInscritos = getNumInscripciones(codTorneo);
    int numSobrantes = numInscritos - MAX_INSCRIPCIONES;
    int *indices = elegirIndices(numSobrantes, numInscritos);
    for(int i = 0; i < numSobrantes; i++) {
        int codParejaBorrada = parejasInscritas[indices[i]];
        borrarInscripcion(codTorneo, codParejaBorrada);
    }
}