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

void configurar_consola(void);

#endif
