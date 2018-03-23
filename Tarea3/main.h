// Funcion para cargar el indexador
void *cargartable(void *args);

// Funcion para navegar a traves de directorios de manera recursiva.
void navegar_directorio(char* routename, int heightvalue);

// Funcion de un hilo para navegar entre directorios de manera recursiva.
void *indizar(void *args);

// Dada una ruta y una clave se escribe la misma en un
// archivo con el formato de archivo indicado en el informe.
void insertarrutaarchivo(char *path, char *claves);
