# Reloj gigante con ncurses

Aplicación de terminal escrita en C que dibuja un reloj digital de dígitos grandes usando `ncurses`. Actualiza la hora cada 100 ms y permite salir cómodamente con `q`.

## Características
- Dígitos ASCII de 9x10 caracteres para `HH:MM:SS` centrados en pantalla.
- Aviso automático si la terminal no tiene espacio suficiente para renderizar el reloj.
- Interfaz sin parpadeos gracias a la redibujado completo en modo `ncurses`.

## Requisitos
- Compilador C compatible (ej. `cc`, `clang` o `gcc`).
- Biblioteca `ncurses` y cabeceras de desarrollo (`libncurses-dev` en Debian/Ubuntu, `ncurses` en macOS vía Homebrew, etc.).

## Compilación
```bash
cc main.c -lncurses -o reloj
```

## Uso
```bash
./reloj
```
- Presiona `q` (o `Q`) para salir.
- Amplía la ventana si aparece el mensaje "Ampliar la ventana del terminal".

## Estructura del proyecto
- `main.c`: lógica completa del reloj y definición de los glifos.
- `reloj`: binario resultante tras compilar (no se versiona normalmente).

## Próximos pasos sugeridos
- Añadir argumentos CLI (por ejemplo, elegir formato 12/24 h).
- Integrar colores o resaltados para mejorar la legibilidad nocturna.
