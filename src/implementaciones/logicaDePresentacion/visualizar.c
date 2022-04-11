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

void imprimirMenuAdmin(){
    imprimirTitulo();
    printf("MENU:\n\n1. Crear nuevo torneo.\n2. Cerrar periodo de inscripcion de un torneo.\n"
    "3. Actualizar ganadores de un torneo.\n4. Descargar informes.\n5. Cerrar sesion.\n6. Salir.\n\n");
}

void imprimirMenuTorneos() {
    imprimirTitulo();
    printf("TORNEOS\n\n1. Inscripciones abiertas.\n2. Proximo torneo.\n3. Volver.\n\n");
}

void imprimirDatosUsuario(Usuario usuario){
    printf("Usuario:\t%s.\nNombre:\t\t%s.\nApellido:\t%s.\nTelefono:\t%i.\nPuntos:\t\t%i.\nEs socio:\t%i.\n",
    usuario.usuario, usuario.nombre, usuario.apellido, usuario.telefono, usuario.puntos, usuario.esSocio);
}

void imprimirMenuTienda(){
    imprimirTitulo();
    printf("Escoger tipo de producto:\n\n1. Pelotas de padel.\n"
    "2. Palas de padel.\n3. Protectores.\n4. Munequeras.\n"
    "5. Cintas.\n6. Paleteros. \n7. Presurizador de pelotas. \n8. Overgrips. \n"
    "9. Zapatillas de padel. \n10. Pantalones. \n11. Camisetas. \n12. Polos. \n"
    "13. Sudaderas. \n14. Gorras. \n15. Tops deportivos\n\n16. Volver\n\n");

    printf("Seleccione el tipo de articulo que desee comprar: \n");


}
void imprimirPistas(int* numeros) {
     printf("Las pistas disponibles son las siguientes:\n");
     printf("\n");
     for (int i=0;i<sizeof(numeros);i++){
         printf("- %d \n",numeros[i]);
     }
}  

void imprimirArticulos(ListaArticulos listaArticulos){
  
    for (int i = 0; i<listaArticulos.tamanyo;i++){
        printf("Codigo de articulo: %i\n", listaArticulos.articulos[i].codigo);
        printf("%s : %s \n", listaArticulos.articulos[i].nombre, listaArticulos.articulos[i].descripcion);    
        printf("Su precio es de %s euros \n\n", listaArticulos.articulos[i].precio);
    }
}

void imprimirInscripcionTorneo() {
    imprimirTitulo();
    printf("INSCRIPCION A TORNEOS\n\n");
}

void imprimirCierreInscripciones() {
    imprimirTitulo();
    printf("CIERRE DE INSCRIPCIONES A TORNEOS\n\n");
}

void imprimirActualizacionGanadores() {
    imprimirTitulo();
    printf("ACTUALIZACION DE GANADORES DE UN TORNEO\n\n");
}