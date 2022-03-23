#include "../../declaraciones/logicaDePresentacion/menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void crearCuenta(){
    imprimirTitulo();
    printf("CREACION DE CUENTA:\n\nUsuario:\t");
    char *usuario = malloc(20*sizeof(char));
    int usuarioCorrecto = 0;
    while(!usuarioCorrecto){
        scanf("%s", usuario);
        //Hay que cambiar la sentencia del if.
        if(strcmp(usuario, "ikervillena") == 0){
            printf("El usuario ya existe, elige otro por favor.\nUsuario:\t");
        } else{
            usuarioCorrecto = 1;
        }
    }
    char *nombre = malloc(20*sizeof(char));
    char *apellido = malloc(20*sizeof(char));
    printf("\nNombre:\t");
    scanf("%s", nombre);
    printf("\nApellido\t");
    scanf("%s", apellido);
    system("cls");
    printf("%s", usuario);
    //Sin terminar
}