/*
- Coger item de la queue
- Construir string del comando: "HandBrakeCLI -i input -o output [tus flags]"
- CreateProcess() en Windows / fork()+exec() en Linux
- Esperar a que termine: WaitForSingleObject() / waitpid()
*/