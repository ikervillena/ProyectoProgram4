#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../declaraciones/gestionBD/getData.h"
#include "../../declaraciones/logicaDePresentacion/visualizar.h"
#include "../../declaraciones/gestionBD/insertData.h"

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

	int numFilas = 0;
	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			numFilas++;
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
			if(strcmp(sqlite3_column_text(stmt, 7), "SI") == 0){
				usuario->esSocio = 1;
			} else{
				usuario->esSocio = 0;
			}
            
		}
	} while (result == SQLITE_ROW);

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}
	return usuario;
}

int parejaLibre(Fecha fecTorn, Usuario usu1, Usuario usu2) {
	startConn();
	char sql[] = "SELECT fec_torneo, usuario1, usuario2 FROM pareja p, inscripcion i, torneo t "
	"WHERE p.cod_pareja = i.cod_pareja AND i.cod_torneo = t.cod_torneo";
    sqlite3_stmt *stmt;
	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	int parejaLibre = 1;
	do {
		result = sqlite3_step(stmt);

		if (result == SQLITE_ROW) {
			char fecha[strlen(sqlite3_column_text(stmt, 0)) + 1];
			strcpy(fecha, sqlite3_column_text(stmt, 0));
			fecha[strlen(sqlite3_column_text(stmt, 0))] = '\0';
			char us1[strlen(sqlite3_column_text(stmt, 1)) + 1];
			strcpy(us1, sqlite3_column_text(stmt, 1));
			us1[strlen(sqlite3_column_text(stmt, 2))] = '\0';
			char us2[strlen(sqlite3_column_text(stmt, 0)) + 1];
			strcpy(us2, sqlite3_column_text(stmt, 2));
			us2[strlen(sqlite3_column_text(stmt, 2))] = '\0';

			if(strcmp(textoFecha(fecTorn), fecha) == 0 && 
			(strcmp(us1, usu1.usuario) == 0 || strcmp(us1, usu2.usuario) == 0 ||
			strcmp(us2, usu1.usuario) == 0 || strcmp(us2, usu2.usuario) == 0)){
				parejaLibre = 0;
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
	return parejaLibre;
}

int* getreservas(char* pista,char* fecha,char*hora){  
	startConn();
	char sql[] = "SELECT NUM_PISTA FROM(SELECT B.NUM_PISTA, FECHA, HORA FROM reserva B JOIN (SELECT NUM_PISTA FROM pista WHERE TIPO_PISTA = ? ) A ON B.NUM_PISTA = A.NUM_PISTA) WHERE FECHA != ? AND HORA != ? ";
    sqlite3_stmt *stmt;
	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	if (result == SQLITE_OK) {
		sqlite3_bind_text(stmt, 1, pista, strlen(pista), SQLITE_STATIC);
		sqlite3_bind_text(stmt, 2, fecha, strlen(fecha), SQLITE_STATIC);
		sqlite3_bind_text(stmt, 3, hora, strlen(hora), SQLITE_STATIC);

	} else{
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}
	int *pistasDisponibles = (int*)malloc(6*sizeof(int));
	int i = 0;
	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {	
			pistasDisponibles[i] = sqlite3_column_int(stmt, 0);
			i++;
		}
	} while (result == SQLITE_ROW);

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}
	return pistasDisponibles;         
}

int tamanyoLista(int COD_TIPO_ART){
	int tamanyo=0;
	startConn();
	char sql[] = "SELECT COUNT(*) FROM articulo WHERE COD_TIPO_ART = ?";
    sqlite3_stmt *stmt;
	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, COD_TIPO_ART);
	} else{
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}
	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {	
			tamanyo = sqlite3_column_int(stmt, 0);
		}
	}while (result == SQLITE_ROW);

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}
	return tamanyo;
}


ListaArticulos *getArticulo(int COD_TIPO_ART, int tamanyo){
	startConn();
	char sql[] = "SELECT * FROM articulo WHERE COD_TIPO_ART = ?";
    sqlite3_stmt *stmt;
	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	if (result == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, COD_TIPO_ART);
	} else{
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}
	ListaArticulos *listaArticulos=(ListaArticulos*)malloc(tamanyo*sizeof(ListaArticulos));
	listaArticulos->tamanyo=tamanyo;
	listaArticulos->articulos = (Articulo*)malloc(sizeof(Articulo));
	int contador = 0;
	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {			
			
			listaArticulos->articulos[contador].codigo=sqlite3_column_int(stmt, 0);
			listaArticulos->articulos[contador].tipo=(char *) malloc((strlen(sqlite3_column_text(stmt,1)) + 1)*sizeof(char));
			listaArticulos->articulos[contador].tipo=strcpy(listaArticulos->articulos[contador].tipo,sqlite3_column_text(stmt,1));
			listaArticulos->articulos[contador].tipo[strlen(sqlite3_column_text(stmt,1))]='\0';
			listaArticulos->articulos[contador].marca=(char *) malloc((strlen(sqlite3_column_text(stmt,2)) + 1)*sizeof(char));
			listaArticulos->articulos[contador].marca=strcpy(listaArticulos->articulos[contador].marca,sqlite3_column_text(stmt,2));
			listaArticulos->articulos[contador].marca[strlen(sqlite3_column_text(stmt,2))]='\0';
			listaArticulos->articulos[contador].nombre=(char *) malloc((strlen(sqlite3_column_text(stmt,3)) + 1)*sizeof(char));
			listaArticulos->articulos[contador].nombre=strcpy(listaArticulos->articulos[contador].nombre,sqlite3_column_text(stmt,3));
			listaArticulos->articulos[contador].nombre[strlen(sqlite3_column_text(stmt,3))]='\0';
			listaArticulos->articulos[contador].descripcion=(char *) malloc((strlen(sqlite3_column_text(stmt,4)) + 1)*sizeof(char));
			listaArticulos->articulos[contador].descripcion=strcpy(listaArticulos->articulos[contador].descripcion,sqlite3_column_text(stmt,4));
			listaArticulos->articulos[contador].descripcion[strlen(sqlite3_column_text(stmt,4))]='\0';
			listaArticulos->articulos[contador].precio=(char *) malloc((strlen(sqlite3_column_text(stmt,5)) + 1)*sizeof(char));
			listaArticulos->articulos[contador].precio=strcpy(listaArticulos->articulos[contador].precio,sqlite3_column_text(stmt,5));
			listaArticulos->articulos[contador].precio[strlen(sqlite3_column_text(stmt,5))]='\0';
			
			contador++;
			
		}

	} while (result == SQLITE_ROW);

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}
	return listaArticulos;
}

int getNumPistas(char* pista, char* fecha, char* hora){
	startConn();
	char sql[] = "SELECT NUM_PISTA FROM(SELECT B.NUM_PISTA, FECHA, HORA FROM reserva B JOIN (SELECT NUM_PISTA FROM pista WHERE TIPO_PISTA = ? ) A ON B.NUM_PISTA = A.NUM_PISTA) WHERE FECHA != ? AND HORA != ?";
	sqlite3_stmt *stmt;
	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	
	if (result == SQLITE_OK) {
		sqlite3_bind_text(stmt, 1, pista, strlen(pista), SQLITE_STATIC);
		sqlite3_bind_text(stmt, 2, fecha, strlen(fecha), SQLITE_STATIC);
		sqlite3_bind_text(stmt, 3, hora, strlen(hora), SQLITE_STATIC);

	} else{
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}
	int numFilas = 0;
	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			numFilas++;
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

int imprimirProximosTorneos(){
	startConn();
	sqlite3_stmt *stmt;
	char sql[] = "SELECT * FROM torneo WHERE cod_par_gan IS NULL";
	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;

	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	int cod;
	char fecha[100];

	printf("Proximos torneos:\n\n");
	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			cod = sqlite3_column_int(stmt, 0);
			strcpy(fecha, (char *) sqlite3_column_text(stmt, 1));
			printf("\t[Codigo de torneo: %d. Fecha: %s]\n\n", cod, fecha);
		}
	} while (result == SQLITE_ROW);

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	return SQLITE_OK;
}

int inscripcionesAbiertas(int codTorneo) {
	char sql[] = "SELECT * FROM torneo WHERE cod_par_gan IS NULL and cod_torneo = ";
	char str[5];
  	sprintf(str, "%d", codTorneo);
    strcat(sql, str);
	if(getNumFilas(sql) > 0) {
		return 1;
	} else{
		return 0;
	}
}

int getCodigoPareja(Usuario usuario1, Usuario usuario2) {
	char sql[] = "SELECT cod_pareja FROM pareja WHERE (usuario1 = ? AND usuario2 = ?)"
		"OR (usuario1 = ? AND usuario2 = ?)";

	int codPareja = 0;
	startConn();
	sqlite3_stmt *stmt;
	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	if (result == SQLITE_OK) {
		sqlite3_bind_text(stmt, 1, usuario1.usuario, strlen(usuario1.usuario), SQLITE_STATIC);
		sqlite3_bind_text(stmt, 2, usuario2.usuario, strlen(usuario2.usuario), SQLITE_STATIC);
		sqlite3_bind_text(stmt, 3, usuario2.usuario, strlen(usuario2.usuario), SQLITE_STATIC);
		sqlite3_bind_text(stmt, 4, usuario1.usuario, strlen(usuario1.usuario), SQLITE_STATIC);
	} else{
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}

	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {			
			codPareja = sqlite3_column_int(stmt, 0);
		}
	} while (result == SQLITE_ROW);

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}
	return codPareja;
}

int getNumInscripciones(int codTorneo) {
	char sql[] = "SELECT * FROM inscripcion WHERE cod_torneo = ";
    char str[5];
  	sprintf(str, "%d", codTorneo);
    strcat(sql, str);
    return getNumFilas(sql);
}

int *getInscripciones(int codTorneo) {
	startConn();
	char sql[] = "SELECT cod_pareja FROM inscripcion WHERE cod_torneo = ?";
	sqlite3_stmt *stmt;
	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	if (result == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, codTorneo);
	} else{
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}

	int *parejasInscritas = (int *) malloc(getNumInscripciones(codTorneo) * sizeof(int));
	int contador = 0;

	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {			
			parejasInscritas[contador] = sqlite3_column_int(stmt, 0);
			contador++;
		}
	} while (result == SQLITE_ROW);

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}
	return parejasInscritas;
}

int ganadorAsignado(int codTorneo) {
	char sql[] = "SELECT * FROM torneo WHERE cod_par_gan = 0 AND cod_torneo = ";
	char str[5];
  	sprintf(str, "%d", codTorneo);
    strcat(sql, str);
	if(getNumFilas(sql) > 0) {
		return 0;
	} else{
		return 1;
	}
}

int imprimirTorneosCerrados() {
	startConn();
	sqlite3_stmt *stmt;
	char sql[] = "SELECT * FROM torneo WHERE cod_par_gan = 0";
	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;

	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	int cod;
	char fecha[100];

	printf("Proximos torneos:\n\n");
	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			cod = sqlite3_column_int(stmt, 0);
			strcpy(fecha, (char *) sqlite3_column_text(stmt, 1));
			printf("\t[Codigo de torneo: %d. Fecha: %s]\n\n", cod, fecha);
		}
	} while (result == SQLITE_ROW);

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	return SQLITE_OK;
}

int ganadorValido(int codTorneo, int codPareja) {
	startConn();
	char sql[] = "SELECT * FROM inscripcion WHERE cod_torneo = ? AND cod_pareja = ?";
	sqlite3_stmt *stmt;
	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	if (result == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, codTorneo);
		sqlite3_bind_int(stmt, 2, codPareja);
	} else{
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}
	int ganadorValido = 0;
	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {			
			ganadorValido = 1;
		}
	} while (result == SQLITE_ROW);

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}
	return ganadorValido;
}

int estaInscrito(int codTorneo, Usuario usuario) {
	startConn();
	char sql[] = "SELECT cod_torneo, usuario1, usuario2 FROM inscripcion I, pareja P "
	"WHERE I.cod_pareja = P.cod_pareja AND I.cod_torneo = ? AND (P.usuario1 = ? OR P.usuario2 = ?)";
	sqlite3_stmt *stmt;
	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	if (result == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, codTorneo);
		sqlite3_bind_text(stmt, 2, usuario.usuario, strlen(usuario.usuario), SQLITE_STATIC);
		sqlite3_bind_text(stmt, 3, usuario.usuario, strlen(usuario.usuario), SQLITE_STATIC);
	} else{
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}

	int estaInscrito = 0;

	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {			
			estaInscrito = 1;
		}
	} while (result == SQLITE_ROW);

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}
	return estaInscrito;
}

int imprimirSiguientesTorneos(Usuario usuario) {
	startConn();
	sqlite3_stmt *stmt;
	char sql[] = "SELECT * FROM torneo WHERE cod_par_gan = 0";
	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;

	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	int cod;
	char fecha[100];

	printf("Proximos torneos:\n\n");
	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			cod = sqlite3_column_int(stmt, 0);
			strcpy(fecha, (char *) sqlite3_column_text(stmt, 1));
			if(estaInscrito(cod, usuario)){
				printf("\t[Codigo de torneo: %d. Fecha: %s. Estas inscrito: SI]\n\n", cod, fecha);
			} else{
				printf("\t[Codigo de torneo: %d. Fecha: %s. Estas inscrito: NO]\n\n", cod, fecha);
			}
			
		}
	} while (result == SQLITE_ROW);

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	return SQLITE_OK;
}

int usuarioLibre(char *nomUsuario) {
	char sql[] = "SELECT * FROM usuario WHERE usuario = '";
	strcat(sql, nomUsuario);
	strcat(sql, "'");
	if(getNumFilas(sql) > 0) {
		return 0;
	} else{
		return 1;
	}
}

int tamanyoListaCompra(){
	int tamanyo=0;
	startConn();
	char sql[] = "SELECT COUNT(*) FROM compra";
    sqlite3_stmt *stmt;
	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	
	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {	
			tamanyo = sqlite3_column_int(stmt, 0);
		}
	}while (result == SQLITE_ROW);

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}
	return tamanyo;
}

ListaCompra *getCompras(int tamanyo){
	startConn();
	char sql[] = "SELECT * FROM compra ";
    sqlite3_stmt *stmt;
	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	ListaCompra *listaCompras=(ListaCompra*)malloc(tamanyo*sizeof(ListaCompra));
	listaCompras->tamanyo=tamanyo;
	listaCompras->arrayCompras = (Compra*)malloc(sizeof(Compra));
	int contador = 0;
	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {			
			listaCompras->arrayCompras[contador].codigo=sqlite3_column_int(stmt, 0);
			listaCompras->arrayCompras[contador].usuario=(char *) malloc((strlen(sqlite3_column_text(stmt,1)) + 1)*sizeof(char));
			listaCompras->arrayCompras[contador].usuario=strcpy(listaCompras->arrayCompras[contador].usuario,sqlite3_column_text(stmt,1));
			listaCompras->arrayCompras[contador].usuario[strlen(sqlite3_column_text(stmt,1))]='\0';

			listaCompras->arrayCompras[contador].codArt=sqlite3_column_int(stmt, 2);
			
			listaCompras->arrayCompras[contador].cantidad=sqlite3_column_int(stmt, 3);
			
			listaCompras->arrayCompras[contador].fecha=(char *) malloc((strlen(sqlite3_column_text(stmt,4)) + 1)*sizeof(char));
			listaCompras->arrayCompras[contador].fecha=strcpy(listaCompras->arrayCompras[contador].fecha,sqlite3_column_text(stmt,4));
			listaCompras->arrayCompras[contador].fecha[strlen(sqlite3_column_text(stmt,4))]='\0';

			listaCompras->arrayCompras[contador].precio=sqlite3_column_int(stmt, 5);
					
			contador++;
		}

	} while (result == SQLITE_ROW);

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}
	return listaCompras;
}

int tamanyoListaReservas(){
	int tamanyo=0;
	startConn();
	char sql[] = "SELECT COUNT(*) FROM reserva";
    sqlite3_stmt *stmt;
	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	
	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {	
			tamanyo = sqlite3_column_int(stmt, 0);
		}
	}while (result == SQLITE_ROW);

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}
	return tamanyo;
}

ListaReservas *getReservas(int tamanyo, char* fecha){
	startConn();
	char sql[] = "SELECT * FROM reserva WHERE FECHA = ?";
    sqlite3_stmt *stmt;
	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	if (result == SQLITE_OK) {
		sqlite3_bind_text(stmt, 1, fecha, strlen(fecha), SQLITE_STATIC);
	} else{
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}

	ListaReservas * listaReservas = (ListaReservas*)malloc(sizeof(ListaReservas));
	listaReservas->tamanyo=tamanyo;
	listaReservas->arrayReservas = (Reservas*)malloc(sizeof(Reservas));
	int contador = 0;
	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {			
			listaReservas->arrayReservas[contador].codigo=sqlite3_column_int(stmt, 0);
			listaReservas->arrayReservas[contador].usuario=(char *) malloc((strlen(sqlite3_column_text(stmt,1)) + 1)*sizeof(char));
			listaReservas->arrayReservas[contador].usuario=strcpy(listaReservas->arrayReservas[contador].usuario,sqlite3_column_text(stmt,1));
			listaReservas->arrayReservas[contador].usuario[strlen(sqlite3_column_text(stmt,1))]='\0';

			listaReservas->arrayReservas[contador].numPista=sqlite3_column_int(stmt, 2);
			
			listaReservas->arrayReservas[contador].fecha=(char *) malloc((strlen(sqlite3_column_text(stmt,3)) + 1)*sizeof(char));
			listaReservas->arrayReservas[contador].fecha=strcpy(listaReservas->arrayReservas[contador].fecha,sqlite3_column_text(stmt,3));
			listaReservas->arrayReservas[contador].fecha[strlen(sqlite3_column_text(stmt,3))]='\0';

			listaReservas->arrayReservas[contador].hora=(char *) malloc((strlen(sqlite3_column_text(stmt,4)) + 1)*sizeof(char));
			listaReservas->arrayReservas[contador].hora=strcpy(listaReservas->arrayReservas[contador].hora,sqlite3_column_text(stmt,4));
			listaReservas->arrayReservas[contador].hora[strlen(sqlite3_column_text(stmt,4))]='\0';

			listaReservas->arrayReservas[contador].precio = sqlite3_column_int(stmt, 5);
					
			contador++;
		}
	} while (result == SQLITE_ROW);

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}
	return listaReservas;
}