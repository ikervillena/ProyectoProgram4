#include "../../declaraciones/logicaDePresentacion/visualizar.h"
#include <stdio.h>
#include <stdlib.h>

//Implementaciones de funciones dirigidas a visualizar informacion en pantalla.

void imprimirTitulo(){
    system("cls");
    printf("\n\t\tPADEL STARS\n\n");
}

void imprimirInicio(){
    imprimirTitulo();
    printf("1. Iniciar sesion.\n2. Crear cuenta.\n3. Salir.\n\n");
}

void imprimirMenuSocio(){
    imprimirTitulo();
    printf("MENU:\n\n1. Reservar pista.\n"
    "2. Torneos.\n3. Tienda.\n4. Cerrar sesion.\n5. Salir.\n\n");
}