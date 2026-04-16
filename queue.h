#ifndef QUEUE_H
#define QUEUE_H

typedef enum { PENDIENTE, PROCESANDO, HECHO } Estado;

typedef struct {
    char *ruta;
    Estado estado;
} Elemento;

typedef struct {
    Elemento *elementos;
    int frente;
    int final;
    int capacidad;
    int tamano;
} Cola;

extern Cola miCola;

void inicializarCola(Cola *q, int capacidad_inicial);
void enqueue(Cola *q, const char *ruta);
Elemento dequeue(Cola *q);
int esVacia(Cola *q);
void liberar_cola(Cola *q);

#endif
