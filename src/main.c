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
    switch (eleccion) {
        case 1:
            iniciarSesion();
            break;
        case 2:
            crearCuenta();
            break;
        default:
            printf("Eleccion incorrecta.");
    }
}