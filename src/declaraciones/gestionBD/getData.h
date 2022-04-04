#include "../logicaDeDatos/estructuras.h"
#include "crearConexion.h"
#ifndef getData
#define getData

extern int numFilas;
Usuario **getListaUsuarios();

//Devuelve el numero de filas que hay en una tabla de la BD.
int getNumFilas(char *tabla);

//Devuelve un 1 si los datos de acceso son correctos, o un 0 si no lo son.
int comprobarUsuario(char *usuario, char *contrasenya);

//Devuelve un 1 si los datos de acceso son correctos, o un 0 si no lo son.
int comprobarAdministrador(char *usuario, char *contrasenya);

//Devuelve un 0 si la fecha esta libre, o un 1 si esta cogida.
int fechaCogida(Fecha fecha);

//Devuelve un puntero al usuario cuyo username es el provisto como parametro.
Usuario *getUsuario(char* nomUsuario);
#endif