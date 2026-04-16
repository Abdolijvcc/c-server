/*
- Struct con ruta del archivo + estado
- enqueue() -> añadir video
- dequeue() -> sacar el siguiente
- Array dinamico con malloc/realloc
*/

#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void inicializarCola(Cola *q, int capacidad_inicial){
    q->elementos = malloc(capacidad_inicial * sizeof(Elemento));
    if (!q->elementos){
        exit(1);
    }

    q->frente = 0;
    q->final = -1;
    q->capacidad = capacidad_inicial;
    q->tamano = 0;
}

void enqueue(Cola *q, const char *ruta){
    if (q->tamano == q->capacidad){
        q->capacidad *= 2;
        q->elementos = realloc(q->elementos, q->capacidad * sizeof(Elemento));

        if (!q->elementos){
            exit(1);
        }
    }

    q->final = (q->final + 1) % q->capacidad;
    q->elementos[q->final].ruta = malloc(strlen(ruta) + 1);

    if (!q->elementos[q->final].ruta){
        exit(1);
    }

    strcpy(q->elementos[q->final].ruta, ruta);
    q->elementos[q->final].estado = PENDIENTE;
    q->tamano++;
}

Elemento dequeue(Cola *q){
    if (esVacia(q)){
        fprintf(stderr, "Cola vacia\n");
        exit(1);
    }

    q->elementos[q->frente].estado = PROCESANDO;

    Elemento elemento = q->elementos[q->frente];
    q->frente = (q->frente + 1) % q->capacidad;
    q->tamano--;

    return elemento;
}

int esVacia(Cola *q){
    return q->tamano == 0;
}

void liberar_cola(Cola *q){
    while (!esVacia(q)){
        Elemento elemento = dequeue(q);
        free(elemento.ruta);
    }

    free(q->elementos);
    q->elementos = NULL;
    q->frente = 0;
    q->final = -1;
    q->capacidad = 0;
    q->tamano = 0;
}
