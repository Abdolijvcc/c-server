/*
- Windows: ReadDirectoryChangesW() en bucle
- Linux: inotify_init() + inotify_add_watch() + read()
- Cuando detecta archivo nuevo -> filter() -> si es video -> enqueue()
- De momento queda montado como modulo separado
*/

#include <stdio.h>
#include "watcher.h"

void vigilar_directorio(const char *ruta){
    printf("Watcher pendiente de implementar para: %s\n", ruta);
}
