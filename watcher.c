/*
- Windows: ReadDirectoryChangesW() en bucle
- Linux: inotify_init() + inotify_add_watch() + read()
- Cuando detecta archivo nuevo -> filter() -> si es video -> enqueue()
- De momento queda montado como modulo separado
*/

#include <stdio.h>
#include "watcher.h"
#include "queue.h"
#ifdef _WIN32
#include <windows.h>  
  
void vigilar_directorio(const char *ruta) {  
    HANDLE dirHandle = CreateFile(  
        ruta,  
        FILE_LIST_DIRECTORY,  
        FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,  
        NULL,  
        OPEN_EXISTING,  
        FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED,  
        NULL  
    );  
      
    char buffer[1024];  
    DWORD bytesReturned;  
      
    while (1) {  
        if (ReadDirectoryChangesW(dirHandle, buffer, sizeof(buffer), TRUE,  
            FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_SIZE,  
            &bytesReturned, NULL, NULL)) {  
              
            // Procesar eventos y agregar videos a la cola  
            // Llamar a es_video() y enqueue()  
        }  
    }  
}  
#else
#include <sys/inotify.h>
#include <unistd.h>

void vigilar_directorio(const char *ruta) {
    int fd = inotify_init();
    if (fd < 0) {
        perror("inotify_init");
        return;
    }

    int wd = inotify_add_watch(fd, ruta, IN_CREATE | IN_MOVED_TO);
    if (wd < 0) {
        perror("inotify_add_watch");
        close(fd);
        return;
    }

    char buffer[1024];
    while (1) {
        int length = read(fd, buffer, sizeof(buffer));
        if (length < 0) {
            perror("read");
            break;
        }

        // Procesar eventos y agregar videos a la cola
        // Llamar a es_video() y enqueue()
    }

    inotify_rm_watch(fd, wd);
    close(fd);
}
#endif