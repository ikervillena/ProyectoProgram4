#include "../../declaraciones/logicaDePresentacion/menu.h"
#include "../../declaraciones/gestionBD/getData.h"
#include "../../declaraciones/gestionBD/insertData.h"
#include "../../declaraciones/logicaDePresentacion/visualizar.h"
#include "../../declaraciones/gestionBD/updateData.h"
#include "../../declaraciones/logicaDeNegocio/torneos.h"
#include "../../declaraciones/gestionBD/deleteData.h"
#include "../../declaraciones/logicaDeNegocio/informes.h"
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
    free(usuario);
    free(contrasenya);
}

void crearCuenta(){
    imprimirTitulo();
    printf("CREACION DE CUENTA:\n\nUsuario:\t");
    char usuario[20];
    int usuarioCorrecto = 0;
    while(!usuarioCorrecto){
        char user[20];
        scanf("%s", user);
        fflush(stdin);
        if(usuarioLibre(user) == 0){
            printf("El usuario ya existe, elige otro por favor.\nUsuario:\t");
        } else{
            usuarioCorrecto = 1;
            strcpy(usuario, user);
        }
    }
    char *contrasenya = malloc(20 * sizeof(char));
    char *nombre = malloc(20*sizeof(char));
    char *apellido = malloc(20*sizeof(char));
    char *fecNac = malloc(20 * sizeof(char));
    int telefono;
    int esSocio;


    printf("\nContrasenya:\t");
    scanf("%s", contrasenya);
    fflush(stdin);
    printf("\nNombre:\t");
    scanf("%s", nombre);
    fflush(stdin);
    printf("\nApellido\t");
    scanf("%s", apellido);
    fflush(stdin);
    printf("\nFecha de nacimiento (formato dd-mm-aaaa):\t");
    scanf("%s", fecNac);
    fflush(stdin);
    printf("\nTelefono:\t");
    scanf("%i", &telefono);
    fflush(stdin);

    int eleccionCorrecta = 0;
    while(eleccionCorrecta == 0){
        char socio[5];
        printf("\nInscribirse como socio (SI/NO):\t");
        scanf("%s", socio);
        fflush(stdin);
        if(strcmp(socio, "SI") == 0){
            esSocio = 1, eleccionCorrecta = 1;
        } else{
            if(strcmp(socio, "NO") == 0) {
                esSocio = 0, eleccionCorrecta = 1;
            } else{
                printf("Eleccion incorrecta.\n");
            }
        }
    }
    printf("Usuario: %s. Nombre: %s. Apellido: %s. FecNac: %s. Telefono: %i. Socio: %s.\n", 
    usuario, nombre, apellido, fecNac, telefono, esSocio == 1 ? "SI":"NO");
    Usuario nuevoUsuario = {usuario, contrasenya, nombre, apellido, getFecha(fecNac), telefono, esSocio};
    insertarUsuario(nuevoUsuario);
    free(contrasenya);
    free(nombre);
    free(apellido);
    free(fecNac);
    menuPrincipal();
}

void crearTorneo(){
    imprimirTitulo();
    int dia, mes, anyo;
    int eleccionCorrecta = 0;
    printf("CREAR TORNEO:\n\nEscoge la fecha del torneo.\n\nDia:\t");
    while (eleccionCorrecta == 0){
        scanf("%i", &dia);
        fflush(stdin);
        printf("\nMes:\t");
        scanf("%i", &mes);
        fflush(stdin);
        printf("\nAnyo:\t");
        scanf("%i", &anyo);
        fflush(stdin);
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

void descargarInformes(){
    imprimirMenuInformes();
    int eleccion;
    int eleccionCorrecta = 0;
    printf("Escoge una opcion:\t");
    scanf("%i", &eleccion);
    fflush(stdin);
    while(eleccionCorrecta == 0) {
        eleccionCorrecta = 1;
        switch (eleccion) {
            case 1:;
                printf("Escriba el dia del que desea descargar el informe de reservas: dd-ms-anyo \n ");
                char* fecha;
                fecha=(char*)malloc(11*sizeof(char));
                scanf("%s",fecha);
                printf("\n ");
                fflush(stdin);
                getReservas(fecha);
                printf("Informe descargado con exito.\n");
                system("pause");
                menuAdmin();
                break;
            case 2:;
                int tamanyo = tamanyoListaCompra();
                ListaCompra* listaCompras = (ListaCompra*)malloc(sizeof(ListaCompra));
                listaCompras = getCompras(tamanyo);
                ficheroCompras(listaCompras);
                printf("Informe descargado con exito.\n");
                system("pause");
                menuAdmin();
                break;
            case 3:
                menuAdmin();
                break;
            default: ;
                printf("Eleccion incorrecta.\nVuelve a escoger una opcion:\t");
                scanf("%i", &eleccion);
                fflush(stdin);
                eleccionCorrecta = 0;
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
                cerrarInscripciones();
                break;
            case 3:
                actualizarGanadores();
                break;
            case 4:
                descargarInformes();
                break;
            case 5:
                menuPrincipal();
                break;
            case 6:
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
            GestionReservas (usuario);
            break;
        case 2:
            menuTorneos(usuario);
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

void menuTorneos(Usuario usuario){
    imprimirMenuTorneos();
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
            inscripcionTorneo(usuario);
            break;
        case 2:
            imprimirSiguientesTorneos(usuario);
            system("pause");
            break;
        case 3:
            menuSocio(usuario);
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
            case 1: ;
                ListaArticulos* listaArticulos = (ListaArticulos*)malloc(sizeof(ListaArticulos));
                int b = tamanyoLista(eleccion);
                listaArticulos = getArticulo(eleccion, b);
                menuTienda2(u,*listaArticulos);
                break;
            case 2: ;
                ListaArticulos* listaArticulos2 = (ListaArticulos*)malloc(sizeof(ListaArticulos));
                int b2 = tamanyoLista(eleccion);
                listaArticulos2 = getArticulo(eleccion, b2);
                menuTienda2(u,*listaArticulos2);
                break;
            case 3: ;
                ListaArticulos* listaArticulos3 = (ListaArticulos*)malloc(sizeof(ListaArticulos));
                int b3 = tamanyoLista(eleccion);
                listaArticulos3 = getArticulo(eleccion, b3);
                menuTienda2(u,*listaArticulos3);
                break;
            case 4: ;
                ListaArticulos* listaArticulos4 = (ListaArticulos*)malloc(sizeof(ListaArticulos));
                int b4 = tamanyoLista(eleccion);
                listaArticulos4 = getArticulo(eleccion, b4);
                menuTienda2(u,*listaArticulos4);
                break;
            case 5: ;
                ListaArticulos* listaArticulos5 = (ListaArticulos*)malloc(sizeof(ListaArticulos));
                int b5 = tamanyoLista(eleccion);
                listaArticulos5 = getArticulo(eleccion, b5);
                menuTienda2(u,*listaArticulos5);
                break;
            case 6: ;
                ListaArticulos* listaArticulos6 = (ListaArticulos*)malloc(sizeof(ListaArticulos));
                int b6 = tamanyoLista(eleccion);
                listaArticulos6 = getArticulo(eleccion, b6);
                menuTienda2(u,*listaArticulos6);
                break;
            case 7: ;
                ListaArticulos* listaArticulos7 = (ListaArticulos*)malloc(sizeof(ListaArticulos));
                int b7 = tamanyoLista(eleccion);
                listaArticulos7 = getArticulo(eleccion, b7);
                menuTienda2(u,*listaArticulos7);
                break;
            case 8: ;
                ListaArticulos* listaArticulos8 = (ListaArticulos*)malloc(sizeof(ListaArticulos));
                int b8 = tamanyoLista(eleccion);
                listaArticulos8 = getArticulo(eleccion, b8);
                menuTienda2(u,*listaArticulos8);
                break;
            case 9: ;
                ListaArticulos* listaArticulos9 = (ListaArticulos*)malloc(sizeof(ListaArticulos));
                int b9 = tamanyoLista(eleccion);
                listaArticulos9 = getArticulo(eleccion, b9);
                menuTienda2(u,*listaArticulos9);
                break;
            case 10: ;
                ListaArticulos* listaArticulos10 = (ListaArticulos*)malloc(sizeof(ListaArticulos));
                int b10 = tamanyoLista(eleccion);
                listaArticulos10 = getArticulo(eleccion, b10);
                menuTienda2(u,*listaArticulos10);
                break;
            case 11: ;
                ListaArticulos* listaArticulos11 = (ListaArticulos*)malloc(sizeof(ListaArticulos));
                int b11 = tamanyoLista(eleccion);
                listaArticulos11 = getArticulo(eleccion, b11);
                menuTienda2(u,*listaArticulos11);
                break;
            case 12: ;
                ListaArticulos* listaArticulos12 = (ListaArticulos*)malloc(sizeof(ListaArticulos));
                int b12 = tamanyoLista(eleccion);
                listaArticulos12 = getArticulo(eleccion, b12);
                menuTienda2(u,*listaArticulos12);
                break;
            case 13: ;
                ListaArticulos* listaArticulos13 = (ListaArticulos*)malloc(sizeof(ListaArticulos));
                int b13 = tamanyoLista(eleccion);
                listaArticulos13 = getArticulo(eleccion, b13);
                menuTienda2(u,*listaArticulos13);
                break;
            case 14: ;
                ListaArticulos* listaArticulos14 = (ListaArticulos*)malloc(sizeof(ListaArticulos));
                int b14 = tamanyoLista(eleccion);
                listaArticulos14 = getArticulo(eleccion, b14);
                menuTienda2(u,*listaArticulos14);
                break;
            case 15: ;
                ListaArticulos* listaArticulos15 = (ListaArticulos*)malloc(sizeof(ListaArticulos));
                int b15 = tamanyoLista(eleccion);
                listaArticulos15 = getArticulo(eleccion, b15);
                menuTienda2(u,*listaArticulos15);
                break;
            case 16: ;
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
        int cantidad;
        printf("Seleccione la cantidad que desea comprar: \t");
        scanf("%i", &cantidad);
        fflush(stdin);
        char sql[] = "SELECT * FROM compra"; 
        int codigoCompra = getNumFilas(sql)+1;
        char* fecha = (char*)malloc(sizeof(char)*100);
        printf("\n");
        fecha = fechaActual(fecha);
        int b = insertCompra(codigoCompra, u, l.articulos[indiceArticulo], cantidad, fecha);

        printf("La compra ha sido procesada con exito. Muchas gracias. \n");
        printf("Si quiere volver al menu de la tienda introduzca un 1, para salir introduzca un 0.\n");
        int eleccionSalida;
        scanf("%i",&eleccionSalida);
        if (eleccionSalida==1){
            menuTienda(u);
        }else{
            system("cls");
            printf("Fin.\n");
        }



    }
}
void GestionReservas (Usuario u){
    imprimirTitulo();
    int pistasdisponibles=0;
    char *nompist;
    char *fecha;
    char *hora ;
    while(pistasdisponibles==0){
        printf("AREA DE RESERVAS DE USUARIO\n");
        printf("\n");
        printf("Escriba el tipo de pista que desea:\n ");
        printf("-indoor\n -outdoor\n");
        nompist=(char*)malloc(8*sizeof(char));
        scanf("%s",nompist);
        fflush(stdin);

        printf("Escriba el dia que desea la pista: dd-ms-anyo \n ");
        fecha=(char*)malloc(11*sizeof(char));
        scanf("%s",fecha);
        printf("\n ");
        fflush(stdin);

        int a=0;
        while (a==0){
            printf("Escriba la hora que desea la pista (Recuerda que solo se pueden servar las pista a en punto): hora:minuto \n"); 
            hora=(char*)malloc(6*sizeof(char));
            scanf("%s",hora);
            printf("\n ");
            fflush(stdin);
            char* Char = (char *)malloc(sizeof(char));
            sscanf("0", "%c", Char);
            
            if (hora[3]==*Char && hora[4]==*Char){
                a=a+1;
            }
            if (a==0){
                printf("Hora incorrecta :");    
            }
        }

    pistasdisponibles=getNumPistas(nompist,fecha,hora);
    if(pistasdisponibles==0){
        printf("En el dia y hora que has seleccionado no hay pistas %s disponibles \n",nompist);
        }
    imprimirTitulo();
    }
    printf("\n ");
    int* numeros=getreservas(nompist,fecha,hora);
    imprimirPistas(numeros);
    int si=0;
    int pistanum;
    while (si==0){
       printf("\n");
       printf("Escriba el numero de pista que desee reservar: \n");
        scanf("%d",&pistanum);
        for(int a=0; a<sizeof(numeros);a++){
            if (numeros[a]==pistanum){
                si=si+1;
            }
        }
        if(si==0){
            printf("El numero de pista que ha elegido no esta disponible \n"); 
            }
    }
    char sql[]=("SELECT * FROM reserva");
    int filas=getNumFilas(sql);
    int b = insertReserva(filas+1,u,pistanum,fecha,hora,8);
    printf("\n");

    printf("La reserva ha sido procesada con exito. Muchas gracias.\n");
    printf("\n");
    system("pause");
    menuSocio(u);
    
}
        
void inscripcionTorneo(Usuario usuario) {
    imprimirInscripcionTorneo();
    imprimirProximosTorneos();
    int eleccion;
    int eleccionCorrecta = 0;
    int salir = 0;
    do
    {
        printf("Escoge un codigo de torneo (0 para volver):\t");
        scanf("%i", &eleccion);
        fflush(stdin);
        if(eleccion == 0) {
            menuTorneos(usuario);
            eleccionCorrecta = 1;
            salir = 1;
        } else{
            if (inscripcionesAbiertas(eleccion) == 1){
                eleccionCorrecta = 1;
            } else {
                printf("Eleccion incorrecta.\n\n");
            }
        }
    } while (eleccionCorrecta == 0);
    
    if(salir == 0){ 
        char nomUsuario[25];
        eleccionCorrecta = 0;
        Usuario *companyero;
        do
        {
            printf("\nNombre de usuario de tu pareja ('volver' para volver):\t");
            scanf("%s", nomUsuario);
            fflush(stdin);
            companyero = getUsuario(nomUsuario);
            printf("%s\n", companyero->nombre);
            if(strcmp(nomUsuario, "volver") == 0) {
                menuTorneos(usuario);
                eleccionCorrecta = 1;
                salir = 1;
            } else{
                if(companyero->esSocio == 1){
                    eleccionCorrecta = 1;
                    printf("Es socio.\n");
                } else {
                    printf("El nombre de usuario no corresponde a ningun socio.\n");
                }
            }
        } while (eleccionCorrecta == 0);
        
        if(salir == 0){
            //Guardar la pareja en la BD en caso de que no este registrada.
            if(getCodigoPareja(usuario, *companyero) == 0) insertarPareja(usuario, *companyero);

            //Inscribir a la pareja en el torneo.
            Pareja pareja = {getCodigoPareja(usuario, *companyero), usuario, *companyero};
            insertarInscripcion(eleccion, pareja);

            free(companyero);
            menuTorneos(usuario);
        }
    }

}

void cerrarInscripciones() {
    imprimirCierreInscripciones();
    imprimirProximosTorneos();
    int eleccion;
    int eleccionCorrecta = 0;
    int salir = 0;
    do
    {
        printf("Escoge un codigo de torneo (0 para volver):\t");
        scanf("%i", &eleccion);
        fflush(stdin);
        if(eleccion == 0) {
            menuAdmin();
            eleccionCorrecta = 1;
            salir = 1;
        } else{
            if (inscripcionesAbiertas(eleccion) == 1){
                eleccionCorrecta = 1;
            } else {
                printf("Eleccion incorrecta.\n\n");
            }
        }
    } while (eleccionCorrecta == 0);

    if(salir == 0){
        printf("eleccion %i\n", eleccion);

        //Cerrar el periodo de inscripciones del torneo (cod_par_gan = 0).
        cierreInscripciones(eleccion);

        int insc = comprobarInscripciones(eleccion);
        if(insc == 1) {
            //En caso de exceder el numero maximo, se realiza un sorteo entre los inscritos.
            reducirParticipantes(eleccion);
        } else {
            if(insc == -1) {
                //En caso de no llegar al numero minimo de inscripciones, se borra el torneo.
                borrarTorneo(eleccion);
            }
        }
        menuAdmin();
    }
    
}

void actualizarGanadores() {
    imprimirActualizacionGanadores();
    imprimirTorneosCerrados();
    int eleccion;
    int eleccionCorrecta = 0;
    int salir = 0;
    do
    {
        printf("Escoge un codigo de torneo (0 para volver):\t");
        scanf("%i", &eleccion);
        fflush(stdin);
        if(eleccion == 0) {
            menuAdmin();
            eleccionCorrecta = 1;
        } else{
            if (ganadorAsignado(eleccion) == 0){
                eleccionCorrecta = 1;
            } else {
                printf("Eleccion incorrecta.\n\n");
            }
        }
    } while (eleccionCorrecta == 0);

    int codTorneo = eleccion;
    eleccionCorrecta = 0;
    do
    {
        printf("\nIndica el codigo de la pareja ganadora (0 para volver):\t");
        scanf("%i", &eleccion);
        fflush(stdin);
        if(eleccion == 0) {
            menuAdmin();
            eleccionCorrecta = 1;
            salir = 1;
        } else{
            if (ganadorValido(codTorneo, eleccion) == 1){
                eleccionCorrecta = 1;
                printf("El ganador es valido.");
            } else {
                printf("Eleccion incorrecta.\n\n");
            }
        }
    } while (eleccionCorrecta == 0);

    if(salir == 0){
        actualizarGanador(codTorneo, eleccion);
        menuAdmin();
    }
}

