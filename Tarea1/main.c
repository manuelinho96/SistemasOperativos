#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "stack.h"


int main (){
	Stack *tas;
	char *nom;
	struct Producto *p1;
	if ((p1 = (struct Producto *) malloc (sizeof (struct Producto))) == NULL) return -1;
	if ((tas = (Stack *) malloc (sizeof (Stack))) == NULL) return -1;
	if ((nom = (char *) malloc (50 * sizeof (char))) == NULL) return -1;
	initialization(tas);
	printf ("Ingrese una palabra: ");
	scanf ("%s", nom);
	strcpy(p1->Nombre , nom);
	push(tas, p1);
	printf("La pila (%d elementos): \n",tas->size);
	printf("\n********** Cabeza de la PILA **********\n");
	show(tas);
	printf("__________ Bajo de la PILA __________\n\n");
	printf ("Ingrese una palabra: ");
	scanf ("%s", nom);
	struct Producto *p2;
	if ((p2 = (struct Producto *) malloc (sizeof (struct Producto))) == NULL) return -1;
	strcpy(p2->Nombre , nom);
	push (tas, p2);
	printf ("La pila (%d elementos): \n",tas->size);
	printf("\n********** Cabeza de la PILA **********\n");
	show(tas);
	printf("__________ Bajo de la PILA __________\n\n");
	printf ("Ingrese una palabra: ");
	scanf ("%s", nom);
	struct Producto *p3;
	if ((p3 = (struct Producto *) malloc (sizeof (struct Producto))) == NULL) return -1;
	strcpy(p3->Nombre , nom);
	push (tas, p3);
	printf ("La pila (%d elementos): \n",tas->size);
	printf("\n********** Cabeza de la PILA **********\n");
	show(tas);
	printf("__________ Bajo de la PILA __________\n\n");
	printf ("\nLa ultima entrada (LastInFirstOut) [ %s ] sera eliminada", stack_data(tas));
	printf ("\nLa ultima entrada es eliminada\n");
	pop (tas);
	/* eliminación del ultimo elemento ingresado */
	printf ("La pila (%d elementos): \n",tas->size);
	printf("\n********** Cabeza de la PILA **********\n");
	show(tas);
	printf("__________ Bajo de la PILA __________\n\n");
	return 0;
}