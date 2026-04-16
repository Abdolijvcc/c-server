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
//#include <sys/stat.h>
#include <stdlib.h>
#ifdef _WIN32  
#include <windows.h>  
#define SLEEP_MS(ms) Sleep(ms)  
#else  
#include <unistd.h>  
#define SLEEP_MS(ms) usleep((ms) * 1000)  
#endif 

Cola miCola;

int main(){
   
    const char *ruta_entrada = "C:\\Users\\User\\Videos";
    const char *ruta_salida = "C:\\Users\\User\\Videos\\convertidos";
    system("mkdir C:\\Users\\User\\Videos\\convertidos");

    //configurar_consola();
    inicializarCola(&miCola, 10);

    printf("Escaneando carpeta inicial...\n");
    recorrer_directorios(ruta_entrada);

    printf("\nProcesando cola...\n");
    procesar_cola(ruta_salida);

    /* printf("\nWatcher preparado...\n");
    vigilar_directorio(ruta_entrada); */

    //inicializar watcher() aqui para no bloquear el proceso principal mientras se comprime el video, y asi poder seguir procesando la cola y vigilando el directorio
    //inicializar modo servidor para que conostantemente escanee la carpeta de entrada y añada nuevos videos a la cola, y el worker() vaya procesando la cola sin bloquear el proceso principal
    printf("\niniciando modo servidor...\n");  
    for (;;){  
        // Solo procesar si hay algo en la cola  
        if (!esVacia(&miCola)){  
            printf("\nProcesando cola...\n");  
            procesar_cola(ruta_salida);  
        }  

        // Esperar antes de volver a escanear  
        //#ifdef _WIN32  
        SLEEP_MS(250000); // 10 segundos en milisegundos  
       // #else  
        //SLEEP_MS(10000); // 10 segundos en microsegundos  
        //#endif  

        // Escanear solo si la cola está vacía  
        if (esVacia(&miCola)){
            // si el video ya esta hecho pues no hace falta ponerlo en la lista de espera
              
            recorrer_directorios(ruta_entrada);  
        }  
    }

    liberar_cola(&miCola);

    return 0;
}
