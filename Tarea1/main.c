#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "producto.h"
#include "cola.h"
#include "stack.h"
#include "ListaEnlazada.c"
#include "configuracion.h"
#include "simulacion.h"

void menu();

int main (){

    int opcion;
    while(1){
        menu();
        while(1){
            printf("Ingrese una opcion: ");
            scanf("%d", &opcion);
            if ( opcion == 1 ){
                simulacion();
                break;
            }
            if ( opcion == 2 ){
                configuracion();
                break;
            }
        }
    }
}

void menu(){
    printf("1. Ejecutar la Simulacion\n");
    printf("2. Cambiar las opciones de la simulacion\n");
    printf("3. Salir del programa\n");
}