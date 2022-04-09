#include "../../declaraciones/logicaDePresentacion/menu.h"
#include "../../declaraciones/gestionBD/getData.h"
#include "../../declaraciones/gestionBD/insertData.h"
#include "../../declaraciones/logicaDePresentacion/visualizar.h"
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
            GestionReservas ();
            break;
        case 2:
            //Torneos
            break;
        case 3:
            menuTienda(usuario);
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

void menuTienda(Usuario u){
    imprimirMenuTienda();
    int eleccion;
    int eleccionCorrecta = 0;
    printf("Escoge el tipo de articulo que desees comprar:\t");
    scanf("%i", &eleccion);
    fflush(stdin);
    while(eleccionCorrecta == 0) {
        eleccionCorrecta = 1;
        switch (eleccion) {
            case 1:
                ListaArticulos* listaArticulos = (ListaArticulos*)malloc(sizeof(ListaArticulos));
                int b = tamanyoLista(eleccion);
                listaArticulos = getArticulo(eleccion, b);
                break;
            case 2:
                ListaArticulos* listaArticulos = (ListaArticulos*)malloc(sizeof(ListaArticulos));
                int b = tamanyoLista(eleccion);
                listaArticulos = getArticulo(eleccion, b);
                break;
            case 3:
                ListaArticulos* listaArticulos = (ListaArticulos*)malloc(sizeof(ListaArticulos));
                int b = tamanyoLista(eleccion);
                listaArticulos = getArticulo(eleccion, b);
                break;
            case 4:
                ListaArticulos* listaArticulos = (ListaArticulos*)malloc(sizeof(ListaArticulos));
                int b = tamanyoLista(eleccion);
                listaArticulos = getArticulo(eleccion, b);
                break;
            case 5:
                ListaArticulos* listaArticulos = (ListaArticulos*)malloc(sizeof(ListaArticulos));
                int b = tamanyoLista(eleccion);
                listaArticulos = getArticulo(eleccion, b);
                break;
            case 6:
                ListaArticulos* listaArticulos = (ListaArticulos*)malloc(sizeof(ListaArticulos));
                int b = tamanyoLista(eleccion);
                listaArticulos = getArticulo(eleccion, b);
                break;
            case 7:
                ListaArticulos* listaArticulos = (ListaArticulos*)malloc(sizeof(ListaArticulos));
                int b = tamanyoLista(eleccion);
                listaArticulos = getArticulo(eleccion, b);
                break;
            case 8:
                ListaArticulos* listaArticulos = (ListaArticulos*)malloc(sizeof(ListaArticulos));
                int b = tamanyoLista(eleccion);
                listaArticulos = getArticulo(eleccion, b);
                break;
            case 9:
                ListaArticulos* listaArticulos = (ListaArticulos*)malloc(sizeof(ListaArticulos));
                int b = tamanyoLista(eleccion);
                listaArticulos = getArticulo(eleccion, b);
                break;
            case 10:
                ListaArticulos* listaArticulos = (ListaArticulos*)malloc(sizeof(ListaArticulos));
                int b = tamanyoLista(eleccion);
                listaArticulos = getArticulo(eleccion, b);
                break;
            case 11:
                ListaArticulos* listaArticulos = (ListaArticulos*)malloc(sizeof(ListaArticulos));
                int b = tamanyoLista(eleccion);
                listaArticulos = getArticulo(eleccion, b);
                break;
            case 12:
                ListaArticulos* listaArticulos = (ListaArticulos*)malloc(sizeof(ListaArticulos));
                int b = tamanyoLista(eleccion);
                listaArticulos = getArticulo(eleccion, b);
                break;
            case 13:
                ListaArticulos* listaArticulos = (ListaArticulos*)malloc(sizeof(ListaArticulos));
                int b = tamanyoLista(eleccion);
                listaArticulos = getArticulo(eleccion, b);
                break;
            case 14:
                ListaArticulos* listaArticulos = (ListaArticulos*)malloc(sizeof(ListaArticulos));
                int b = tamanyoLista(eleccion);
                listaArticulos = getArticulo(eleccion, b);
                break;
            case 15:
                ListaArticulos* listaArticulos = (ListaArticulos*)malloc(sizeof(ListaArticulos));
                int b = tamanyoLista(eleccion);
                listaArticulos = getArticulo(eleccion, b);
                break;
            case 16:
                menuSocio(u);
                break;
            default: ;
                printf("Eleccion incorrecta.\nVuelve a escoger una opcion:\t");
                scanf("%i", &eleccion);
                fflush(stdin);
                eleccionCorrecta = 0;
        }
    }
}

void menuTienda2(Usuario u, ListaArticulos l){ 
    imprimirArticulos(l);
    int eleccion;
    int cantidad;
    int eleccionCorrecta = 0;
    printf("Escoge el codigo del articulo que desees comprar:\t");
    scanf("%i", &eleccion);
    fflush(stdin);
    int existeCodigoArticulo = 0;
    int indiceArticulo=0;
    for (int i = 0; i < l.tamanyo; i++)
    {
        if (l.articulos[i].codigo==eleccion)
        {
            existeCodigoArticulo=1;
            indiceArticulo=i;
        }
    }
    if (existeCodigoArticulo==1)
    {
        printf("Seleccione la cantidad que desea comprar: \t");
        scanf("%i", &cantidad);
        fflush(stdin);
        char sql[] = "SELECT * FROM compra"; 
        int codigoCompra = getNumFilas(sql)+1;
        char* fecha = fechaActual();
        int b = insertCompra(codigoCompra, u, l.articulos[indiceArticulo], cantidad, fecha);

        printf("La compra ha sido procesada con éxito. Muchas gracias. \n");

    }
}




void GestionReservas (){
    printf("AREA DE RESERVAS DE USUARIO\n");
    printf("\n");
    printf("Escriba el tipo de pista que desea:\n ");
    printf("-indoor\n -outdoor\n");

    char* nompist= (char*)malloc(strlen(stdin)*sizeof(char));
    scanf(stdin,"%s",nompist);
    printf("Escriba el dia que desea la pista: dd-ms-anyo  ");
    char* fecha= (char*)malloc(strlen(stdin)*sizeof(char));
    scanf(stdin,"%s",fecha);
    printf("\n ");

    ffflush(stdin);
    printf("Escriba la hora que desea la pista (Recuerda que solo se pueden servar las pista a empunto): hora:minuto  ");
    char* hora= (char*)malloc(6*sizeof(char));   
    scanf(stdin,"%s",hora);
    printf("\n ");
    char num1='0';
        while(hora[3]== num1 && hora[4]== num1){
        fflush(stdout);
        printf("Escriba la hora que desea la pista (Recuerda que solo se pueden servar las pista a empunto): hora:minuto  ");
        char* hora= (char*)malloc(strlen(stdin)*sizeof(char));
        scanf(stdin,"%s",hora);
        printf("\n ");
    }
    printf("\n ");
    int* numeros=getreservas(nompist,fecha,hora);
    imprimirPistas(numeros);
    int si=0;
    while (si=0){
       printf("Escriba el numero de pista que dese reservar: \n");
        int pistanum;
        scanf(stdin,"%s",&pistanum);
          
    }
    if(int a=0; a<sizeof if(int a=0; a<sizeof(numerosnumeros
        if (n{
            si=1;
            [a]=    stanum){
            si=1;
        }
        }
    (numeros);a++){
        
