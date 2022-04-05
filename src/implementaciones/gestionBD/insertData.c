#include "../../declaraciones/gestionBD/insertData.h"
#include "../../../librerias/sqlite/sqlite3.h"
#include "../../declaraciones/logicaDeNegocio/fechas.h"
#include "../../declaraciones/gestionBD/crearConexion.h"
#include <string.h>
#include <stdio.h>

//SIN TERMINAR
int insertarTorneo(Fecha fecha) {
    startConn();
    sqlite3_stmt *stmt;
    //HAY QUE CAMBIAR COD_TOORNEO.
	char sql[] = "INSERT INTO torneo (cod_torneo, fec_torneo, cod_par_gan) VALUES (50, ?, NULL)";
    char *fecTorneo = textoFecha(fecha);
	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	result = sqlite3_bind_text(stmt, 1, fecTorneo, strlen(fecTorneo), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error inserting new data\n");
		return result;
	}

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	return SQLITE_OK;
}