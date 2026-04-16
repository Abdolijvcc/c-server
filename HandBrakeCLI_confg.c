#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HandBrakeCLI_confg.h"

void compress_video(const char *input, const char *output) {
    char command[2048];

    // Preset mas rapido + x265 + calidad baja (RF 35 = mucha compresion)
    snprintf(command, sizeof(command),
    "HandBrakeCLI.exe -i \"%s\" -o \"%s\" "
    "-e x265 "
    "-q 26 "
    "--encoder-preset slow "
    "--vfr "
    "-B 96 "
    "-E av_aac "
    "2>&1",
    input, output
);

    FILE *fp = popen(command, "r");
    if (!fp) {
        printf("Error al ejecutar HandBrakeCLI\n");
        return;
    }
    else{
        printf("\nque crack que eres tio como lo has conseguido\nDale maquina que vas a ser el mejor programador del mundo inshaallah\n");
    }

    char line[1024];
    while (fgets(line, sizeof(line), fp)) {
        // HandBrakeCLI imprime el progreso en estas lineas
        if (strstr(line, "ETA") || strstr(line, "Encoding")) {
            printf("\r%s", line);
            fflush(stdout);
        }
        /* else {
            printf("algo ha fallado o es un mensaje de log, lo imprimo por si acaso: %s", line);
            //printf("%s", line);
        } */
    }

    int result = pclose(fp);
    if (result == 0)
        printf("\nCompresion completada: %s\n", output);
    else{
        printf("\nError. Codigo: %d\n", result);
        printf("Revisa si el video de entrada es correcto, si el preset es compatible con tu version de HandBrakeCLI, o si tienes permisos para escribir en la carpeta de salida.\n");
    }
}
