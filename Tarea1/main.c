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
#include <math.h>

void menu();

void interactiva(ListaEnlazada *Carrito,ColaCarrito *BandaT, Stack *Pila);

void automatica(ListaEnlazada *Carrito);

void moveralabanda(ListaEnlazada *Carrito, ColaCarrito *BandaT, int *volumen);

int procesamiento(ColaCarrito *BandaT,Stack *Pila,int *volumen);

int embolsar(Stack *Pila, ListaEnlazada *Bolsa, int *volumen);



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
                ColaCarrito *BandaT;
                Stack *Pila;
                Carrito = malloc(sizeof(ListaEnlazada));
                BandaT = malloc(sizeof(ColaCarrito));
                Pila = malloc(sizeof(Stack));
                Inicialize(Carrito);
                iniciarcola(BandaT);
                initialization(Pila);
                cantidaddecarritos = rand();
                Productos = LeerProductos();
                generarcarrito(Carrito); 
                if ( modalidad == "interactiva" ) interactiva(Carrito,BandaT,Pila);
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

void interactiva(ListaEnlazada *Carrito,ColaCarrito *BandaT, Stack *Pila){
	int tiempo = 0;
	int tiempoprocesamiento = 0;
	int tiempoinicio = 0;
	int facturacion = 0;
	int volumenbo = 0;
	int volumenbt = 0;
	ListaEnlazada *Bolsa;
	Inicialize(Bolsa);
	printf("Presiona Enter para iniciar la simulacion");
	fflush(stdin);
	getchar();
	do{
		printf("Lista de elementos aun en el carrito: ");
		imprimirlista(Carrito);
		printf("Lista de elementos en la banda transportadora: ");
		imprimircola(BandaT);
		printf("Lista de elementos en el area de embolsado: ");
		show(Pila);
		printf("Lista de elementos embolsados: "); //PENEDIENTE
		//imprimirlista(Cola);
		moveralabanda(Carrito,BandaT,&volumenbt);
		if(BandaT->nraiz->Dato->Peso+AreaPila(Pila) <= maxareaembolsado){
			if ((tiempo - tiempoprocesamiento) == tiempoinicio){
				tiempoinicio = tiempo;
				tiempoprocesamiento = procesamiento(BandaT,Pila,&volumenbt);
				if (tiempo>0){
					push(Pila,extraernodocola(BandaT));
				}
			}
		}
		if (Pila->head!=NULL){
			//if (embolsar(Pila,Bolsa,&volumenbo) == 1){
				// AGREGAMOS LA BOLSA A UNA LISTA DE APUNTADORES
				// CREAMOS UNA INSTANCIA NUEVA DE LA BOLSA
				//free(Bolsa);
			}
		}
		fflush(stdin);
		printf("\nPresiona Enter para continuar la simulacion: ");
		getchar();
		tiempo ++;
	}while (Carrito->head!=NULL || BandaT->nraiz!=NULL || Pila->head!=NULL);
}

void moveralabanda(ListaEnlazada *Carrito, ColaCarrito *BandaT, int *volumen){
	// DESPUES VERIFICAR SI EL OBJETO SUPERA LA CAPACIDAD DE LA BANDA
	while (Carrito->head->Dato->Peso + *volumen <= maxbt && Carrito->head != NULL){
		struct Producto *objeto = removeelementlist(Carrito);
		insertarnodocola(objeto, BandaT);
		*volumen += objeto->Peso;
	}
}

int procesamiento(ColaCarrito *BandaT,Stack *Pila,int *volumen){
	struct Producto *item = BandaT->nraiz->Dato;
	*volumen -= item -> Peso;
	return ceil(item->Complejidad / velocidadcajera); // FUNCION TECHO
}

int embolsar(Stack *Pila, ListaEnlazada *Bolsa, int *volumen){ //PASAR DE BANDA DE TRANSBORDADORA
	while (Pila->head->item->Peso + *volumen <= maxbolsa && Pila->head != NULL){
		struct Producto *objeto = pop(Pila);
		addelementlist(Bolsa,objeto);
		*volumen += objeto->Peso;
	}
	if (Pila->head->item->Peso + *volumen > maxbolsa){
		return 1;
	}
	else{
		return 0;
	}
}

void automatica(ListaEnlazada *Carrito){
}