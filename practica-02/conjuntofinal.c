/*
 * Archivo: conjunto.c
 * Implementación de conjuntos de enteros con arreglos de capacidad fija.
 * Completen las funciones pendientes según conjunto.h.
 * Usen funciones, arreglos y apuntadores; no usen estructuras, memoria
 * dinámica, archivos ni ordenamientos.
 * Autoría: Molina Fuentes Uri Israel
 */

#include <stdio.h>

#include "conjunto.h"

/* Busca únicamente en las posiciones utilizadas del conjunto. */
int buscarElemento(const int conjunto[], int cantidad, int elemento) {
    for (int indice = 0; indice < cantidad; indice++) {
        if (conjunto[indice] == elemento)
            return indice;
    }
    return -1;
}

/* Agrega un elemento si no existe y queda espacio. */
int agregarElemento(int conjunto[], int capacidad, int *cantidad,int elemento) {
    if (buscarElemento(conjunto, *cantidad, elemento) != -1){
        return 0;
    }    
    if (*cantidad >= capacidad) { // Corregido: se evalúa *cantidad en lugar del apuntador
        return 0;
    } 
    conjunto[*cantidad]= elemento;
    (*cantidad)++;
    return 1;
}

/* Elimina un elemento y conserva el orden de los restantes. */
int eliminarElemento(int conjunto[], int *cantidad, int elemento) {
    int indice = buscarElemento(conjunto, *cantidad, elemento);
    if (indice == -1) {
        return 0;
    }
    for (int i = indice; i < *cantidad - 1; i++) {
        conjunto[i] = conjunto[i + 1];
    }
    (*cantidad)--;
    return 1;       
}

/* Sustituye un elemento sin cambiar la cantidad ni introducir repetidos. */
int reemplazarElemento(int conjunto[], int cantidad, int elemento,
                       int reemplazo) {
    if (elemento == reemplazo) {
        return 0;
    }
    int indice = buscarElemento(conjunto, cantidad, elemento);
    if (indice == -1) {
        return 0;
    } // Corregido: faltaba cerrar esta llave
    
    conjunto[indice] = reemplazo;
    return 1;
}

/* Deja el conjunto vacío, conservando el arreglo y su capacidad. */
void vaciarConjunto(int *cantidad) {
    *cantidad = 0;
}

/* Copia los elementos a otro arreglo, conservando su orden. */
int copiarConjunto(const int origen[], int cantidad,
                   int destino[], int capacidadDestino) {
    if (capacidadDestino < cantidad) { // Corregido: se compara capacidadDestino en vez de la función
        return -1;
    }
    for (int i=0; i < cantidad; i++) {
        destino[i] = origen[i];
    }
    return cantidad;
}

/* Indica si A es subconjunto de B, sin importar el orden. */
int esSubconjunto(const int conjuntoA[], int cantidadA,
                 const int conjuntoB[], int cantidadB) {
    for (int i = 0; i < cantidadA; i++) {
        if (buscarElemento(conjuntoB, cantidadB, conjuntoA[i]) == -1) {
            return 0;
        }
    }
    return 1; // Corregido: faltaba retornar 1 si pasa todas las validaciones
}

/* Indica si los conjuntos tienen los mismos elementos, sin importar el orden. */
int sonConjuntosIguales(const int conjuntoA[], int cantidadA,
                       const int conjuntoB[], int cantidadB) {
    if (cantidadA != cantidadB) {
        return 0;
    }
    return esSubconjunto(conjuntoA, cantidadA, conjuntoB, cantidadB) &&
           esSubconjunto(conjuntoB, cantidadB, conjuntoA, cantidadA);             
}

/* Calcula la unión conservando primero A y después los elementos nuevos de B. */
int unirConjuntos(const int conjuntoA[], int cantidadA,
                 const int conjuntoB[], int cantidadB,
                 int resultado[], int capacidadResultado) {
    int cantidadresultadoactual = 0;

    if (capacidadResultado < cantidadA + cantidadB) {
        return -1;
    }
    for (int i = 0; i < cantidadA; i++) {
        resultado[i] = conjuntoA[i];
        cantidadresultadoactual++;
    }

    for (int i = 0; i < cantidadB; i++) {
        if (buscarElemento(resultado, cantidadresultadoactual, conjuntoB[i]) == -1) {
            if (cantidadresultadoactual >= capacidadResultado) { // Corregido: nombre de variable y lógica de capacidad
                return -1;
            }
            resultado[cantidadresultadoactual] = conjuntoB[i];
            cantidadresultadoactual++;
        }
    }
    return cantidadresultadoactual;
}

/* Calcula la intersección conservando el orden de A. */
int intersectarConjuntos(const int conjuntoA[], int cantidadA,
                        const int conjuntoB[], int cantidadB,
                        int resultado[], int capacidadResultado) {
    int cantidadresultadoactual = 0;

    for (int i = 0; i < cantidadA; i++) {
        if (buscarElemento(conjuntoB, cantidadB, conjuntoA[i]) != -1) {
            if (cantidadresultadoactual >= capacidadResultado) {
                return -1;
            }
            resultado[cantidadresultadoactual] = conjuntoA[i];
            cantidadresultadoactual++;
        }
    }
    return cantidadresultadoactual;
}

/* Calcula la diferencia A-B conservando el orden de A. */
int diferenciarConjuntos(const int conjuntoA[], int cantidadA,
                        const int conjuntoB[], int cantidadB,
                        int resultado[], int capacidadResultado) {
    int cantidadresultadoactual = 0;

    for (int i = 0; i < cantidadA; i++) {
        if (buscarElemento(conjuntoB, cantidadB, conjuntoA[i]) == -1) {
            if (cantidadresultadoactual >= capacidadResultado) {
                return -1;
            }
            resultado[cantidadresultadoactual] = conjuntoA[i];
            cantidadresultadoactual++;
        }
    }
    return cantidadresultadoactual;
}

/* Muestra el conjunto con llaves, comas y un salto de línea al final. */
void mostrarConjunto(const int conjunto[], int cantidad) {
    printf("{");
    for (int indice = 0; indice < cantidad; indice++) {
        if (indice > 0)
            printf(", ");
        printf("%d", conjunto[indice]);
    }
    printf("}\n");
}