#include "../logicaDeDatos/estructuras.h"
#include "crearConexion.h"
#ifndef getData
#define getData

extern int numFilas;
Usuario **getListaUsuarios();
int getNumFilas(char *tabla);
int comprobarUsuario(char *usuario, char *contrasenya);
#endif