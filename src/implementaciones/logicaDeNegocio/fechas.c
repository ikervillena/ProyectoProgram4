#include "../../declaraciones/logicaDeNegocio/fechas.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>

int compFecha(Fecha fec1, Fecha fec2) {
    int comp = 0;
    if(fec1.anyo == fec2.anyo){
        if(fec1.mes == fec2.mes) {
            if(fec1.dia > fec2.dia){
                comp = 1;
            } else {
                if(fec1.dia != fec2.dia){
                    comp = -1;
                }
            }
        } else{
            if(fec1.mes > fec2.mes) {
                comp = 1;
            } else{
                comp = -1;
            }
        }
    } else{
        if(fec1.anyo > fec2.anyo){
            comp = 1;
        } else{
            comp = -1;
        }
    }
    return comp;
}

//Convierte un int en un char.
char intToChar(int a){
	char c = a + '0';
	return c;
}

char* textoFecha(Fecha fec){
    char* texto = malloc(11 * sizeof(char));
    texto[0] = intToChar(fec.dia/10%10);
    texto[1] = intToChar(fec.dia%10);
    texto[2] = '-';
    texto[3] = intToChar(fec.mes/10%10);
    texto[4] = intToChar(fec.mes%10);
    texto[5] = '-';
    texto[6] = intToChar(fec.anyo/1000%10);
    texto[7] = intToChar(fec.anyo/100%10);
    texto[8] = intToChar(fec.anyo/10%10);
    texto[9] = intToChar(fec.anyo%10);
    texto[10] = '\0';
    return texto;
}

char* fechaActual(char* fechayhora){
    time_t t;
    struct tm *tm;
    t=time(NULL);
    tm=localtime(&t);
    strftime(fechayhora, 100, "%d/%m/%Y", tm);
    
    return fechayhora;
}   
