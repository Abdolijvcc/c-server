/*
- Inicializar la cola
- Elegir ruta de entrada y salida
- Lanzar scanner() una vez al arrancar
- Procesar lo encontrado en la cola
- Dejar watcher() preparado para el siguiente paso
*/

#include <stdio.h>
#include "platform.h"
#include "queue.h"
#include "scanner.h"
#include "worker.h"
#include "watcher.h"

Cola miCola;

int main( void ){
    const char *ruta_entrada = "C:\\Users\\User\\Videos";
    const char *ruta_salida = "C:\\Users\\User\\Videos\\convertidos";

    configurar_consola();
    inicializarCola(&miCola, 10);

    printf("Escaneando carpeta inicial...\n");
    recorrer_directorios(ruta_entrada);

    printf("\nProcesando cola...\n");
    procesar_cola(ruta_salida);

    printf("\nWatcher preparado...\n");
    vigilar_directorio(ruta_entrada);

    liberar_cola(&miCola);
    return 0;
}
