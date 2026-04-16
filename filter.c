/*
- Lista de extensiones: .mp4 .mkv .avi .mov .wmv
- strcmp() / strrchr() para sacar la extension
- Devuelve la ruta si es video, NULL si no
*/

#include <stdio.h>
#include <string.h>
#include "filter.h"

const char *lista[] = {".mp4", ".mkv", ".avi", ".mov", ".wmv", ".flv", ".webm", ".m4v", ".3gp", ".3g2", ".mts", ".m2ts", ".ts", ".vob", ".mpeg", ".mpg", ".iso"};


const char* es_video(const char *nombre_del_archivo){
    int numero_de_extensiones = 5;
    const char *punto = strrchr(nombre_del_archivo, '.');

    if (punto == NULL){
        printf("no tiene punto\n");
        return NULL;
    }

    for (int i = 0; i < numero_de_extensiones; i++){
        if (strcmp(punto, lista[i]) == 0){
            return nombre_del_archivo;
        }
    }

    return NULL;
}
