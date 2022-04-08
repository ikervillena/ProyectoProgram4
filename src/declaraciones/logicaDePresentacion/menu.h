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

#endif