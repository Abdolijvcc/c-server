/*
- Configurar consola segun sistema
- En Windows poner UTF-8 para acentos
- En Linux dejar locale del sistema
*/

#include "platform.h"

#ifdef _WIN32
#include <fcntl.h>
#include <io.h>
#include <locale.h>
#include <stdio.h>
#include <windows.h>

void configurar_consola(void){
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    setlocale(LC_ALL, ".UTF-8");
    _setmode(_fileno(stdout), _O_U8TEXT);
}
#else
#include <locale.h>

void configurar_consola(void){
    setlocale(LC_ALL, "");
}
#endif
