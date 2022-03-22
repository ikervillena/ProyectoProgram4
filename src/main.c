#include "declaraciones/logicaDePresentacion/visualizar.h"
#include "declaraciones/logicaDePresentacion/menu.h"
#include <stdio.h>
#include <stdlib.h>

//Main de la aplicacion.

void main(void){
    imprimirInicio();
    int eleccion;
    printf("Escoge una opcion:\t");
    scanf("%i", &eleccion);
    if(eleccion == 1){
        iniciarSesion();
    }
}