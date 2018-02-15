/* IMPLEMENTACION DE FUNCIONES PARA LA CONFIGURACION

Estudiantes:
- Ian Goldberg      # 14-10406
- Manuel Rodriguez  # 13-11223
- David Segura      # 13-11341
*/

#include "configuracion.h"

/******************** IMPRIMIROPCIONES *********************/
/*
TIPO: Funcion 
DESCRIPCION: Imprime la configuracion actual de las opciones
*/

void imprimiropciones(){
    printf("La modalidad es: %s\n", modalidad);
    printf("La cantidad de carritos en la cola es: %d \n", carritoEnCola);
    printf("La cantidad maxima de productos que puede tener el carrito es: %d\n", maxproductscarrito);
    printf("La capacidad maxima de la banda transportadora es: %d cc\n", maxbt);
    printf("La velocidad de la cajera es: %f.2 ops\n", velocidadcajera);
    printf("La velocidad del embolsador es: %d spb\n", velocidadembolsador);
    printf("El tiempo de facturacion es: %d s\n", tiempofacturacion);
    printf("La capacidad maxima del area de embolsado es: %d cc\n", maxareaembolsado);
    printf("La capacidad maxima de una bolsa: %d cc\n", maxbolsa);
    printf("Introduzca enter para volver al menu anterior: ");
}

/******************** MENUOPCIONES *********************/
/*
TIPO: Funcion 
DESCRIPCION: Muestra el menu de opciones a configurar
*/

void menuopciones(){
    printf("1. Modalidad\n");
    printf("2. Cantidad de carritos en la cola\n");
    printf("3. Cantidad maxima de productos que puede tener un carrito\n");
    printf("4. Capacidad maxima de la banda transportadora\n");
    printf("5. Velocidad de la cajera\n");
    printf("6. Velocidad del embolsador\n");
    printf("7. Tiempo de facturacion\n");
    printf("8. Capacidad maxima del area de embolsador\n");
    printf("9. Capacidad maxima de una bolsa\n");
    printf("10. Mostrar configuracion actual\n");
    printf("11. Regresar al menu\n");
}

/******************** CONFIGURACION *********************/
/*
TIPO: Funcion 
DESCRIPCION: Configura las opciones con las que se iniciara la
             simulacion
*/

void configuracion(){
    int opcion;
    while (1){
        menuopciones();
        while(1){
            printf("Ingrese una opcion: ");
            scanf("%d", &opcion);
            if ( opcion == 1 ){
                printf("1. Interactiva\n");
                printf("2. Automatica\n");
                printf("Ingrese la modalidad: ");
                scanf("%d", &opcion);
                if ( opcion == 1){
                    modalidad = "Interactiva";
                }
                else if (opcion == 2){
                    modalidad = "Automatica";
                }
                else{
                    printf("Opcion erronea, vuelva a intentarlo\n");
                }
            }
            else if ( opcion == 2 ){
                printf("Ingrese la cantidad de carritos en la cola: \n");
                scanf("%d", &carritoEnCola);
                break;
            }
            else if ( opcion == 3){
               printf("Ingrese la cantidad máxima de productos que puede tener un carrito:");
               scanf("%d", &maxproductscarrito);
            }
            else if ( opcion == 4){
                printf("Ingrese la Capacidad máxima de la banda transportadora: \n");
                scanf("%d", &maxbt);
            }
            else if (opcion == 5){
                printf("Ingrese la velocidad de la cajera: \n");
                scanf("%f", &velocidadcajera);
            }
            else if ( opcion == 6 ){
                printf("Ingrese la velocidad del embolsador: \n");
                scanf("%d", &velocidadembolsador);
            }
            else if( opcion == 7 ){
                printf("Ingrese el tiempo de facturación: \n");
                scanf("%d", &tiempofacturacion);
            }
            else if(opcion == 8){
                printf("Ingrese la capacidad máxima del área de embolsador: \n");
                scanf("%d", &maxareaembolsado);                               
            }
            else if(opcion == 9){
                printf("Ingrese la capacidad máxima de una bolsa: \n");
                scanf("%d", &maxbolsa);
            }
            else if (opcion == 10){
                imprimiropciones();
                fflush(stdin);
                getchar();
            }
            else if (opcion == 11){
                return;
            }
            else{
                printf("Opcion invalida, vuelva a intentarlo\n");
            }
            break;
        }
    }
}
