#include "../../declaraciones/logicaDeNegocio/fechas.h"

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