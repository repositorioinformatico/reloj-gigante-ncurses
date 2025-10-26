# Registro de acciones del agente

1. Creé `main.c` con un reloj ncurses básico a pantalla completa que muestra la hora centrada (`%H:%M:%S`) y permite salir con `q`.
2. Compilé y probé el binario con `cc main.c -lncurses -o reloj` y ejecución breve de `./reloj`.
3. Reemplacé la implementación para dibujar dígitos gigantes (~9x10 caracteres cada uno) y mostrar un mensaje cuando la terminal es demasiado pequeña.
4. Volví a compilar y ejecuté `./reloj` para verificar el nuevo estilo, confirmando también el aviso de tamaño insuficiente.
