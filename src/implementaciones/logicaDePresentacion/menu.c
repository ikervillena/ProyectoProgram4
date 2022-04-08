#include "../../declaraciones/logicaDePresentacion/menu.h"
#include "../../declaraciones/gestionBD/getData.h"
#include "../../declaraciones/gestionBD/insertData.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Implementaciones de las funciones dirigidas a gestionar el menu de la aplicacion.

void menuPrincipal(){
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
        default: ;
            system("cls");
            printf("Fin.\n");
    }
}

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
    if(comprobarUsuario(usuario, contrasenya) == 1){
        printf("Contrasenya correcta.\nSus datos son los siguientes:\n\n");
        Usuario *user = getUsuario(usuario);
        if(user->esSocio == 1) {
            menuSocio(*user);
        } else{
            imprimirDatosUsuario(*user);
            //MenuNoSocio(*user);
        }
        
    } else{
        if(comprobarAdministrador(usuario, contrasenya) == 1){
            menuAdmin();
        } else{
            printf("La contrasenya no es valida.\n");
        }
    }
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

void crearTorneo(){
    imprimirTitulo();
    int dia, mes, anyo;
    int eleccionCorrecta = 0;
    printf("CREAR TORNEO:\n\nEscoge la fecha del torneo.\n\nDia:\t");
    while (eleccionCorrecta == 0){
        scanf("%i", &dia);
        printf("\nMes:\t");
        scanf("%i", &mes);
        printf("\nAnyo:\t");
        scanf("%i", &anyo);
        Fecha fecha = {anyo, mes, dia};
        if(fechaCogida(fecha) == 0) {
            eleccionCorrecta = 1;
            insertarTorneo(fecha);
            menuAdmin();
        } else{
            printf("\nYa hay un torneo previsto para esa fecha, escoge otra por favor.\n\nDia:\t");
        }
    }
}

void menuAdmin(){
    imprimirMenuAdmin();
    int eleccion;
    int eleccionCorrecta = 0;
    printf("Escoge una opcion:\t");
    scanf("%i", &eleccion);
    fflush(stdin);
    while(eleccionCorrecta == 0) {
        eleccionCorrecta = 1;
        switch (eleccion) {
            case 1:
                crearTorneo();
                break;
            case 2:
                printf("Cerrar periodo de inscripcion de un torneo.");
                break;
            case 3:
                printf("Descargar informes.");
                break;
            case 4:
                menuPrincipal();
                break;
            case 5:
                system("cls");
                printf("Fin.\n");
                break;
            default: ;
                printf("Eleccion incorrecta.\nVuelve a escoger una opcion:\t");
                scanf("%i", &eleccion);
                fflush(stdin);
                eleccionCorrecta = 0;
        }
    }
}

void menuSocio(Usuario usuario) {
    imprimirMenuSocio();
    int eleccion;
    int eleccionCorrecta = 0;
    printf("Escoge una opcion:\t");
    scanf("%i", &eleccion);
    fflush(stdin);
    while(eleccionCorrecta == 0){
        eleccionCorrecta = 1;
        switch (eleccion)
        {
        case 1:
            //Reservar pista
            break;
        case 2:
            //Torneos
            break;
        case 3:
            //Tienda
            break;
        case 4:
            menuPrincipal();
            break;
        case 5:
            system("cls");
            printf("Fin.\n");
            break;
        default:
            printf("Eleccion incorrecta.\nVuelve a escoger una opcion:\t");
            scanf("%i", &eleccion);
            fflush(stdin);
            eleccionCorrecta = 0;
            break;
        }
    }
}