/*
 * Archivo: conjunto.h
 * Biblioteca para representar conjuntos de enteros con arreglos de capacidad
 * fija. Sólo las primeras cantidad posiciones pertenecen al conjunto y no
 * contienen elementos repetidos; las posiciones restantes no se consultan.
 *
 * Las cantidades y capacidades deben ser no negativas y corresponder con el
 * espacio disponible en los arreglos. Los apuntadores deben ser válidos. En las
 * operaciones entre conjuntos, resultado debe ser un arreglo distinto de las
 * entradas. Las funciones reciben conjuntos que cumplen estas condiciones.
 */

#ifndef CONJUNTO_H
#define CONJUNTO_H

/* Capacidad de cada conjunto del programa de ejemplo. */
#define CAPACIDAD_CONJUNTO 10
/* Capacidad suficiente para la unión de dos conjuntos del ejemplo. */
#define CAPACIDAD_RESULTADO (2 * CAPACIDAD_CONJUNTO)

/*
 * Busca un elemento en las posiciones utilizadas del conjunto.
 * conjunto: el arreglo que contiene los elementos.
 * cantidad: el número de posiciones utilizadas.
 * elemento: el elemento buscado.
 * Regresa el índice del elemento, o -1 si no pertenece al conjunto.
 */
int buscarElemento(const int conjunto[], int cantidad, int elemento);

/*
 * Agrega un elemento al final del conjunto si no existe y queda espacio.
 * Si lo agrega, incrementa la cantidad; en otro caso no modifica el conjunto
 * ni la cantidad.
 * conjunto: el arreglo que contiene los elementos.
 * capacidad: el número máximo de elementos que admite el arreglo.
 * cantidad: el apuntador al número de posiciones utilizadas.
 * elemento: el elemento que se quiere agregar.
 * Regresa 1 si agrega el elemento; 0 si ya existe o no queda espacio.
 */
int agregarElemento(int conjunto[], int capacidad, int *cantidad,
                    int elemento);

/*
 * Elimina un elemento del conjunto y recorre los posteriores una posición a
 * la izquierda. Si lo elimina, decrementa la cantidad; en otro caso no modifica
 * el conjunto ni la cantidad.
 * conjunto: el arreglo que contiene los elementos.
 * cantidad: el apuntador al número de posiciones utilizadas.
 * elemento: el elemento que se quiere eliminar.
 * Regresa 1 si elimina el elemento; 0 si no pertenece al conjunto.
 */
int eliminarElemento(int conjunto[], int *cantidad, int elemento);

/*
 * Sustituye un elemento por otro en la misma posición. Conserva la cantidad
 * y las demás posiciones del arreglo, sin introducir elementos repetidos.
 * conjunto: el arreglo que contiene los elementos.
 * cantidad: el número de posiciones utilizadas.
 * elemento: el elemento que se quiere sustituir.
 * reemplazo: el nuevo valor.
 * Regresa 1 si realiza la sustitución; 0 si elemento no existe o reemplazo
 * ya pertenece al conjunto. Sustituir un elemento por sí mismo regresa 0.
 * Cuando regresa 0, no modifica el arreglo.
 */
int reemplazarElemento(int conjunto[], int cantidad, int elemento,
                       int reemplazo);

/*
 * Deja el conjunto vacío, conservando el arreglo y su capacidad.
 * cantidad: el apuntador al número de posiciones utilizadas del conjunto.
 * No modifica el contenido del arreglo ni regresa un valor.
 */
void vaciarConjunto(int *cantidad);

/*
 * Copia los elementos a otro arreglo, conservando su orden y sin modificar
 * el origen. Sólo modifica las posiciones del destino que recibe la copia.
 * origen: el arreglo que contiene los elementos por copiar.
 * cantidad: el número de posiciones utilizadas del origen.
 * destino: el arreglo que recibe la copia; no debe compartir memoria con
 * el origen.
 * capacidadDestino: el número de posiciones disponibles en destino.
 * Regresa la cantidad copiada, o -1 si falta capacidad. Si falta capacidad,
 * no modifica el destino. Copiar un conjunto vacío regresa 0.
 */
int copiarConjunto(const int origen[], int cantidad,
                   int destino[], int capacidadDestino);

/*
 * Indica si A es subconjunto de B, sin modificar ninguna entrada.
 * conjuntoA: el conjunto cuya pertenencia se quiere comprobar.
 * cantidadA: el número de elementos de A.
 * conjuntoB: el conjunto que debe contener los elementos de A.
 * cantidadB: el número de elementos de B.
 * Regresa 1 si todos los elementos de A pertenecen a B; 0 en otro caso.
 * El orden no importa. Un conjunto es subconjunto de sí mismo y el conjunto
 * vacío es subconjunto de cualquier conjunto, incluido el vacío.
 */
int esSubconjunto(const int conjuntoA[], int cantidadA,
                 const int conjuntoB[], int cantidadB);

/*
 * Compara dos conjuntos sin modificar ninguna entrada.
 * conjuntoA: el primer conjunto.
 * cantidadA: el número de elementos de A.
 * conjuntoB: el segundo conjunto.
 * cantidadB: el número de elementos de B.
 * Regresa 1 si ambos contienen exactamente los mismos elementos, sin importar
 * su orden; 0 en otro caso. Dos conjuntos vacíos son iguales.
 */
int sonConjuntosIguales(const int conjuntoA[], int cantidadA,
                       const int conjuntoB[], int cantidadB);

/*
 * Calcula la unión sin modificar los conjuntos de entrada. Conserva el orden
 * de A y agrega después los elementos de B que aún no aparecen, en su orden.
 * conjuntoA: el primer conjunto.
 * cantidadA: el número de elementos de A.
 * conjuntoB: el segundo conjunto.
 * cantidadB: el número de elementos de B.
 * resultado: el arreglo donde se guardan los elementos sin repetidos.
 * capacidadResultado: el número de posiciones disponibles en resultado.
 * Regresa la cantidad de elementos del resultado, o -1 si falta capacidad.
 * Cuando falta capacidad, el contenido del resultado no está definido,
 * pero no se debe escribir fuera de las posiciones disponibles.
 */
int unirConjuntos(const int conjuntoA[], int cantidadA,
                 const int conjuntoB[], int cantidadB,
                 int resultado[], int capacidadResultado);

/*
 * Calcula la intersección sin modificar los conjuntos de entrada. Guarda los
 * elementos de A que también pertenecen a B, conservando el orden de A.
 * conjuntoA: el primer conjunto.
 * cantidadA: el número de elementos de A.
 * conjuntoB: el segundo conjunto.
 * cantidadB: el número de elementos de B.
 * resultado: el arreglo donde se guardan los elementos sin repetidos.
 * capacidadResultado: el número de posiciones disponibles en resultado.
 * Regresa la cantidad de elementos del resultado, o -1 si falta capacidad.
 * Cuando falta capacidad, el contenido del resultado no está definido,
 * pero no se debe escribir fuera de las posiciones disponibles.
 */
int intersectarConjuntos(const int conjuntoA[], int cantidadA,
                        const int conjuntoB[], int cantidadB,
                        int resultado[], int capacidadResultado);

/*
 * Calcula la diferencia A-B sin modificar los conjuntos de entrada. Guarda los
 * elementos de A que no pertenecen a B, conservando el orden de A.
 * conjuntoA: el primer conjunto.
 * cantidadA: el número de elementos de A.
 * conjuntoB: el segundo conjunto.
 * cantidadB: el número de elementos de B.
 * resultado: el arreglo donde se guardan los elementos sin repetidos.
 * capacidadResultado: el número de posiciones disponibles en resultado.
 * Regresa la cantidad de elementos del resultado, o -1 si falta capacidad.
 * Cuando falta capacidad, el contenido del resultado no está definido,
 * pero no se debe escribir fuera de las posiciones disponibles.
 */
int diferenciarConjuntos(const int conjuntoA[], int cantidadA,
                        const int conjuntoB[], int cantidadB,
                        int resultado[], int capacidadResultado);

/*
 * Muestra las posiciones utilizadas con el formato {a, b, c}, seguido de un
 * salto de línea. Un conjunto vacío se muestra como {}.
 * conjunto: el arreglo que contiene los elementos.
 * cantidad: el número de posiciones utilizadas.
 */
void mostrarConjunto(const int conjunto[], int cantidad);

#endif
