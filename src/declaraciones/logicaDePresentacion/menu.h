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

//Gestiona el menu de torneos.
void menuTorneos(Usuario usuario);

//Gestiona la creacion de un torneo nuevo.
void crearTorneo();

//Gestiona la reservas de pista de la aplicacion.
void GestionReservas (Usuario u);

//Gestiona la primera venta del menu de la tienda. 
void menuTienda(Usuario usuario);

//Gestiona la segunda ventana del menu de la tienda.
void menuTienda2(Usuario u, ListaArticulos l);

//Gestiona la inscripcion a nuevos torneos.
void inscripcionTorneo(Usuario usuario);

//Gestiona el cierre del periodo de inscripciones de un torneo.
void cerrarInscripciones();

//Gestiona la actualizacion del ganador de un torneo por parte del administrador.
void actualizarGanadores();

//Gestiona el menu de descarga de informes. 
void descargarInformes();

#endif