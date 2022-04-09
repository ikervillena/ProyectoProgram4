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
	char sql[] = "INSERT INTO torneo (fec_torneo) VALUES (?)";
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

int insertCompra(int codCompra, Usuario u, Articulo a, int cantidad, char * f){
	int precioArticulo = atoi(a.precio);
	int rc;
	char *err_msg=0;
	sqlite3_stmt *res;
	char *sql ="INSERT INTO compra (COD_COMP, USUARIO, COD_ART, CANTIDAD, FECHA, PRECIO) VALUES (?,?,?,?,?,?);";
	rc=sqlite3_prepare_v2(db,sql,-1,&res,0);
	if (rc==SQLITE_OK){
		sqlite3_bind_int(res,1,codCompra);
		sqlite3_bind_int(res,4,cantidad);
		sqlite3_bind_int(res,3,a.codigo);
		sqlite3_bind_text(res,2,u.usuario,-1,SQLITE_STATIC);
		sqlite3_bind_int(res,6,precioArticulo*cantidad);
		sqlite3_bind_text(res,5,f,-1,SQLITE_STATIC);
	}else{
		fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
	}
	int step=sqlite3_step(res);
	printf("%i",step);
	sqlite3_finalize(res);

	return step;
	
}
