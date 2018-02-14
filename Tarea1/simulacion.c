struct Producto **LeerProductos(){

    FILE *archivo;
    char caracteres[100];
    int i = 0;
    int x;

    Producto *Product;
    Producto **Productos;
    char *token;

 	archivo = fopen("entrada1.txt","r");
 	
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

void generarcarrito(ListaEnlazada *Carrito){
    int productoscarrito = rand() % maxproductscarrito;
    int producto;
    while(productoscarrito == 0){
        productoscarrito = rand() % maxproductscarrito;
    }
    for (int j = 0; j < productoscarrito; j++){
        producto = rand() % cantidaddeproductos;
        addelementlist(Carrito, Productos[producto]);
    }
}