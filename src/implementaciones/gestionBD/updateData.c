#include "../../declaraciones/gestionBD/updateData.h"
#include "../../declaraciones/gestionBD/crearConexion.h"
#include "../../../librerias/Sqlite/sqlite3.h"
#include <stdio.h>

int cierreInscripciones(int codTorneo) {
    startConn();
    sqlite3_stmt *stmt;
	char sql[] = "UPDATE torneo SET cod_par_gan = 0 WHERE cod_torneo = ?";
	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, 0) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (UPDATE)\n");
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
		printf("Error updating data\n");
		return result;
	}

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (UPDATE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	return SQLITE_OK;
}