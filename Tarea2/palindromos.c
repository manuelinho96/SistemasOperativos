#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int min(int a, int b){
	if(a<b){
		return a;
	}
	else{
		return b;
	}
}

/*char devolverpalabra(int *longitud){
	int contador = 0;
	for (int i = 0;i<sizeof(longitud);i++){
		if (longitud[i]!=0)
			contador++;
	}
	char *palabras[contador];
	for (int j = 0;j<sizeof(longitud);j++){
		if(longitud[j]!=0){
			char *substr;
			strncpy(substr,palabra[j-longitud[j]],longitud[j]*2 + 1);
			printf("%s\n",substr);
		}
	}
}*/

char* substr(char* cadena, int comienzo, int longitud){
	if (longitud == 0) longitud = strlen(cadena)-comienzo-1;
	
	char *nuevo = (char*)malloc(sizeof(char) * longitud);
	
	strncpy(nuevo, cadena + comienzo, longitud);
	
	return nuevo;
}


int main(){
	char *palabra = "bannabanitalavalatina";

	printf("PALABRA: %s\n",palabra);

	// PALINDROMOS IMPARES
	int length = strlen(palabra);
	int longitudespal[length];
	int posicion, posizq, posder,actual;
	memset(longitudespal,0, sizeof(longitudespal)); //Inicializamos en 0 el arreglo
	posizq = posder = -1;
	for(posicion = 0; posicion < length; posicion++){
  		actual = 0;
  		if(posicion <= posder)
    		actual = min(posder - posicion, longitudespal[posizq + posder - posicion]) + 1;
  		while(posicion - actual >= 0
        	  && posicion + actual < length
       	 	  && palabra[posicion - actual] == palabra[posicion + actual])
     		  actual++;
  		longitudespal[posicion] = --actual;
  		if(posicion + actual > posder){
     		posder = posicion + actual;
     		posizq = posicion - actual;
  		}
	}
	printf("Palindromos Impares>\n");
	for (int j = 0;j<sizeof(longitudespal)/sizeof(int);j++){
		if(longitudespal[j]!=0){
			if (longitudespal[j]>1){
				for (int z = 1;z<=longitudespal[j];z++){
					char *substr1 = substr(palabra,(j-z),z*2 +1);
					printf("%s\n",substr1);
				}
			}
			else{
				char *substr1 = substr(palabra,(j-longitudespal[j]),longitudespal[j]*2 +1);
				printf("%s\n",substr1);
				//VERIFICAR SI LA PALABRA YA ESTÁ EN EL ARREGLO QUE AUN NO ESTA DECLARADA
			}
		}
	}

	// PALINDROMOS PARES

	/*int length = strlen(palabra);
	int longitudespal[length];
	int posicion, posizq, posder,actual;*/
	memset(longitudespal,0, sizeof(longitudespal));
	posizq = posder = -1;
	for(posicion = 0;posicion<length; posicion++){
	  	actual = 0;
	  	if(posicion <= posder){
	    	actual = min(posder - posicion + 1,longitudespal[posizq+posder-(posicion+1)])+1;
	  	}
	  	while(posicion - actual >= 0
	          && posicion + actual - 1 < length
	          && palabra[posicion - actual] == palabra[posicion + actual - 1])
	    		actual++;  
	  	longitudespal[posicion] = --actual;
	  	if (posicion + actual -1 > posder){
	    	posizq = posicion - actual;
	    	posder = posicion + actual - 1;
	  	}
	}
	printf("Palindromos Pares>\n");
	for (int j = 0;j<sizeof(longitudespal)/sizeof(int);j++){
		if(longitudespal[j]>1){
			if (longitudespal[j]>2){
				for (int z = 2;z<=longitudespal[j];z++){
					char *substr1 = substr(palabra,(j-z),z*2);
					printf("%s\n",substr1);
				}
			}
			else{
				char *substr1 = substr(palabra,(j-longitudespal[j]),longitudespal[j]*2);
				printf("%s\n",substr1);
				//VERIFICAR SI LA PALABRA YA ESTÁ EN EL ARREGLO QUE AUN NO ESTA DECLARADA
			}
		}
	}
}