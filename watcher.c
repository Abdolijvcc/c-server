/*
- Windows: ReadDirectoryChangesW() en bucle
- Linux: inotify_init() + inotify_add_watch() + read()
- Cuando detecta archivo nuevo → filter() → si vídeo → enqueue()
*/
