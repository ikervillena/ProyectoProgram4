#ifndef _VISUALIZAR_H_
#define _VISUALIZAR_H_
#include "../logicaDeDatos/estructuras.h"

//Declaraciones de funciones dirigidas a visualizar informacion en pantalla.

//Limpia la pantalla e imprime la cabecera que sera utilizada en todas las ventanas de la aplicacion.
void imprimirTitulo();

//Imprime el menu inicial.
void imprimirInicio();

//Imprime el menu de los socios.
void imprimirMenuSocio();

//Imprime el menu de los administradores.
void imprimirMenuAdmin();

//Imprime los datos del usuario recibido como parametro.
void imprimirDatosUsuario(Usuario usuario);

//Imprime las pistas disponibles en la fecha y hora indicada.
void imprimirPistas(int* numeros);

//Imprime el menu de la tienda. 
void imprimirMenuTienda();

//Imprime los articulos de una lista pasada por parámetro
void imprimirArticulos(ListaArticulos listaArticulos);


#endif