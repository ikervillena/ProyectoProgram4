#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include "../../declaraciones/gestionBD/getData.h"

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
            (*(lista + i))-> fecNac;
            (*(lista + i))-> telefono = sqlite3_column_int(stmt, 5);
            (*(lista + i))-> puntos = sqlite3_column_int(stmt, 6);
            (*(lista + i))-> esSocio = sqlite3_column_int(stmt, 7);
			
            i++;
		}
	} while (result == SQLITE_ROW);

	return lista;
}