#include "../logicaDeDatos/estructuras.h"
#include "crearConexion.h"
#include "../logicaDeNegocio/fechas.h"
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

//Devuelve un 0 si la fecha para un torneo esta libre, o un 1 si esta cogida.
int fechaCogida(Fecha fecha);

//Devuelve un puntero al usuario cuyo username es el provisto como parametro.
Usuario *getUsuario(char* nomUsuario);

//Devuelve un 1 si ningun usuario de la pareja esta apuntado al torneo y un 0 en caso contrario.
int parejaLibre(Fecha fecTorn, Usuario usu1, Usuario usu2);

//Devuelve las reservas que se han realizado hasta el momento
int*  getreservas(char* pista,char* fecha,char*hora);

//Devuelve el tamanyo del array de articulos

int tamanyoLista(int COD_TIPO_ART);

//Devueve un array de articulos

ListaArticulos *getArticulo(int COD_TIPO_ART, int tamanyo);

//Devuelve el numero de pistas de un tipo especifico disponibles en la fecha y hora indicadas por el usuario.
int getNumPistas(char* pista, char* fecha, char* hora);


#endif