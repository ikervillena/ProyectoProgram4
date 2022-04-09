#ifndef _MENU_H_
#define _MENU_H_
#include "visualizar.h"

//Declaraciones de las funciones dirigidas a gestionar el menu de la aplicacion.


void menuPrincipal();

//Gestiona el inicio de sesion.
void iniciarSesion();

//Gestiona la creacion de cuentas de usuarios.
void crearCuenta();

//Gestiona el menu de un administrador.
void menuAdmin();

//Gestiona el menu de un socio.
void menuSocio(Usuario usuario);

//Gestiona la creacion de un torneo nuevo.
void crearTorneo();

//Gestiona la reservas de pista de la aplicacion.
void GestionReservas ();

//Gestiona la primera venta del menu de la tienda. 
void menuTienda(Usuario usuario);

//Gestiona la segunda ventana del menu de la tienda.
void menuTienda2(Usuario u, ListaArticulos l);
#endif