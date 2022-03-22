#include "../../declaraciones/logicaDePresentacion/menu.h"
#include <stdio.h>
#include <stdlib.h>

//Implementaciones de las funciones dirigidas a gestionar el menu de la aplicacion.

void iniciarSesion(){
    imprimirTitulo();
    printf("INICIO DE SESION:\n\nUsuario:\t");
    char *usuario = malloc(25 * sizeof(char));
    char *contrasenya = malloc(25 * sizeof(char));
    scanf("%s", usuario);
    printf("\nContrasenya:\t");
    scanf("%s",contrasenya);
    system("cls");
    //Ahora se debe comprobar la contrasenya y pasar a la siguiente ventana.
    printf("%s - %s", usuario, contrasenya);
}