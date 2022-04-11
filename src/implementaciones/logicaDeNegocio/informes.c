#include "../../declaraciones/logicaDeNegocio/informes.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../declaraciones/logicaDeDatos/estructuras.h"

void ficheroCompras(ListaCompra* listaCompra){
    FILE* f;
    f = fopen("InformeCompras.txt","w");
    for (int i = 0; i < listaCompra->tamanyo; i++)
    {
        fprintf(f,"Codigo de compra: %i\n", listaCompra->arrayCompras[i].codigo);
        fprintf(f,"Fecha: %s\n", listaCompra->arrayCompras[i].fecha);
        fprintf(f,"Usuario: %s\n", listaCompra->arrayCompras[i].usuario);
        fprintf(f,"Codigo de articulo: %i\n", listaCompra->arrayCompras[i].codArt);
        fprintf(f,"Unidades: %i\n", listaCompra->arrayCompras[i].cantidad);
        fprintf(f,"Precio total: %i\n\n", listaCompra->arrayCompras[i].precio);
    }
    fclose(f);
    
}
