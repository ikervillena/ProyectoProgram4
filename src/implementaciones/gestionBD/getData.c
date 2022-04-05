#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../declaraciones/gestionBD/getData.h"
#include "../../declaraciones/logicaDePresentacion/visualizar.h"

/*El siguiente metodo devuelve el numero de filas que tiene por resultado una consulta sql
recibida como parametro.*/

int getNumFilas(char sql[]){
	startConn();
    sqlite3_stmt *stmt;
	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	int numFilas = 1;
	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			numFilas = sqlite3_column_int(stmt, 0);
		}
	} while (result == SQLITE_ROW);

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	return numFilas;
}

//El siguiente metodo devuelve un listado que contiene todos los usuarios.
//ESTÁ SIN TERMINAR

Usuario **getListaUsuarios(){
	startConn();
	sqlite3_stmt *stmt;
	char sql[] = "SELECT * FROM usuario";
	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}

	int numFilas = getNumFilas("SELECT * FROM usuario");
	Usuario **lista = (Usuario **) malloc(numFilas * sizeof(Usuario *));
	for(int i = 0; i < numFilas; i++){
		*(lista + i) = (Usuario *) malloc(sizeof(Usuario));
	}
	int i = 0;
	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			strcpy((*(lista + i))-> usuario, (const char *) sqlite3_column_text(stmt, 0));
            strcpy((*(lista + i))-> contrasenya, (const char *) sqlite3_column_text(stmt, 1));
            strcpy((*(lista + i))-> nombre, (const char *) sqlite3_column_text(stmt, 2));
            strcpy((*(lista + i))-> apellido, (const char *) sqlite3_column_text(stmt, 3));
            // Hay que cambiar la fecha de nacimiento.
            Fecha fecNac = {0,1,2};
            (*(lista + i))-> fecNac = fecNac;
            (*(lista + i))-> telefono = sqlite3_column_int(stmt, 5);
            (*(lista + i))-> puntos = sqlite3_column_int(stmt, 6);
            (*(lista + i))-> esSocio = sqlite3_column_int(stmt, 7);
			
            i++;
		}
	} while (result == SQLITE_ROW);

	return lista;
}

//El siguiente metodo devuelve un 1 si el usuario esta registrado en la BD, y un 0 en caso contrario.f

int comprobarUsuario(char *usuario, char *contrasenya){
	startConn();
	char sql[] = "SELECT usuario, contrasenya FROM usuario";
    sqlite3_stmt *stmt;
	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	int usuarioValido = 0;
	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			if(strcmp(usuario, sqlite3_column_text(stmt,0)) == 0 &&
			strcmp(contrasenya, sqlite3_column_text(stmt,1)) == 0){
				usuarioValido = 1;
				break;
			}

		}
	} while (result == SQLITE_ROW);

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	return usuarioValido;
}

int comprobarAdministrador(char *usuario, char *contrasenya){
	startConn();
	char sql[] = "SELECT usuario, contrasenya FROM admin";
    sqlite3_stmt *stmt;
	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	int usuarioValido = 0;
	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			if(strcmp(usuario, sqlite3_column_text(stmt,0)) == 0 &&
			strcmp(contrasenya, sqlite3_column_text(stmt,1)) == 0){
				usuarioValido = 1;
				break;
			}

		}
	} while (result == SQLITE_ROW);

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	return usuarioValido;
}

// PENDIENTE:

int fechaCogida(Fecha fecha) {
	startConn();
	char sql[] = "SELECT COUNT(*) FROM torneo WHERE fec_torneo = '";
	strcat(sql, textoFecha(fecha));
	strcat(sql, "'");
    sqlite3_stmt *stmt;
	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	int fechaCogida = 0;
	result = sqlite3_step(stmt);

	if(result == SQLITE_ROW) {
		if (sqlite3_column_int(stmt, 0) > 0) {
			fechaCogida = 1;
		}
	}

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	return fechaCogida;
}

Usuario *getUsuario(char* nomUsuario){
	startConn();
	char sql[] = "SELECT * FROM usuario WHERE usuario = ?";
    sqlite3_stmt *stmt;
	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	if (result == SQLITE_OK) {
		sqlite3_bind_text(stmt, 1, nomUsuario, strlen(nomUsuario), SQLITE_STATIC);
	} else{
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}

	Usuario *usuario = malloc(sizeof(Usuario));
	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {			
			usuario->usuario=(char *) malloc((strlen(sqlite3_column_text(stmt,0)) + 1)*sizeof(char));
			usuario->usuario=strcpy(usuario->usuario,sqlite3_column_text(stmt,0));
			usuario->usuario[strlen(sqlite3_column_text(stmt,0))]='\0';
			usuario->contrasenya=(char *) malloc((strlen(sqlite3_column_text(stmt,1)) + 1)*sizeof(char));
			usuario->contrasenya=strcpy(usuario->contrasenya,sqlite3_column_text(stmt,1));
			usuario->contrasenya[strlen(sqlite3_column_text(stmt,1))]='\0';
			usuario->nombre=(char *) malloc((strlen(sqlite3_column_text(stmt,2)) + 1)*sizeof(char));
			usuario->nombre=strcpy(usuario->nombre,sqlite3_column_text(stmt,2));
			usuario->nombre[strlen(sqlite3_column_text(stmt,2))]='\0';
			usuario->apellido=(char *) malloc((strlen(sqlite3_column_text(stmt,3)) + 1)*sizeof(char));
			usuario->apellido=strcpy(usuario->apellido,sqlite3_column_text(stmt,3));
			usuario->apellido[strlen(sqlite3_column_text(stmt,3))]='\0';
			Fecha fecNac = {0,1,2};
			usuario->fecNac = fecNac;
            usuario->telefono = sqlite3_column_int(stmt, 5);
            usuario->puntos = sqlite3_column_int(stmt, 6);
            usuario->esSocio = sqlite3_column_int(stmt, 7);
		}
	} while (result == SQLITE_ROW);

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}
	return usuario;
}