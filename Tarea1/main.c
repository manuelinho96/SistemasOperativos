#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "producto.h"
#include "cola.h"
#include "stack.h"
#include "ListaEnlazada.c"
#include "configuracion.h"
#include "simulacion.c"
#include <time.h>

void menu();

void interactiva(ListaEnlazada *Carrito);

void automatica(ListaEnlazada *Carrito);

int main (){
    int opcion;
    while(1){
        menu();
        while(1){
            printf("Ingrese una opcion: ");
            scanf("%d", &opcion);
            if ( opcion == 1 ){
                srand(time(NULL));
                ListaEnlazada *Carrito;
                ListaEnlazada *BandaT;
                Carrito = malloc(sizeof(ListaEnlazada));
                Inicialize(Carrito);
                Inicialize(BandaT);
                cantidaddecarritos = rand();
                Productos = LeerProductos();
                if ( modalidad == "interactiva" ) interactiva(Carrito);
                else{
                    automatica(Carrito);
                } 
            }
            else if ( opcion == 2 ){
                configuracion();
            }
            else if (opcion == 3){
                return 0;
            }
            else{
                printf("Introdujo una opcion erronea");
            }
            break;
        }
    }
}

void menu(){
    printf("1. Ejecutar la Simulacion\n");
    printf("2. Cambiar las opciones de la simulacion\n");
    printf("3. Salir del programa\n");
}

void interactiva(ListaEnlazada *Carrito){

}

void automatica(ListaEnlazada *Carrito){
    
}