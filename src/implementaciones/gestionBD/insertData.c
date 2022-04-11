#include "../../declaraciones/gestionBD/insertData.h"
#include "../../../librerias/sqlite/sqlite3.h"
#include "../../declaraciones/logicaDeNegocio/fechas.h"
#include "../../declaraciones/gestionBD/crearConexion.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int insertarTorneo(Fecha fecha) {
    startConn();
    sqlite3_stmt *stmt;
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

int insertReserva(int codReserva, Usuario u,int numpista, char* fecha, char* hora, int precio){
	int rc;
	char *err_msg=0;
	sqlite3_stmt *res;
	char *sql ="INSERT INTO reserva (COD_RES, USUARIO, NUM_PISTA,FECHA,HORA,PRECIO) VALUES (?,?,?,?,?,?);";
	rc=sqlite3_prepare_v2(db,sql,-1,&res,0);
	
	if (rc==SQLITE_OK){
		sqlite3_bind_int(res,1,codReserva);
		sqlite3_bind_text(res,2,u.usuario,-1,SQLITE_STATIC);
		sqlite3_bind_int(res,3,numpista);
		sqlite3_bind_text(res,4,fecha,-1,SQLITE_STATIC);
		sqlite3_bind_text(res,5,hora,-1,SQLITE_STATIC);
		sqlite3_bind_int(res,6,precio);
		}else{
		fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
	}
	int step=sqlite3_step(res);
	printf("%i",step);
	sqlite3_finalize(res);

	return step;
	
}

int insertarInscripcion(int codTorneo, Pareja pareja){
	startConn();
    sqlite3_stmt *stmt;
	char sql[] = "INSERT INTO inscripcion (cod_torneo, cod_pareja) VALUES (?, ?)";
	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	result = sqlite3_bind_int(stmt, 1, codTorneo);
	result = sqlite3_bind_int(stmt, 2, pareja.codigo);

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

int insertarPareja(Usuario jugador1, Usuario jugador2) {
	startConn();
    sqlite3_stmt *stmt;
	char sql[] = "INSERT INTO pareja (usuario1, usuario2) VALUES (?, ?)";
	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	result = sqlite3_bind_text(stmt, 1, jugador1.usuario, strlen(jugador1.usuario), SQLITE_STATIC);
	result = sqlite3_bind_text(stmt, 2, jugador2.usuario, strlen(jugador2.usuario), SQLITE_STATIC);

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

int insertarUsuario(Usuario usuario) {
	startConn();
    sqlite3_stmt *stmt;
	char sql[] = "INSERT INTO usuario VALUES (?, ?, ?, ?, ?, ?, 100, ?)";
	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	result = sqlite3_bind_text(stmt, 1, usuario.usuario, strlen(usuario.usuario), SQLITE_STATIC);
	result = sqlite3_bind_text(stmt, 2, usuario.contrasenya, strlen(usuario.contrasenya), SQLITE_STATIC);
	result = sqlite3_bind_text(stmt, 3, usuario.nombre, strlen(usuario.nombre), SQLITE_STATIC);
	result = sqlite3_bind_text(stmt, 4, usuario.apellido, strlen(usuario.apellido), SQLITE_STATIC);
	result = sqlite3_bind_text(stmt, 5, textoFecha(usuario.fecNac), strlen(textoFecha(usuario.fecNac)), SQLITE_STATIC);
	result = sqlite3_bind_int(stmt, 6, usuario.telefono);
	result = sqlite3_bind_text(stmt, 7, (usuario.esSocio == 1 ? "SI" : "NO"), 2, SQLITE_STATIC);

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