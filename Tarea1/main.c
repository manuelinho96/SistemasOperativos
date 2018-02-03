#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "stack.h"

int main (){
	Stack *tas;
	char *nom;
	if ((tas = (Stack *) malloc (sizeof (Stack))) == NULL) return -1;
	if ((nom = (char *) malloc (50 * sizeof (char))) == NULL) return -1;
	initialization(tas);
	printf ("Ingrese una palabra: ");
	scanf ("%s", nom);
	push(tas, nom);
	printf("La pila (%d elementos): \n",tas->size);
	printf("\n********** Cabeza de la PILA **********\n");
	show(tas);
	printf("__________ Bajo de la PILA __________\n\n");
	printf ("Ingrese una palabra: ");
	scanf ("%s", nom); push (tas, nom);
	printf ("La pila (%d elementos): \n",tas->size);
	printf("\n********** Cabeza de la PILA **********\n");
	show(tas);
	printf("__________ Bajo de la PILA __________\n\n");
	printf ("Ingrese una palabra: "); scanf ("%s", nom);
	push (tas, nom);
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