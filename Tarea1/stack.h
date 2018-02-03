/* IMPLEMENTACION DE LA ESTRUCTURA DE DATOS PILA

Estudiantes:
- Ian Goldberg		# 14-10406
- Manuel Rodriguez	# 13-11223
- David Segura		# 13-11341
*/

#include<stdlib.h>

/************************ LISTELEMENT ************************/
/*
TIPO: Estructura de datos
DESCRIPCION: Implementacion de un nodo que contendra dos
estructuras para simular una lista simple */
typedef struct ListElement{
	char *item; //struct Producto *item; 
	struct ListElement *next;
}Element;

/************************ LISTELEMENT ************************/
/*
TIPO: Estructura de datos
DESCRIPCION: Implementacion de un nodo que contendra una
estructura con el primer elemento de la lista y un entero
que representara la cantidad de elementos en la lista, simulando
de esta manera una pila */
typedef struct ListLocation{
	Element *head;
	int size;
}Stack;

/******************** INITIALIZATION ********************/
/*
TIPO: Funcion 
DESCRIPCION: Funcion que inicializa la estructura de pila
			 mediante listas
ENTRADA: s ----> Stack */
void initialization(Stack *s){
	s->head = NULL;
	s->size = 0;
}
/************************** PUSH **************************/
/*
TIPO: Funcion 
DESCRIPCION: Funcion que agrega un elemento a la lista, de
			 esta manera se hace la operacion de apilar
ENTRADA: s ----> Stack
		 i ----> Producto
SALIDA:  int (-1 para error y 0 para exito) */
int push(Stack *s, char *itm){
	Element *new_element;
	if ((new_element = (Element *) malloc (sizeof (Element))) == NULL) return -1;
	if ((new_element->item = (char *) malloc (50 * sizeof (char))) == NULL) return -1;
	strcpy (new_element->item, itm);
	new_element->next = s->head;
	s->head = new_element;
	s->size++;
	return 0;
}
/************************** POP **************************/
/*
TIPO: Funcion 
DESCRIPCION: Funcion que elimina un elemento a la lista, de
			 esta manera se hace la operacion de desenpilar
ENTRADA: s ----> Stack
SALIDA:  int (-1 para error y 0 para exito) */
int pop(Stack *s){
	Element *del_element;
	if (s->size == 0) return -1;
	del_element = s->head;
	s->head = s->head->next;
	free (del_element->item);
	free (del_element);
	s->size--;
	return 0;
}
/* Visualización del elemento en la cabeza de la pila (LastInFirstOut) */
#define stack_data(s) s->head->item
/************************** SHOW **************************/
/*
TIPO: Funcion 
DESCRIPCION: Funcion que muestra los elementos de la pila
ENTRADA: s ----> Stack */
void show(Stack *s){
	Element *actual;
	int i;
	actual = s->head;
	for(i=0; i < s->size;i++){
		printf("\t\t%s\n", actual->item);
		actual = actual->next;
	}
}