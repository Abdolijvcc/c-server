/*
- Coger item de la queue
- Construir string del comando de HandBrake
- Lanzar el proceso mas adelante
- De momento dejar claro que archivo tocaria procesar
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "platform.h"
#include "worker.h"
#include "queue.h"

void procesar_cola(const char *ruta_salida){
    while (!esVacia(&miCola)){
        Elemento elemento = dequeue(&miCola);
        char comando[1024];
        char ruta_final[1024];
        const char *ultimo_barra_invertida = strrchr(elemento.ruta, '\\');
        const char *ultimo_barra_normal = strrchr(elemento.ruta, '/');
        const char *nombre_archivo = ultimo_barra_invertida;

        if (ultimo_barra_normal != NULL && (nombre_archivo == NULL || ultimo_barra_normal > nombre_archivo)){
            nombre_archivo = ultimo_barra_normal;
        }

        if (nombre_archivo == NULL){
            nombre_archivo = elemento.ruta;
        } else {
            nombre_archivo++;
        }

        snprintf(ruta_final, sizeof(ruta_final), "%s%s%s", ruta_salida, SEPARADOR_RUTA, nombre_archivo);

        snprintf(comando, sizeof(comando),
            "bin/HandBrakeCLI.exe -i \"%s\" -o \"%s\" "
            "--preset \"Very Fast 480p30\" "
            "-e x265 "
            "-q 35 "
            "--vfr "
            "-B 64 "
            "-E av_aac "
            "2>&1",
            elemento.ruta, ruta_final
        );

        printf("Procesando: %s\n", elemento.ruta);
        printf("Comando: %s\n", comando);

        elemento.estado = HECHO;
        free(elemento.ruta);
    }
}
