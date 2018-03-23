// Estructura de las celdas de la tabla
// Las celdas contienen una ruta
// Y un apuntador al siguientes.
typedef struct celda
{
    char *ruta;
    struct celda *next;
} tcelda, *pcelda;

// Crear tabla vacia
void maketablenull(void);

// Funcion de hash. Propuesta por Brian Kernighan y Dennis Ritchie
unsigned int stringhash(char *string);

// Buscar si una ruta esta en la tabla
pcelda buscar(char *ruta, char *termbusq);

// Insertar ruta a la tabla
pcelda insertar(char *ruta, char*termbusq);

// Buscador de la tabla de Hash
// Dado un termino de busqueda lo busca en la tabla de hash
// Al entrar en la celda verifica que rutas cumplen con el termino
// de busqueda indicado. Se asume que el nombre de los archivos
// son con - para hacer el split.
void buscarruta(char *termbusq);