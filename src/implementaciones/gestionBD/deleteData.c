#include "../../declaraciones/gestionBD/deleteData.h"
#include "../../declaraciones/gestionBD/crearConexion.h"
#include "../../../librerias/Sqlite/sqlite3.h"
#include <stdio.h>

int borrarTorneo(int codTorneo) {
    startConn();
    sqlite3_stmt *stmt;
	char sql[] = "DELETE FROM torneo WHERE cod_torneo = ?";
	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, 0) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	result = sqlite3_bind_int(stmt, 1, codTorneo);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error deleting data\n");
		return result;
	}

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	return SQLITE_OK;
}

int borrarInscripcion(int codTorneo, int codPareja) {
	startConn();
    sqlite3_stmt *stmt;
	char sql[] = "DELETE FROM inscripcion WHERE cod_torneo = ? AND cod_pareja = ?";
	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, 0) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	result = sqlite3_bind_int(stmt, 1, codTorneo);
	result = sqlite3_bind_int(stmt, 2, codPareja);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error deleting data\n");
		return result;
	}

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	return SQLITE_OK;
}