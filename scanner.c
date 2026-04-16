/*
- opendir() / readdir() / closedir()
- Recursividad para subcarpetas
- Por cada archivo -> llamar filter()
- Si es video -> meter en queue
*/

#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "scanner.h"
#include "filter.h"
#include "platform.h"
#include "queue.h"

void recorrer_directorios(const char *ruta_actual){
    struct dirent *entrada;
    DIR *directorio = opendir(ruta_actual);

    if (directorio == NULL){
        perror("opendir");
        return;
    }

    while ((entrada = readdir(directorio)) != NULL){
        if (strcmp(entrada->d_name, ".") == 0 || strcmp(entrada->d_name, "..") == 0){
            continue;
        }

        char ruta_completa[512];
        struct stat info;

        snprintf(ruta_completa, sizeof(ruta_completa), "%s%s%s", ruta_actual, SEPARADOR_RUTA, entrada->d_name);

        if (stat(ruta_completa, &info) != 0){
            perror("stat");
            continue;
        }

        printf("Entrada: %s\n", ruta_completa);

        if (S_ISDIR(info.st_mode)){
            printf(" -> es un directorio. Recursividad...\n");
            recorrer_directorios(ruta_completa);
        } else {
            printf(" -> es un archivo\n");

            if (es_video(entrada->d_name) != NULL){
                printf("Archivo valido: %s\n", ruta_completa);
                enqueue(&miCola, ruta_completa);
            }
        }
    }

    closedir(directorio);
}
