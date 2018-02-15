/* IMPLEMENTACION DE LAS FUNCIONES DE PILA

Estudiantes:
- Ian Goldberg		# 14-10406
- Manuel Rodriguez	# 13-11223
- David Segura		# 13-11341
*/

#include "stack.h"

/******************** INITIALIZATION ********************/
/*
TIPO: Funcion 
DESCRIPCION: Inicializa la estructura de pila
ENTRADA: s ----> Stack */

void initialization(Stack *s){
	s->head = NULL;
	s->size = 0;
}

/************************** PUSH **************************/
/*
TIPO: Funcion 
DESCRIPCION: Agrega un elemento a la lista, de
			 esta manera se hace la operacion de apilar
ENTRADA: s ----> Stack
		 itm --> Producto
SALIDA:  int (-1 para error y 0 para exito) */

int push(Stack *s, struct Producto *itm){
	Element *new_element;
	if ((new_element = malloc (sizeof (Element))) == NULL) return -1;
	if ((new_element->item = malloc (sizeof (struct Producto))) == NULL) return -1;
	new_element->item = itm;
	new_element->next = s->head;
	s->head = new_element;
	s->size++;
	return 0;
}

/************************** POP **************************/
/*
TIPO: Funcion 
DESCRIPCION: Elimina un elemento de la lista y se retorna,
			 de esta manera se hace la operacion de desenpilar
ENTRADA: s ----> Stack
SALIDA:  recovery ---> struct Producto (retorna NULL si hubo
					   error y retorna la estructura en caso
					   contrario) */

struct Producto *pop(Stack *s){
	Element *del_element;
	struct Producto *recovery;
	if (s->size == 0) return NULL;
	del_element = s->head;
	recovery = s->head->item;
	s->head = s->head->next;
	free (del_element);
	s->size--;
	if(s->size == 0) s->head = NULL;
	return recovery;
}

/************************** SHOW **************************/
/*
TIPO: Funcion 
DESCRIPCION: Muestra los elementos de la pila
ENTRADA: s ----> Stack */

void show(Stack *s){
	Element *actual;
	int i;
	actual = s->head;
	for(i=0; i < s->size;i++){
		if(i == (s->size)-1){
			printf("%s\n", actual->item->Nombre);
		}else{
			printf("%s - ", actual->item->Nombre);
			actual = actual->next;
		}
	}
	printf("\n");
}

/******************** AREAPILA ********************/
/*
TIPO: Funcion 
DESCRIPCION: Calcula la cantidad en peso que hay en el
			 area de embolsado en base a la pila.
ENTRADA: s ----> Stack 
SALIDA:  area --> Cantidad en peso en el area de la pila*/

int AreaPila(Stack *s){
	Element *actual;
	actual = s->head;
	int area = 0;
	for(int i=0; i < s->size;i++){
		area += actual->item->Peso;
		actual = actual->next;
	}
	return area;
}