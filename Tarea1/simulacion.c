struct Producto **LeerProductos(const char *Nombre){

    FILE *archivo;
    char caracteres[100];
    int i = 0;
    int x;

    Producto *Product;
    Producto **Productos;
    char *token;

 	archivo = fopen(Nombre,"r");
 	
 	if (archivo == NULL)
 		exit(1);
 	else{
        while (feof(archivo) == 0){
            fgets(caracteres,1000,archivo);
            i++;
        }
        cantidaddeproductos = i;
        if ((Productos = malloc(i*sizeof(Producto)))==NULL) return NULL;
        rewind(archivo);
        i = 0;
        while (feof(archivo) == 0)
 	    {
            fgets(caracteres,1000,archivo);
            if ((Product = malloc(sizeof(Producto)))==NULL) return NULL;
            Productos[i] = Product;
            token = strtok(caracteres,"\t");
            x = 0;
            while(token != NULL){
                if ( x == 0 ) strcpy(Product->Nombre, token);
                if ( x== 1 ) Product->Peso = atoi(token);
                if ( x== 2 ) Product->Complejidad = atoi(token);
                x++;
                token = strtok(NULL,"\t");
            }
            i++;
 	    }
        fclose(archivo);
    }
    return Productos;
}

void imprimirproductos(){
        for(int j = 0; j<cantidaddeproductos; j++){
            printf("Nombre: %s", Productos[j]->Nombre);
            printf(" Peso: %d", Productos[j]->Peso);
            printf(" Complejidad: %d\n", Productos[j]->Complejidad);
    }
}

int generarcarrito(ListaEnlazada *Carrito){
    int productoscarrito = rand() % maxproductscarrito;
    int producto;
    while(productoscarrito == 0){
        productoscarrito = rand() % maxproductscarrito;
    }
    for (int j = 0; j < productoscarrito; j++){
        producto = rand() % cantidaddeproductos;
        addelementlist(Carrito, Productos[producto]);
    }
    return productoscarrito;
}

void writelogfile(int cantidaddecarritos, int *numproductscarrito, int *tiempoclientes, int tiempototal, const char *infile){
    FILE *logfile;
    logfile = fopen("simulacion.log", "w");
    if (fopen == NULL){
        printf("Error al escribir el log\n");
        exit(1);
    }else{
        fprintf(logfile, "Nombre del archivo de entrada: %s\n", infile);
        fprintf(logfile, "Cantidad de carritos: %d\n", cantidaddecarritos);
        fprintf(logfile, "Numero de productos en cada carrito: ");
        for(int i = 0; i<cantidaddecarritos; i++){
            fprintf(logfile, "Carrito %d: %d\n", i+1, numproductscarrito[i]);
        }
        fprintf(logfile, "Capacidad de la banda transportadora: %d\n", maxbt);
        fprintf(logfile, "Velocidad de la cajera: %f\n", velocidadcajera);
        fprintf(logfile, "Velocidad del embolsador: %d\n", velocidadembolsador);
        fprintf(logfile, "Tiempo de facturacion: %d\n", tiempofacturacion);
        fprintf(logfile, "Capacidad del area de embolsado: %d\n", maxareaembolsado);
        fprintf(logfile, "Capacidad de una bolsa: %d\n", maxbolsa);
        fprintf(logfile, "Tiempo en procesar cada cliente: \n");
        for(int i = 0; i<cantidaddecarritos; i++){
            fprintf(logfile, "Cliente %d: %d\n", i+1, tiempoclientes[i]);
        }
        fprintf(logfile, "Tiempo total: %d", tiempototal);
        fclose(logfile);
    }
}