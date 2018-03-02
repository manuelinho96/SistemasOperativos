/* DECLARACION DE LAS FUNCIONES PALINDROMOS

Estudiantes:
- Ian Goldberg      # 14-10406
- Manuel Rodriguez  # 13-11223
- David Segura      # 13-11341
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Funcion que determina el menor valor entre un par de numeros
int min(int a, int b);

//Funcion que retorna un substring de una palabra
char* substr(char* cadena, int comienzo, int longitud);

//Funcion que transforma una letra mayuscula en minuscula
char minus(char letra);

//Funcion que encuentra los palindromos impares de un string
int palindromosimpares(char *palabra);

//Funcion que encuentra los palindromos pares de un string
int palindromospares(char *palabra);