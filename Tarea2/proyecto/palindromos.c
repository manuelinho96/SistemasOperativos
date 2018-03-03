/* IMPLEMENTACION DE LAS FUNCIONES PALINDROMOS

Estudiantes:
- Ian Goldberg      # 14-10406
- Manuel Rodriguez  # 13-11223
- David Segura      # 13-11341
*/

#include "palindromos.h"

/************************** MIN **************************/
/*
TIPO: Funcion 
DESCRIPCION: Determina el menor valor entre un par de numeros
ENTRADA: a ----> Entero
		 b ----> Entero
SALIDA:  int (Entero menor) */

int min(int a, int b){
	if(a<b){
		return a;
	}
	else{
		return b;
	}
}

/************************** SUBSTR **************************/
/*
TIPO: Funcion 
DESCRIPCION: Retorna un substring de una palabra
ENTRADA: cadena ----> Palabra a la cual se le sacara un substring
		 comienzo ----> Entero que indica en donde comienza el substring
		 longitud ----> Entero que indica el tamaño del substring
SALIDA:  char (substring) */

char* substr(char* cadena, int comienzo, int longitud){
	char *nuevo;
	if ((nuevo = (char *)malloc(sizeof(char)*(int)longitud)) != NULL){
		if (longitud == 0) longitud = strlen(cadena)-comienzo-1;
		strncpy(nuevo, cadena + comienzo, longitud);
		return nuevo;
	}else{
		exit(-1);
	}
}

/************************** MINUS **************************/
/*
TIPO: Funcion 
DESCRIPCION: Transforma una letra mayuscula en minuscula
ENTRADA: letra ----> Letra a transformar
SALIDA:  char (Letra transformada) */

char minus(char letra){
	if (letra>=65 && letra<=90){
		char minletra = letra+32;
		return minletra;
	}
	else{
		return letra;
	}
}

/***************** PALINDROMOSIMPARES *****************/
/*
TIPO: Funcion 
DESCRIPCION: Encuentra los palindromos impares de un string
ENTRADA: palabra ----> String a evaluar
SALIDA:  int (Indica cuantos palindromos encontro) */

int palindromosimpares(char *palabra){
	int length = strlen(palabra);
	int longitudespal[length];
	int posicion, posizq, posder,actual;
	int contador = 0;

	memset(longitudespal,0, sizeof(longitudespal)); //Inicializamos en 0 el arreglo
	posizq = posder = -1;
	for(posicion = 0; posicion < length; posicion++){
  		actual = 0;
  		if(posicion <= posder)
    		actual = min(posder - posicion, longitudespal[posizq + posder - posicion]) + 1;
  		while(posicion - actual >= 0
        	  && posicion + actual < length
       	 	  && minus(palabra[posicion - actual]) == minus(palabra[posicion + actual]))
     		  actual++;
  		longitudespal[posicion] = --actual;
  		if(posicion + actual > posder){
     		posder = posicion + actual;
     		posizq = posicion - actual;
  		}
	}
	for (int j = 0;j<sizeof(longitudespal)/sizeof(int);j++){
		if(longitudespal[j]!=0){
			if (longitudespal[j]>1){
				for (int z = 1;z<=longitudespal[j];z++){
					char *substr1 = substr(palabra,(j-z),z*2 +1);
					printf("%s,\n",substr1);
				}
			}
			else{
				char *substr1 = substr(palabra,(j-longitudespal[j]),longitudespal[j]*2 +1);
				printf("%s,\n",substr1);
			}
			contador++;
		}
	}
	return contador;
}

/***************** PALINDROMOSPARES *****************/
/*
TIPO: Funcion 
DESCRIPCION: Encuentra los palindromos pares de un string
ENTRADA: palabra ----> String a evaluar
SALIDA:  int (Indica cuantos palindromos encontro) */

int palindromospares(char *palabra){
	int length = strlen(palabra);
	int longitudespal[length];
	int posicion, posizq, posder,actual;
	int contador = 0;

	memset(longitudespal,0, sizeof(longitudespal));
	posizq = posder = -1;
	for(posicion = 0;posicion<length; posicion++){
	  	actual = 0;
	  	if(posicion <= posder){
	    	actual = min(posder - posicion + 1,longitudespal[posizq+posder-(posicion+1)])+1;
	  	}
	  	while(posicion - actual >= 0
	          && posicion + actual - 1 < length
	          && minus(palabra[posicion - actual]) == minus(palabra[posicion + actual - 1]))
	    		actual++;  
	  	longitudespal[posicion] = --actual;
	  	if (posicion + actual -1 > posder){
	    	posizq = posicion - actual;
	    	posder = posicion + actual - 1;
	  	}
	}
	for (int j = 0;j<sizeof(longitudespal)/sizeof(int);j++){
		if(longitudespal[j]>1){
			if (longitudespal[j]>2){
				for (int z = 2;z<=longitudespal[j];z++){
					char *substr1 = substr(palabra,(j-z),z*2);
					printf("%s,\n",substr1);
				}
			}
			else{
				char *substr1 = substr(palabra,(j-longitudespal[j]),longitudespal[j]*2);
				printf("%s,\n",substr1);
			}
			contador++;
		}
	}
	return contador;
}