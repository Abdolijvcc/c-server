/*
- Separar Windows y Linux con ifdef
- Incluir cabeceras segun sistema
- Dejar una base simple para usar despues
*/

#ifndef PLATFORM_H
#define PLATFORM_H

#ifdef _WIN32
#define SEPARADOR_RUTA "\\"
#else
#define SEPARADOR_RUTA "/"
#endif

#ifdef _WIN32  
#include <windows.h>  
#define SLEEP_MS(ms) Sleep(ms)  
#else  
#include <unistd.h>  
#define SLEEP_MS(ms) usleep((ms) * 1000)  
#endif
void configurar_consola(void);

#endif
