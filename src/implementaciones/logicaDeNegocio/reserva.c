#include "../../declaraciones/logicaDeNegocio/reserva.h"
#include "../../declaraciones/gestionBD/getData.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void horareserva (char* hora){
    char num1="0";
    while (hora[3] != num1 && hora[4] != num1){
        fflush(stdout);
        printf("Hora seleccionada incorrecta \n Escriba la hora que desea la pista (Recuerda que solo se pueden servar las pista a empunto): hora:minuto  ");
        char* tiempo= (char*)malloc(6*sizeof(char));
        fgets(tiempo,6,stdin);
        scanf(tiempo,"%s",hora);
        printf("\n ");
        free(tiempo);
    }
}


