/*
 * Archivo: test_conjunto.c
 * Pruebas unitarias de la biblioteca de conjuntos, sin dependencias externas.
 * Cada caso informa su resultado; el programa falla si alguna prueba falla.
 * Este archivo forma parte de la infraestructura y no debe modificarse para
 * resolver la práctica.
 */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "conjunto.h"

/* Número de pruebas ejecutadas. */
static int pruebas;
/* Número de pruebas que fallaron. */
static int fallas;
/* Valor que permite detectar escrituras fuera de la capacidad disponible. */
static const int CENTINELA = 123456789;

/* Comprueba una condición y termina sólo el caso actual si falla.
 * A diferencia de assert, estas comprobaciones permanecen activas con NDEBUG.
 */
#define COMPROBAR(condicion) do { \
    if (!(condicion)) { \
        printf("    %s:%d: falló %s\n", __FILE__, __LINE__, #condicion); \
        return 0; \
    } \
} while (0)

/*
 * Compara dos enteros y muestra sus valores si son distintos.
 * obtenido: el valor que produjo la función.
 * esperado: el valor que establece el caso de prueba.
 * Regresa 1 si coinciden; 0 en otro caso.
 */
static int enterosIguales(int obtenido, int esperado) {
    if (obtenido == esperado)
        return 1;
    printf("    Esperado: %d; obtenido: %d.\n", esperado, obtenido);
    return 0;
}

/*
 * Compara las posiciones utilizadas de dos arreglos en el mismo orden.
 * obtenido: el arreglo que produjo la función.
 * esperado: el arreglo que establece el caso de prueba.
 * cantidad: el número de posiciones que se comparan.
 * Regresa 1 si coinciden; 0 en otro caso.
 */
static int arreglosIguales(const int obtenido[], const int esperado[],
                          int cantidad) {
    for (int indice = 0; indice < cantidad; indice++) {
        if (obtenido[indice] != esperado[indice]) {
            printf("    Posición %d: esperado %d; obtenido %d.\n",
                   indice, esperado[indice], obtenido[indice]);
            return 0;
        }
    }
    return 1;
}

/*
 * Registra e imprime el resultado de un caso de prueba.
 * nombre: la descripción del caso.
 * pasa: 1 si la prueba pasó; 0 si falló.
 */
static void registrarResultado(const char nombre[], int pasa) {
    pruebas++;
    if (!pasa)
        fallas++;
    printf("[%s] %s\n", pasa ? "PASA" : "FALLA", nombre);
}

/* Prueba la búsqueda al inicio, en medio y al final. */
static int testBuscarElemento(void) {
    int conjunto[] = {44, 17, 31, 23};
    COMPROBAR(enterosIguales(buscarElemento(conjunto, 4, 44), 0));
    COMPROBAR(enterosIguales(buscarElemento(conjunto, 4, 31), 2));
    COMPROBAR(enterosIguales(buscarElemento(conjunto, 4, 23), 3));
    COMPROBAR(enterosIguales(buscarElemento(conjunto, 4, 99), -1));
    return 1;
}

/* Prueba que la búsqueda no consulta posiciones fuera de cantidad. */
static int testBuscarPosicionesUtilizadas(void) {
    int conjunto[] = {17, 23, 99};
    COMPROBAR(enterosIguales(buscarElemento(conjunto, 2, 99), -1));
    return 1;
}

/* Prueba la búsqueda en un conjunto vacío. */
static int testBuscarVacio(void) {
    int conjunto[] = {17};
    COMPROBAR(enterosIguales(buscarElemento(conjunto, 0, 17), -1));
    return 1;
}

/* Prueba la búsqueda de cero, negativos y los extremos de int. */
static int testBuscarEnteros(void) {
    int conjunto[] = {INT_MIN, 0, INT_MAX, -1};
    for (int indice = 0; indice < 4; indice++)
        COMPROBAR(enterosIguales(buscarElemento(conjunto, 4,
                                              conjunto[indice]), indice));
    return 1;
}

/* Prueba agregar el primer elemento, aunque ya esté en una posición libre. */
static int testAgregarVacio(void) {
    int conjunto[] = {17, CENTINELA};
    int cantidad = 0;
    COMPROBAR(enterosIguales(agregarElemento(conjunto, 1, &cantidad, 17), 1));
    COMPROBAR(enterosIguales(cantidad, 1));
    COMPROBAR(enterosIguales(conjunto[0], 17));
    COMPROBAR(enterosIguales(conjunto[1], CENTINELA));
    return 1;
}

/* Prueba agregar al final sin alterar el orden de los elementos anteriores. */
static int testAgregarElemento(void) {
    int conjunto[] = {44, 17, 0, CENTINELA};
    int esperado[] = {44, 17, 23, CENTINELA};
    int cantidad = 2;
    COMPROBAR(enterosIguales(agregarElemento(conjunto, 3, &cantidad, 23), 1));
    COMPROBAR(enterosIguales(cantidad, 3));
    COMPROBAR(arreglosIguales(conjunto, esperado, 4));
    return 1;
}

/* Prueba que agregar un repetido no cambia ni el arreglo ni la cantidad. */
static int testAgregarRepetido(void) {
    int conjunto[] = {17, 23, 31, CENTINELA};
    int esperado[] = {17, 23, 31, CENTINELA};
    int cantidad = 3;
    for (int indice = 0; indice < 3; indice++) {
        COMPROBAR(enterosIguales(agregarElemento(conjunto, 4, &cantidad,
                                               esperado[indice]), 0));
        COMPROBAR(enterosIguales(cantidad, 3));
        COMPROBAR(arreglosIguales(conjunto, esperado, 4));
    }
    return 1;
}

/* Prueba agregar a un conjunto lleno, con elementos nuevos y repetidos. */
static int testAgregarLleno(void) {
    int conjunto[] = {17, 23, CENTINELA};
    int esperado[] = {17, 23, CENTINELA};
    int cantidad = 2;
    COMPROBAR(enterosIguales(agregarElemento(conjunto, 2, &cantidad, 31), 0));
    COMPROBAR(enterosIguales(agregarElemento(conjunto, 2, &cantidad, 17), 0));
    COMPROBAR(enterosIguales(cantidad, 2));
    COMPROBAR(arreglosIguales(conjunto, esperado, 3));
    return 1;
}

/* Prueba que una capacidad de cero no permite escribir ningún elemento. */
static int testAgregarSinCapacidad(void) {
    int conjunto[] = {CENTINELA};
    int cantidad = 0;
    COMPROBAR(enterosIguales(agregarElemento(conjunto, 0, &cantidad, 17), 0));
    COMPROBAR(enterosIguales(cantidad, 0));
    COMPROBAR(enterosIguales(conjunto[0], CENTINELA));
    return 1;
}

/* Prueba agregar cero, negativos y los extremos de int sin duplicarlos. */
static int testAgregarEnteros(void) {
    int conjunto[5] = {0, 0, 0, 0, CENTINELA};
    int esperado[] = {INT_MIN, 0, INT_MAX, -1};
    int cantidad = 0;
    for (int indice = 0; indice < 4; indice++) {
        COMPROBAR(enterosIguales(agregarElemento(conjunto, 4, &cantidad,
                                               esperado[indice]), 1));
        COMPROBAR(enterosIguales(cantidad, indice + 1));
        COMPROBAR(arreglosIguales(conjunto, esperado, cantidad));
        COMPROBAR(enterosIguales(agregarElemento(conjunto, 4, &cantidad,
                                               esperado[indice]), 0));
        COMPROBAR(enterosIguales(cantidad, indice + 1));
    }
    COMPROBAR(enterosIguales(conjunto[4], CENTINELA));
    return 1;
}

/* Prueba eliminar el primer elemento y desplazar todos los posteriores. */
static int testEliminarPrimero(void) {
    int conjunto[] = {44, 17, 31, 23};
    int esperado[] = {17, 31, 23};
    int cantidad = 4;
    COMPROBAR(enterosIguales(eliminarElemento(conjunto, &cantidad, 44), 1));
    COMPROBAR(enterosIguales(cantidad, 3));
    COMPROBAR(arreglosIguales(conjunto, esperado, 3));
    return 1;
}

/* Prueba eliminar un elemento intermedio conservando el orden restante. */
static int testEliminarIntermedio(void) {
    int conjunto[] = {44, 17, 31, 23};
    int esperado[] = {44, 31, 23};
    int cantidad = 4;
    COMPROBAR(enterosIguales(eliminarElemento(conjunto, &cantidad, 17), 1));
    COMPROBAR(enterosIguales(cantidad, 3));
    COMPROBAR(arreglosIguales(conjunto, esperado, 3));
    return 1;
}

/* Prueba eliminar el último elemento sin cambiar los anteriores. */
static int testEliminarUltimo(void) {
    int conjunto[] = {44, 17, 31, 23};
    int esperado[] = {44, 17, 31};
    int cantidad = 4;
    COMPROBAR(enterosIguales(eliminarElemento(conjunto, &cantidad, 23), 1));
    COMPROBAR(enterosIguales(cantidad, 3));
    COMPROBAR(arreglosIguales(conjunto, esperado, 3));
    return 1;
}

/* Prueba eliminar el único elemento y obtener un conjunto vacío. */
static int testEliminarUnico(void) {
    int conjunto[] = {0};
    int cantidad = 1;
    COMPROBAR(enterosIguales(eliminarElemento(conjunto, &cantidad, 0), 1));
    COMPROBAR(enterosIguales(cantidad, 0));
    return 1;
}

/* Prueba eliminar un elemento inexistente sin cambiar el estado. */
static int testEliminarInexistente(void) {
    int conjunto[] = {17, 23, 99};
    int esperado[] = {17, 23, 99};
    int cantidad = 2;
    COMPROBAR(enterosIguales(eliminarElemento(conjunto, &cantidad, 99), 0));
    COMPROBAR(enterosIguales(cantidad, 2));
    COMPROBAR(arreglosIguales(conjunto, esperado, 3));
    return 1;
}

/* Prueba eliminar de un conjunto vacío sin consultar posiciones libres. */
static int testEliminarVacio(void) {
    int conjunto[] = {17};
    int cantidad = 0;
    COMPROBAR(enterosIguales(eliminarElemento(conjunto, &cantidad, 17), 0));
    COMPROBAR(enterosIguales(cantidad, 0));
    COMPROBAR(enterosIguales(conjunto[0], 17));
    return 1;
}

/* Prueba eliminar números negativos y extremos de int. */
static int testEliminarEnteros(void) {
    int conjunto[] = {INT_MIN, 0, INT_MAX, -1};
    int esperado[] = {0, -1};
    int cantidad = 4;
    COMPROBAR(enterosIguales(eliminarElemento(conjunto, &cantidad, INT_MIN), 1));
    COMPROBAR(enterosIguales(eliminarElemento(conjunto, &cantidad, INT_MAX), 1));
    COMPROBAR(enterosIguales(cantidad, 2));
    COMPROBAR(arreglosIguales(conjunto, esperado, 2));
    COMPROBAR(enterosIguales(eliminarElemento(conjunto, &cantidad, -1), 1));
    COMPROBAR(enterosIguales(cantidad, 1));
    COMPROBAR(enterosIguales(conjunto[0], 0));
    return 1;
}

/* Prueba llenar un conjunto y reutilizar el espacio de una eliminación. */
static int testReutilizarEspacio(void) {
    int conjunto[CAPACIDAD_CONJUNTO + 1] = {0};
    int cantidad = 0;
    conjunto[CAPACIDAD_CONJUNTO] = CENTINELA;
    for (int indice = 0; indice < CAPACIDAD_CONJUNTO; indice++) {
        COMPROBAR(enterosIguales(agregarElemento(conjunto, CAPACIDAD_CONJUNTO,
                                               &cantidad, indice), 1));
        COMPROBAR(enterosIguales(cantidad, indice + 1));
    }
    COMPROBAR(enterosIguales(agregarElemento(conjunto, CAPACIDAD_CONJUNTO,
                                           &cantidad, 99), 0));
    COMPROBAR(enterosIguales(eliminarElemento(conjunto, &cantidad, 0), 1));
    COMPROBAR(enterosIguales(cantidad, CAPACIDAD_CONJUNTO - 1));
    COMPROBAR(enterosIguales(agregarElemento(conjunto, CAPACIDAD_CONJUNTO,
                                           &cantidad, 0), 1));
    COMPROBAR(enterosIguales(cantidad, CAPACIDAD_CONJUNTO));
    for (int indice = 0; indice < cantidad - 1; indice++)
        COMPROBAR(enterosIguales(conjunto[indice], indice + 1));
    COMPROBAR(enterosIguales(conjunto[cantidad - 1], 0));
    COMPROBAR(enterosIguales(conjunto[CAPACIDAD_CONJUNTO], CENTINELA));
    return 1;
}

/* Prueba reemplazar al inicio, en medio y al final sin mover los demás. */
static int testReemplazarPosiciones(void) {
    int conjunto[] = {44, 17, 31, 23, CENTINELA};
    int primero[] = {99, 17, 31, 23, CENTINELA};
    int intermedio[] = {99, 17, 58, 23, CENTINELA};
    int ultimo[] = {99, 17, 58, 0, CENTINELA};
    COMPROBAR(enterosIguales(reemplazarElemento(conjunto, 4, 44, 99), 1));
    COMPROBAR(arreglosIguales(conjunto, primero, 5));
    COMPROBAR(enterosIguales(reemplazarElemento(conjunto, 4, 31, 58), 1));
    COMPROBAR(arreglosIguales(conjunto, intermedio, 5));
    COMPROBAR(enterosIguales(reemplazarElemento(conjunto, 4, 23, 0), 1));
    COMPROBAR(arreglosIguales(conjunto, ultimo, 5));
    return 1;
}

/* Prueba que reemplazar por otro elemento del conjunto no crea repetidos. */
static int testReemplazarRepetido(void) {
    int conjunto[] = {17, 23, 31, CENTINELA};
    int esperado[] = {17, 23, 31, CENTINELA};
    COMPROBAR(enterosIguales(reemplazarElemento(conjunto, 3, 17, 31), 0));
    COMPROBAR(arreglosIguales(conjunto, esperado, 4));
    return 1;
}

/* Prueba que reemplazar por el mismo valor no cuenta como modificación. */
static int testReemplazarMismo(void) {
    int conjunto[] = {17, 23, CENTINELA};
    int esperado[] = {17, 23, CENTINELA};
    COMPROBAR(enterosIguales(reemplazarElemento(conjunto, 2, 23, 23), 0));
    COMPROBAR(enterosIguales(reemplazarElemento(conjunto, 2, 99, 99), 0));
    COMPROBAR(arreglosIguales(conjunto, esperado, 3));
    return 1;
}

/* Prueba que el valor por reemplazar debe estar en las posiciones utilizadas. */
static int testReemplazarInexistente(void) {
    int conjunto[] = {17, 23, 99};
    int esperado[] = {17, 23, 99};
    COMPROBAR(enterosIguales(reemplazarElemento(conjunto, 2, 99, 44), 0));
    COMPROBAR(arreglosIguales(conjunto, esperado, 3));
    return 1;
}

/* Prueba reemplazar en un conjunto vacío sin modificar el arreglo. */
static int testReemplazarVacio(void) {
    int conjunto[] = {17, CENTINELA};
    int esperado[] = {17, CENTINELA};
    COMPROBAR(enterosIguales(reemplazarElemento(conjunto, 0, 17, 23), 0));
    COMPROBAR(arreglosIguales(conjunto, esperado, 2));
    return 1;
}

/* Prueba que un valor en una posición libre puede usarse como reemplazo. */
static int testReemplazarPosicionesUtilizadas(void) {
    int conjunto[] = {17, 23, 99};
    int esperado[] = {99, 23, 99};
    COMPROBAR(enterosIguales(reemplazarElemento(conjunto, 2, 17, 99), 1));
    COMPROBAR(arreglosIguales(conjunto, esperado, 3));
    return 1;
}

/* Prueba reemplazar el único elemento sin necesitar espacio adicional. */
static int testReemplazarUnico(void) {
    int conjunto[] = {17, CENTINELA};
    int esperado[] = {23, CENTINELA};
    COMPROBAR(enterosIguales(reemplazarElemento(conjunto, 1, 17, 23), 1));
    COMPROBAR(arreglosIguales(conjunto, esperado, 2));
    return 1;
}

/* Prueba reemplazar cero, negativos y los extremos de int. */
static int testReemplazarEnteros(void) {
    int conjunto[] = {INT_MIN, 0, -1, CENTINELA};
    int esperado[] = {INT_MAX, INT_MIN, 0, CENTINELA};
    COMPROBAR(enterosIguales(reemplazarElemento(conjunto, 3, INT_MIN,
                                              INT_MAX), 1));
    COMPROBAR(enterosIguales(reemplazarElemento(conjunto, 3, 0, INT_MIN), 1));
    COMPROBAR(enterosIguales(reemplazarElemento(conjunto, 3, -1, 0), 1));
    COMPROBAR(arreglosIguales(conjunto, esperado, 4));
    return 1;
}

/* Prueba vaciar un conjunto sin modificar su arreglo. */
static int testVaciarConjunto(void) {
    int conjunto[] = {44, 17, 31, CENTINELA};
    int esperado[] = {44, 17, 31, CENTINELA};
    int cantidad = 3;
    vaciarConjunto(&cantidad);
    COMPROBAR(enterosIguales(cantidad, 0));
    COMPROBAR(arreglosIguales(conjunto, esperado, 4));
    COMPROBAR(enterosIguales(buscarElemento(conjunto, cantidad, 17), -1));
    return 1;
}

/* Prueba vaciar varias veces un conjunto que ya está vacío. */
static int testVaciarVacio(void) {
    int cantidad = 0;
    vaciarConjunto(&cantidad);
    COMPROBAR(enterosIguales(cantidad, 0));
    vaciarConjunto(&cantidad);
    COMPROBAR(enterosIguales(cantidad, 0));
    return 1;
}

/* Prueba reutilizar toda la capacidad después de vaciar un conjunto lleno. */
static int testVaciarYReutilizar(void) {
    int conjunto[CAPACIDAD_CONJUNTO + 1];
    int cantidad = CAPACIDAD_CONJUNTO;
    for (int indice = 0; indice < CAPACIDAD_CONJUNTO; indice++)
        conjunto[indice] = indice;
    conjunto[CAPACIDAD_CONJUNTO] = CENTINELA;
    vaciarConjunto(&cantidad);
    COMPROBAR(enterosIguales(cantidad, 0));
    for (int indice = 0; indice < CAPACIDAD_CONJUNTO; indice++) {
        COMPROBAR(enterosIguales(agregarElemento(conjunto, CAPACIDAD_CONJUNTO,
                                               &cantidad, indice), 1));
        COMPROBAR(enterosIguales(cantidad, indice + 1));
        COMPROBAR(enterosIguales(conjunto[indice], indice));
    }
    COMPROBAR(enterosIguales(conjunto[CAPACIDAD_CONJUNTO], CENTINELA));
    return 1;
}

/*
 * Comprueba la copia, la conservación del origen y los límites del destino.
 * origen: los elementos que se deben copiar.
 * cantidad: el número de elementos del origen.
 * capacidad: las posiciones disponibles del destino.
 * cantidadEsperada: la cantidad copiada esperada, o -1 si falta capacidad.
 * Regresa 1 si todas las comprobaciones pasan; 0 en otro caso.
 */
static int verificarCopia(const int origen[], int cantidad,
                          int capacidad, int cantidadEsperada) {
    int entrada[CAPACIDAD_CONJUNTO];
    int destino[CAPACIDAD_RESULTADO + 2];
    int obtenida;
    for (int indice = 0; indice < CAPACIDAD_CONJUNTO; indice++)
        entrada[indice] = indice < cantidad ? origen[indice] : CENTINELA;
    for (int indice = 0; indice < CAPACIDAD_RESULTADO + 2; indice++)
        destino[indice] = CENTINELA;

    obtenida = copiarConjunto(entrada, cantidad, destino + 1, capacidad);

    COMPROBAR(enterosIguales(obtenida, cantidadEsperada));
    COMPROBAR(enterosIguales(destino[0], CENTINELA));
    for (int indice = 0; indice < CAPACIDAD_RESULTADO + 1; indice++) {
        int esperado = cantidadEsperada >= 0 && indice < cantidad
                       ? origen[indice] : CENTINELA;
        COMPROBAR(enterosIguales(destino[indice + 1], esperado));
    }
    for (int indice = 0; indice < CAPACIDAD_CONJUNTO; indice++)
        COMPROBAR(enterosIguales(entrada[indice],
                                indice < cantidad ? origen[indice]
                                                  : CENTINELA));
    return 1;
}

/* Pruebas unitarias para copiarConjunto. */
static void testCopiarConjunto(void) {
    int conjunto[] = {44, 17, 31, 23};
    int vacio[] = {17};
    int extremos[] = {INT_MAX, -1, 0, INT_MIN};
    int lleno[CAPACIDAD_CONJUNTO];
    registrarResultado("copia: conserva el orden y las posiciones libres",
                       verificarCopia(conjunto, 4, CAPACIDAD_RESULTADO, 4));
    registrarResultado("copia: capacidad exacta",
                       verificarCopia(conjunto, 4, 4, 4));
    registrarResultado("copia: capacidad insuficiente, destino intacto",
                       verificarCopia(conjunto, 4, 3, -1));
    registrarResultado("copia: sin capacidad, destino intacto",
                       verificarCopia(conjunto, 4, 0, -1));
    registrarResultado("copia: conjunto vacío sin capacidad",
                       verificarCopia(vacio, 0, 0, 0));
    registrarResultado("copia: conjunto vacío con capacidad",
                       verificarCopia(vacio, 0, CAPACIDAD_RESULTADO, 0));
    registrarResultado("copia: cero, negativos y extremos",
                       verificarCopia(extremos, 4, 4, 4));
    for (int indice = 0; indice < CAPACIDAD_CONJUNTO; indice++)
        lleno[indice] = CAPACIDAD_CONJUNTO - indice;
    registrarResultado("copia: conjunto lleno",
                       verificarCopia(lleno, CAPACIDAD_CONJUNTO,
                                      CAPACIDAD_CONJUNTO, CAPACIDAD_CONJUNTO));
}

/*
 * Comprueba la relación de subconjunto y que las entradas no cambien.
 * conjuntoA: los elementos del primer conjunto.
 * cantidadA: el número de elementos del primer conjunto.
 * conjuntoB: los elementos del segundo conjunto.
 * cantidadB: el número de elementos del segundo conjunto.
 * esperado: el resultado esperado de la relación de subconjunto.
 * Regresa 1 si todas las comprobaciones pasan; 0 en otro caso.
 */
static int verificarSubconjunto(const int conjuntoA[], int cantidadA,
                                const int conjuntoB[], int cantidadB,
                                int esperado) {
    int copiaA[CAPACIDAD_CONJUNTO];
    int copiaB[CAPACIDAD_CONJUNTO];
    for (int indice = 0; indice < CAPACIDAD_CONJUNTO; indice++) {
        copiaA[indice] = indice < cantidadA ? conjuntoA[indice] : CENTINELA;
        copiaB[indice] = indice < cantidadB ? conjuntoB[indice] : CENTINELA;
    }
    COMPROBAR(enterosIguales(esSubconjunto(copiaA, cantidadA,
                                         copiaB, cantidadB), esperado));
    for (int indice = 0; indice < CAPACIDAD_CONJUNTO; indice++) {
        COMPROBAR(enterosIguales(copiaA[indice],
                                indice < cantidadA ? conjuntoA[indice]
                                                   : CENTINELA));
        COMPROBAR(enterosIguales(copiaB[indice],
                                indice < cantidadB ? conjuntoB[indice]
                                                   : CENTINELA));
    }
    return 1;
}

/* Pruebas unitarias para esSubconjunto. */
static void testEsSubconjunto(void) {
    int a[] = {44, 17};
    int b[] = {17, 23, 31, 44};
    int iguales[] = {17, 44};
    int distinto[] = {44, 99};
    int disjunto[] = {58, 99};
    int vacio[] = {0};
    int extremos[] = {INT_MAX, 0, INT_MIN};
    int enteros[] = {INT_MIN, -1, 0, INT_MAX};
    int libre[] = {CENTINELA};
    registrarResultado("subconjunto: contenido con distinto orden",
                       verificarSubconjunto(a, 2, b, 4, 1));
    registrarResultado("subconjunto: conjuntos iguales en distinto orden",
                       verificarSubconjunto(a, 2, iguales, 2, 1));
    registrarResultado("subconjunto: mismo conjunto",
                       verificarSubconjunto(a, 2, a, 2, 1));
    registrarResultado("subconjunto: la relación no es simétrica",
                       verificarSubconjunto(b, 4, a, 2, 0));
    registrarResultado("subconjunto: falta un elemento, misma cantidad",
                       verificarSubconjunto(distinto, 2, a, 2, 0));
    registrarResultado("subconjunto: conjuntos disjuntos",
                       verificarSubconjunto(disjunto, 2, b, 4, 0));
    registrarResultado("subconjunto: A vacío",
                       verificarSubconjunto(vacio, 0, b, 4, 1));
    registrarResultado("subconjunto: B vacío",
                       verificarSubconjunto(a, 2, vacio, 0, 0));
    registrarResultado("subconjunto: ambos vacíos",
                       verificarSubconjunto(vacio, 0, vacio, 0, 1));
    registrarResultado("subconjunto: cero, negativos y extremos",
                       verificarSubconjunto(extremos, 3, enteros, 4, 1));
    registrarResultado("subconjunto: ignora las posiciones libres de B",
                       verificarSubconjunto(libre, 1, b, 4, 0));
}

/*
 * Comprueba la igualdad de conjuntos y que las entradas no cambien.
 * conjuntoA: los elementos del primer conjunto.
 * cantidadA: el número de elementos del primer conjunto.
 * conjuntoB: los elementos del segundo conjunto.
 * cantidadB: el número de elementos del segundo conjunto.
 * esperado: el resultado esperado de la comparación.
 * Regresa 1 si todas las comprobaciones pasan; 0 en otro caso.
 */
static int verificarIgualdad(const int conjuntoA[], int cantidadA,
                             const int conjuntoB[], int cantidadB,
                             int esperado) {
    /* Las posiciones libres difieren para comprobar que no se comparan. */
    int copiaA[CAPACIDAD_CONJUNTO];
    int copiaB[CAPACIDAD_CONJUNTO];
    for (int indice = 0; indice < CAPACIDAD_CONJUNTO; indice++) {
        copiaA[indice] = indice < cantidadA ? conjuntoA[indice] : CENTINELA;
        copiaB[indice] = indice < cantidadB ? conjuntoB[indice] : -CENTINELA;
    }
    COMPROBAR(enterosIguales(sonConjuntosIguales(copiaA, cantidadA,
                                               copiaB, cantidadB), esperado));
    for (int indice = 0; indice < CAPACIDAD_CONJUNTO; indice++) {
        COMPROBAR(enterosIguales(copiaA[indice],
                                indice < cantidadA ? conjuntoA[indice]
                                                   : CENTINELA));
        COMPROBAR(enterosIguales(copiaB[indice],
                                indice < cantidadB ? conjuntoB[indice]
                                                   : -CENTINELA));
    }
    return 1;
}

/* Prueba comparar un arreglo consigo mismo, sin modificarlo. */
static int testIgualdadMismoArreglo(void) {
    int conjunto[] = {44, 17, 23, CENTINELA};
    int esperado[] = {44, 17, 23, CENTINELA};
    COMPROBAR(enterosIguales(sonConjuntosIguales(conjunto, 3, conjunto, 3), 1));
    COMPROBAR(arreglosIguales(conjunto, esperado, 4));
    return 1;
}

/* Pruebas unitarias para sonConjuntosIguales. */
static void testSonConjuntosIguales(void) {
    int a[] = {44, 17, 31, 23};
    int otroOrden[] = {23, 31, 44, 17};
    int distinto[] = {44, 17, 31, 99};
    int disjunto[] = {58, 99, -1, 0};
    int subconjunto[] = {17, 44};
    int vacio[] = {0};
    int unico[] = {17};
    int extremos[] = {INT_MAX, -1, 0, INT_MIN};
    int mismosExtremos[] = {INT_MIN, 0, INT_MAX, -1};
    int llenoA[CAPACIDAD_CONJUNTO];
    int llenoB[CAPACIDAD_CONJUNTO];
    registrarResultado("igualdad: mismos elementos y orden",
                       verificarIgualdad(a, 4, a, 4, 1));
    registrarResultado("igualdad: mismos elementos en distinto orden",
                       verificarIgualdad(a, 4, otroOrden, 4, 1));
    registrarResultado("igualdad: mismo arreglo", testIgualdadMismoArreglo());
    registrarResultado("igualdad: misma cantidad, elementos distintos",
                       verificarIgualdad(a, 4, distinto, 4, 0));
    registrarResultado("igualdad: conjuntos disjuntos",
                       verificarIgualdad(a, 4, disjunto, 4, 0));
    registrarResultado("igualdad: A es subconjunto propio de B",
                       verificarIgualdad(subconjunto, 2, a, 4, 0));
    registrarResultado("igualdad: B es subconjunto propio de A",
                       verificarIgualdad(a, 4, subconjunto, 2, 0));
    registrarResultado("igualdad: ambos vacíos",
                       verificarIgualdad(vacio, 0, vacio, 0, 1));
    registrarResultado("igualdad: sólo A vacío",
                       verificarIgualdad(vacio, 0, a, 4, 0));
    registrarResultado("igualdad: sólo B vacío",
                       verificarIgualdad(a, 4, vacio, 0, 0));
    registrarResultado("igualdad: un elemento y posiciones libres distintas",
                       verificarIgualdad(unico, 1, unico, 1, 1));
    registrarResultado("igualdad: cero, negativos y extremos",
                       verificarIgualdad(extremos, 4, mismosExtremos, 4, 1));
    for (int indice = 0; indice < CAPACIDAD_CONJUNTO; indice++) {
        llenoA[indice] = indice;
        llenoB[indice] = CAPACIDAD_CONJUNTO - indice - 1;
    }
    registrarResultado("igualdad: conjuntos llenos en distinto orden",
                       verificarIgualdad(llenoA, CAPACIDAD_CONJUNTO,
                                         llenoB, CAPACIDAD_CONJUNTO, 1));
}

/*
 * Comprueba una operación entre conjuntos, sus entradas y su capacidad.
 * operacion: la función de unión, intersección o diferencia por probar.
 * conjuntoA: los elementos de la primera entrada.
 * cantidadA: el número de elementos de la primera entrada.
 * conjuntoB: los elementos de la segunda entrada.
 * cantidadB: el número de elementos de la segunda entrada.
 * esperado: los elementos esperados cuando la operación tiene éxito.
 * cantidadEsperada: la cantidad esperada, o -1 si falta capacidad.
 * capacidad: el espacio que puede utilizar la operación.
 * Regresa 1 si todas las comprobaciones pasan; 0 en otro caso.
 */
static int verificarOperacion(int (*operacion)(const int[], int,
                                             const int[], int, int[], int),
                              const int conjuntoA[], int cantidadA,
                              const int conjuntoB[], int cantidadB,
                              const int esperado[], int cantidadEsperada,
                              int capacidad) {
    /* Las posiciones libres tienen datos para detectar recorridos de más. */
    int copiaA[CAPACIDAD_CONJUNTO];
    int copiaB[CAPACIDAD_CONJUNTO];
    /* Se reserva un centinela antes y espacio vigilado después del resultado. */
    int resultado[CAPACIDAD_RESULTADO + 2];
    int cantidad;

    for (int indice = 0; indice < CAPACIDAD_CONJUNTO; indice++) {
        copiaA[indice] = indice < cantidadA ? conjuntoA[indice] : CENTINELA;
        copiaB[indice] = indice < cantidadB ? conjuntoB[indice] : CENTINELA;
    }
    for (int indice = 0; indice < CAPACIDAD_RESULTADO + 2; indice++)
        resultado[indice] = CENTINELA;

    cantidad = operacion(copiaA, cantidadA, copiaB, cantidadB,
                         resultado + 1, capacidad);

    COMPROBAR(enterosIguales(resultado[0], CENTINELA));
    for (int indice = capacidad + 1; indice < CAPACIDAD_RESULTADO + 2; indice++)
        COMPROBAR(enterosIguales(resultado[indice], CENTINELA));
    for (int indice = 0; indice < CAPACIDAD_CONJUNTO; indice++) {
        COMPROBAR(enterosIguales(copiaA[indice],
                                indice < cantidadA ? conjuntoA[indice]
                                                   : CENTINELA));
        COMPROBAR(enterosIguales(copiaB[indice],
                                indice < cantidadB ? conjuntoB[indice]
                                                   : CENTINELA));
    }
    COMPROBAR(enterosIguales(cantidad, cantidadEsperada));
    if (cantidadEsperada >= 0)
        COMPROBAR(arreglosIguales(resultado + 1, esperado, cantidadEsperada));
    return 1;
}

/* Ejecuta un caso de una operación y conserva un nombre legible en la salida. */
#define PROBAR_OPERACION(nombre, operacion, a, na, b, nb, esperado, ne, cap) \
    registrarResultado(nombre, verificarOperacion(operacion, a, na, b, nb, \
                                                   esperado, ne, cap))

/* Pruebas unitarias para unirConjuntos. */
static void testUnirConjuntos(void) {
    int a[] = {17, 23, 31, 44};
    int b[] = {23, 44, 58};
    int esperado[] = {17, 23, 31, 44, 58};
    int vacio[] = {0};
    int desordenado[] = {44, 17, 31, 23};
    int ordenEsperado[] = {44, 17, 31, 23, 58};
    int inversoEsperado[] = {23, 44, 58, 17, 31};
    int extremos[] = {INT_MIN, 0, INT_MAX};
    int negativos[] = {0, -1, INT_MIN};
    int enterosEsperados[] = {INT_MIN, 0, INT_MAX, -1};
    int llenoA[CAPACIDAD_CONJUNTO];
    int llenoB[CAPACIDAD_CONJUNTO];
    int unionLlena[CAPACIDAD_RESULTADO];

    PROBAR_OPERACION("unión: caso del ejemplo", unirConjuntos,
                     a, 4, b, 3, esperado, 5, CAPACIDAD_RESULTADO);
    PROBAR_OPERACION("unión: conserva el orden sin ordenar", unirConjuntos,
                     desordenado, 4, b, 3, ordenEsperado, 5, 5);
    PROBAR_OPERACION("unión: entradas intercambiadas", unirConjuntos,
                     b, 3, a, 4, inversoEsperado, 5, 5);
    PROBAR_OPERACION("unión: conjuntos iguales", unirConjuntos,
                     a, 4, a, 4, a, 4, 4);
    PROBAR_OPERACION("unión: A vacío", unirConjuntos,
                     vacio, 0, b, 3, b, 3, 3);
    PROBAR_OPERACION("unión: B vacío", unirConjuntos,
                     a, 4, vacio, 0, a, 4, 4);
    PROBAR_OPERACION("unión: ambos vacíos sin capacidad", unirConjuntos,
                     vacio, 0, vacio, 0, vacio, 0, 0);
    PROBAR_OPERACION("unión: capacidad exacta", unirConjuntos,
                     a, 4, b, 3, esperado, 5, 5);
    PROBAR_OPERACION("unión: falta capacidad al copiar A", unirConjuntos,
                     a, 4, b, 3, vacio, -1, 2);
    PROBAR_OPERACION("unión: falta capacidad al agregar B", unirConjuntos,
                     a, 4, b, 3, vacio, -1, 4);
    PROBAR_OPERACION("unión: sin capacidad", unirConjuntos,
                     a, 4, b, 3, vacio, -1, 0);
    PROBAR_OPERACION("unión: cero, negativos y extremos", unirConjuntos,
                     extremos, 3, negativos, 3, enterosEsperados, 4, 4);

    for (int indice = 0; indice < CAPACIDAD_CONJUNTO; indice++) {
        llenoA[indice] = indice;
        llenoB[indice] = CAPACIDAD_CONJUNTO + indice;
        unionLlena[indice] = llenoA[indice];
        unionLlena[CAPACIDAD_CONJUNTO + indice] = llenoB[indice];
    }
    PROBAR_OPERACION("unión: dos conjuntos llenos disjuntos", unirConjuntos,
                     llenoA, CAPACIDAD_CONJUNTO, llenoB, CAPACIDAD_CONJUNTO,
                     unionLlena, CAPACIDAD_RESULTADO, CAPACIDAD_RESULTADO);
}

/* Pruebas unitarias para intersectarConjuntos. */
static void testIntersectarConjuntos(void) {
    int a[] = {17, 23, 31, 44};
    int b[] = {23, 44, 58};
    int esperado[] = {23, 44};
    int vacio[] = {0};
    int desordenado[] = {44, 17, 31, 23};
    int ordenEsperado[] = {44, 23};
    int disjunto[] = {99, 100};
    int extremos[] = {INT_MAX, -1, 0, INT_MIN};
    int negativos[] = {INT_MIN, 0, -1};
    int enterosEsperados[] = {-1, 0, INT_MIN};

    PROBAR_OPERACION("intersección: caso del ejemplo", intersectarConjuntos,
                     a, 4, b, 3, esperado, 2, CAPACIDAD_RESULTADO);
    PROBAR_OPERACION("intersección: conserva el orden de A",
                     intersectarConjuntos,
                     desordenado, 4, b, 3, ordenEsperado, 2, 2);
    PROBAR_OPERACION("intersección: conjuntos iguales", intersectarConjuntos,
                     a, 4, a, 4, a, 4, 4);
    PROBAR_OPERACION("intersección: A contenido en B", intersectarConjuntos,
                     esperado, 2, a, 4, esperado, 2, 2);
    PROBAR_OPERACION("intersección: conjuntos disjuntos", intersectarConjuntos,
                     a, 4, disjunto, 2, vacio, 0, CAPACIDAD_RESULTADO);
    PROBAR_OPERACION("intersección: disjuntos sin capacidad",
                     intersectarConjuntos, a, 4, disjunto, 2, vacio, 0, 0);
    PROBAR_OPERACION("intersección: A vacío", intersectarConjuntos,
                     vacio, 0, b, 3, vacio, 0, 0);
    PROBAR_OPERACION("intersección: B vacío", intersectarConjuntos,
                     a, 4, vacio, 0, vacio, 0, 0);
    PROBAR_OPERACION("intersección: ambos vacíos", intersectarConjuntos,
                     vacio, 0, vacio, 0, vacio, 0, 0);
    PROBAR_OPERACION("intersección: capacidad exacta", intersectarConjuntos,
                     a, 4, b, 3, esperado, 2, 2);
    PROBAR_OPERACION("intersección: capacidad insuficiente",
                     intersectarConjuntos, a, 4, b, 3, vacio, -1, 1);
    PROBAR_OPERACION("intersección: sin capacidad", intersectarConjuntos,
                     a, 4, b, 3, vacio, -1, 0);
    PROBAR_OPERACION("intersección: cero, negativos y extremos",
                     intersectarConjuntos,
                     extremos, 4, negativos, 3, enterosEsperados, 3, 3);
}

/* Pruebas unitarias para diferenciarConjuntos. */
static void testDiferenciarConjuntos(void) {
    int a[] = {17, 23, 31, 44};
    int b[] = {23, 44, 58};
    int esperado[] = {17, 31};
    int vacio[] = {0};
    int desordenado[] = {31, 44, 17, 23};
    int ordenEsperado[] = {31, 17};
    int inversoEsperado[] = {58};
    int disjunto[] = {99, 100};
    int extremos[] = {INT_MAX, -1, 0, INT_MIN};
    int negativos[] = {-1};
    int enterosEsperados[] = {INT_MAX, 0, INT_MIN};

    PROBAR_OPERACION("diferencia: caso del ejemplo", diferenciarConjuntos,
                     a, 4, b, 3, esperado, 2, CAPACIDAD_RESULTADO);
    PROBAR_OPERACION("diferencia: conserva el orden de A", diferenciarConjuntos,
                     desordenado, 4, b, 3, ordenEsperado, 2, 2);
    PROBAR_OPERACION("diferencia: B-A es distinta de A-B", diferenciarConjuntos,
                     b, 3, a, 4, inversoEsperado, 1, 1);
    PROBAR_OPERACION("diferencia: conjuntos iguales", diferenciarConjuntos,
                     a, 4, a, 4, vacio, 0, 0);
    PROBAR_OPERACION("diferencia: A contenido en B", diferenciarConjuntos,
                     esperado, 2, a, 4, vacio, 0, 0);
    PROBAR_OPERACION("diferencia: conjuntos disjuntos", diferenciarConjuntos,
                     a, 4, disjunto, 2, a, 4, 4);
    PROBAR_OPERACION("diferencia: A vacío", diferenciarConjuntos,
                     vacio, 0, b, 3, vacio, 0, 0);
    PROBAR_OPERACION("diferencia: B vacío", diferenciarConjuntos,
                     a, 4, vacio, 0, a, 4, 4);
    PROBAR_OPERACION("diferencia: ambos vacíos", diferenciarConjuntos,
                     vacio, 0, vacio, 0, vacio, 0, 0);
    PROBAR_OPERACION("diferencia: capacidad exacta", diferenciarConjuntos,
                     a, 4, b, 3, esperado, 2, 2);
    PROBAR_OPERACION("diferencia: capacidad insuficiente", diferenciarConjuntos,
                     a, 4, b, 3, vacio, -1, 1);
    PROBAR_OPERACION("diferencia: sin capacidad", diferenciarConjuntos,
                     a, 4, b, 3, vacio, -1, 0);
    PROBAR_OPERACION("diferencia: cero, negativos y extremos",
                     diferenciarConjuntos,
                     extremos, 4, negativos, 1, enterosEsperados, 3, 3);
}

/*
 * Ejecuta todas las pruebas y muestra el resumen.
 * Regresa EXIT_SUCCESS si todas pasan; EXIT_FAILURE si alguna falla.
 */
int main(void) {
    registrarResultado("búsqueda: presentes y ausente", testBuscarElemento());
    registrarResultado("búsqueda: posiciones utilizadas",
                       testBuscarPosicionesUtilizadas());
    registrarResultado("búsqueda: conjunto vacío", testBuscarVacio());
    registrarResultado("búsqueda: cero, negativos y extremos",
                       testBuscarEnteros());
    registrarResultado("agregar: conjunto vacío", testAgregarVacio());
    registrarResultado("agregar: nuevo elemento al final", testAgregarElemento());
    registrarResultado("agregar: elemento repetido", testAgregarRepetido());
    registrarResultado("agregar: capacidad llena", testAgregarLleno());
    registrarResultado("agregar: sin capacidad", testAgregarSinCapacidad());
    registrarResultado("agregar: cero, negativos y extremos", testAgregarEnteros());
    registrarResultado("eliminar: primero", testEliminarPrimero());
    registrarResultado("eliminar: intermedio", testEliminarIntermedio());
    registrarResultado("eliminar: último", testEliminarUltimo());
    registrarResultado("eliminar: único elemento", testEliminarUnico());
    registrarResultado("eliminar: inexistente", testEliminarInexistente());
    registrarResultado("eliminar: conjunto vacío", testEliminarVacio());
    registrarResultado("eliminar: negativos y extremos", testEliminarEnteros());
    registrarResultado("agregar y eliminar: reutilizar espacio",
                       testReutilizarEspacio());
    registrarResultado("reemplazar: inicio, medio y final",
                       testReemplazarPosiciones());
    registrarResultado("reemplazar: evita repetidos", testReemplazarRepetido());
    registrarResultado("reemplazar: mismo valor", testReemplazarMismo());
    registrarResultado("reemplazar: inexistente", testReemplazarInexistente());
    registrarResultado("reemplazar: conjunto vacío", testReemplazarVacio());
    registrarResultado("reemplazar: posiciones utilizadas",
                       testReemplazarPosicionesUtilizadas());
    registrarResultado("reemplazar: único elemento", testReemplazarUnico());
    registrarResultado("reemplazar: cero, negativos y extremos",
                       testReemplazarEnteros());
    registrarResultado("vaciar: conjunto con elementos", testVaciarConjunto());
    registrarResultado("vaciar: conjunto vacío", testVaciarVacio());
    registrarResultado("vaciar: reutilizar la capacidad", testVaciarYReutilizar());
    testCopiarConjunto();
    testEsSubconjunto();
    testSonConjuntosIguales();
    testUnirConjuntos();
    testIntersectarConjuntos();
    testDiferenciarConjuntos();

    printf("\nPruebas: %d; pasaron: %d; fallaron: %d.\n",
           pruebas, pruebas - fallas, fallas);
    return fallas == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
