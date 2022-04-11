#ifndef _ESTRUCTURAS_H_
#define _ESTRUCTURAS_H_

//Declaracion de la estructura de un articulo.

typedef struct {
	int codigo;
    char *tipo;
    char *marca;
    char *nombre;
    char *descripcion;
    char *precio;
} Articulo;

//Declaracion de la estructura de un material.

typedef struct {
    int codigo;
    char *descripcion;
    int precioHora;
} Material;

//Declaracion de la estructura de una pista.

typedef struct {
    int numero;
    char *tipo;
} Pista;

//Declaracion de la estructura de una fecha.

typedef struct {
    int anyo;
    int mes;
    int dia;
} Fecha;

//Declaracion de la estructura de un usuario.

typedef struct {
    char *usuario;
    char *contrasenya;
    char *nombre;
    char *apellido;
    Fecha fecNac;
    int telefono;
    int puntos;
    int esSocio;
} Usuario;

//Declaracion de la estructura de una reserva.

typedef struct {
    Pista pista;
    Fecha fecha;
    char *hora;
    int precio;
} Reserva;

//Declaracion de la estructura de un administrador.

typedef struct {
    char *usuario;
    char *contrasenya;
} Administrador;

//Declaracion de la estructura de una pareja.

typedef struct {
    int codigo;
    Usuario jugador1;
    Usuario jugador2;
} Pareja;

//Declaracion de la estructura de un torneo.

typedef struct {
    int codigo;
    Fecha fecha;
    Pareja parejaGanadora;
} Torneo;

typedef struct{
	int tamanyo;
	Articulo *articulos;
}ListaArticulos;

typedef struct{
    int codigo;
    char* usuario;
    int codArt;
    int cantidad;
    char* fecha;
    int precio;
}Compra;

typedef struct{
    Compra* arrayCompras;
    int tamanyo;
}ListaCompra;

typedef struct 
{
    int codigo;
    char* usuario;
    int numPista;
    char* fecha;
    char* hora;
    int precio;
} Reservas;

typedef struct 
{
    int tamanyo;
    Reservas* arrayReservas;
}ListaReservas;



#endif