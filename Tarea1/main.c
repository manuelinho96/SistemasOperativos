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

<<<<<<< HEAD
void simulacion(ListaEnlazada *Carrito,ColaCarrito *BandaT, Stack *Pila, ListaEnlazada *Bolsas,const char *modalidad, int numerocarritos);
=======
void simulacion(ListaEnlazada *Carrito,ColaCarrito *BandaT, Stack *Pila, ListaEnlazada *Bolsas,const char *modalidad,int numerocarrito,int *numerocliente);
>>>>>>> TiendaDavid

void moveralabanda(ListaEnlazada *Carrito, ColaCarrito *BandaT, int *volumen);

int procesamiento(Producto *Producto,int *volumen);

void embolsar(Stack *Pila, ListaEnlazada *Bolsa);

int main (int argc, char *argv[]){
	if (argc <= 1){
		printf("No se introdujo un nombre de archivo de inventario, error.\n");
		return 1;
	}
	else if(argc == 2){
		Productos = LeerProductos(argv[1]);
		if(Productos == NULL){
			printf("Error al abrir el archivo de entrada\n");
			return 1;
		}
	}else{
		printf("Se introdujo mas parametros de los permitidos\n");
		return 1;
	}
    int opcion = 0;
    while(1){
        menu();
        while(1){
            printf("Ingrese una opcion: ");
            scanf("%d", &opcion);
<<<<<<< HEAD
            if ( opcion == 1 ){
            	printf("entre");
            	for(int i = 0; i < carritoEnCola; i++){   
=======
            if (opcion == 1){
            	int tiempoclientes[carritoEnCola];
            	int tiempototal = 0;
				int numproductscarrito[carritoEnCola];
            	for(int i = 0; i < carritoEnCola; i++){
>>>>>>> TiendaDavid
	                srand(time(NULL));
	                ListaEnlazada *Carrito;
	                ColaCarrito *BandaT;
	                Stack *Pila;
					ListaEnlazada *Bolsas;
<<<<<<< HEAD
	                Carrito = malloc(sizeof(ListaEnlazada));
	                BandaT = malloc(sizeof(ColaCarrito));
	                Pila = malloc(sizeof(Stack));
					Bolsas = malloc(sizeof(ListaEnlazada));
=======
	                if ((Carrito = malloc(sizeof(ListaEnlazada)))==NULL) return -1;
	                if ((BandaT = malloc(sizeof(ColaCarrito)))==NULL) return -1;
	                if ((Pila = malloc(sizeof(Stack)))==NULL) return -1;
					if ((Bolsas = malloc(sizeof(ListaEnlazada)))==NULL) return -1;
>>>>>>> TiendaDavid
	                Inicialize(Carrito);
	                iniciarcola(BandaT);
	                initialization(Pila);
					Inicialize(Bolsas);
<<<<<<< HEAD
	                Productos = LeerProductos();
	                generarcarrito(Carrito);
	                simulacion(Carrito,BandaT,Pila,Bolsas,modalidad, 1);
	            }
=======
	                numproductscarrito[i] = generarcarrito(Carrito);
	                simulacion(Carrito,BandaT,Pila,Bolsas,modalidad,i,tiempoclientes);
	                free(Carrito);
	                free(BandaT);
	                free(Pila);
	                removelist(Bolsas);
	                free(Bolsas); 
            	}
            	for (int j = 0;j<carritoEnCola;j++){
            		printf("Tiempo del cliente %d: %d\n",j+1,tiempoclientes[j]);
            		tiempototal += tiempoclientes[j];
            	}
            	printf("TIEMPO TOTAL: %d\n",tiempototal);
				writelogfile(carritoEnCola, numproductscarrito, tiempoclientes, tiempototal, argv[1]);
>>>>>>> TiendaDavid
            }
            else if (opcion == 2){
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

<<<<<<< HEAD
void simulacion(ListaEnlazada *Carrito,ColaCarrito *BandaT, Stack *Pila, ListaEnlazada *Bolsas,const char *modalidad, int numerocarritos){
=======
void simulacion(ListaEnlazada *Carrito,ColaCarrito *BandaT, Stack *Pila, ListaEnlazada *Bolsas,const char *modalidad,int numerocarrito,int *tiempoclientes){
>>>>>>> TiendaDavid
	int tiempo = 0;
	int tiempoprocesamiento = 0;
	int tiempoinicio = 0;
	int facturacion = 0;
	int volumenbt = 0;
	ListaEnlazada *Bolsa;
	struct Producto *Producto;
	fflush(stdin);
	printf("Presiona Enter para iniciar la simulacion\n");
	getchar();
	if (modalidad == "Interactiva"){
		printf("Lista de elementos en el carrito: ");
		imprimirlista(Carrito);
		printf("Lista de elementos en la banda transportadora: ");
		imprimircola(BandaT);
		printf("Lista de elementos en el area de embolsado: ");
		show(Pila);
		printf("Lista de elementos embolsados: \n");
		imprimirlistabolsa(Bolsas);
	}
	do{
		if (Carrito->head != NULL){
			moveralabanda(Carrito,BandaT,&volumenbt);
		}
		if (BandaT->nraiz != NULL){
			if((BandaT->nraiz->Dato->Peso+AreaPila(Pila) <= maxareaembolsado)|| 
			(BandaT->nraiz->Dato->Peso > maxareaembolsado && Pila->size == 0)){
				if ((tiempo - tiempoprocesamiento) == tiempoinicio){
					tiempoinicio = tiempo;
					if(BandaT->nraiz->Dato->Peso <= maxbolsa && tiempo > 0){
						volumenbt -= BandaT->nraiz->Dato->Peso;
						push(Pila,extraernodocola(BandaT));
					}else{
						if(tiempo > 0){
							volumenbt -= BandaT->nraiz->Dato->Peso;
							anadirbolsa2(Bolsas, extraernodocola(BandaT));
						}
					}
					if (BandaT->nraiz != NULL){
						Producto = BandaT->nraiz->Dato;
						tiempoprocesamiento = Producto->Complejidad / velocidadcajera;
					}
				}
			}else{;
				tiempoinicio++;
			}
		}
		if (Pila->head!=NULL && tiempo % velocidadembolsador == 0){
			if ((Bolsa = malloc(sizeof(ListaEnlazada)))==NULL) return;
			Inicialize(Bolsa);
			embolsar(Pila,Bolsa);
			ListaEnlazada *BolsaAuxiliar;
			if ((BolsaAuxiliar = malloc(sizeof(Bolsa)))==NULL) return;
			memcpy(BolsaAuxiliar, Bolsa, sizeof(Bolsa));
			anadirbolsa(Bolsas, BolsaAuxiliar);
			free(Bolsa);
		}
		if(tiempo>0 && modalidad == "Interactiva"){
			printf("Lista de elementos en el carrito: ");
			imprimirlista(Carrito);
			printf("\nLista de elementos en la banda transportadora: ");
			imprimircola(BandaT);
			printf("\nLista de elementos en el area de embolsado: ");
			show(Pila);
			printf("\nLista de elementos embolsados: \n");
			imprimirlistabolsa(Bolsas);
		}
		fflush(stdin);
		printf("Presiona Enter para continuar la simulacion: \n");
		getchar();
		tiempo ++;
	}while (Carrito->head != NULL || BandaT->nraiz != NULL || Pila->head !=NULL);
	tiempoclientes[numerocarrito] = tiempo + tiempofacturacion;
}

void moveralabanda(ListaEnlazada *Carrito, ColaCarrito *BandaT, int *volumen){
	while (Carrito->head->Dato->Peso + *volumen <= maxbt && Carrito->head != NULL){
		struct Producto *objeto = removeelementlist(Carrito);
		insertarnodocola(objeto, BandaT);
		*volumen += objeto->Peso;
		if (Carrito->head == NULL){
			break;
		}
	}
	if(BandaT->nraiz == NULL && Carrito->head->Dato->Peso > maxbt){
		struct Producto *objeto = removeelementlist(Carrito);
		insertarnodocola(objeto, BandaT);
	}
}

void embolsar(Stack *Pila, ListaEnlazada *Bolsa){
	int volumen = 0;
	while (1){
		if (Pila->head == NULL){
			break;
		}
		else if (Pila->head->item->Peso + volumen <= maxbolsa){
			struct Producto *objeto = pop(Pila);
			addelementlist(Bolsa,objeto);
			volumen += objeto->Peso;
		}
		else{
			break;
		}
	}
}