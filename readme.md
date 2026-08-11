# Emulador Chip 8
Bienvenido a mi proyecto personal y el "Hola Mundo" de la emulación para entender
las cosas desde lo más simple a lo más complejo, si bien he tenido un poco
de dificultades al iniciar este proyecto he estado investigando, buscando referencias
e incluso preguntándole a la IA como apoyo pero sin copiar el código directamente.

## Fuentes
Algunos recursos utilizados para este proyecto como se nombró anteriormente fue
utilizar distintas IA para consulta sobre OpCodes; sin embargo, los documentos que se utilizaron
oficialmente van a continuación.

1. **CowGod's Chip-8 Technical Reference** http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#2.0
2. **Austin Morlan Chip8 Emulator** https://austinmorlan.com/posts/chip8_emulator/
3. **Chip 8 Roms** https://github.com/kripod/chip8-roms/tree/master

## Lógica nivel maquina

### Memoria
La memoria abarca desde los valores 0 hasta 0xFFF (4095) donde las direcciones
0 y 0x1FF son reservadas para el intérprete mientras que la mayoría de los programas
de Chip8 inician en 0x200

### Registros
El emulador Chip 8 tiene 16 registros generalmente de 8-bits, usualmente se refiere
a **Vx** donde **x** es un número hexadecimal. También existe un registro 16-bit llamado I o Index.
Este registro generalmente guarda la dirección de memoria y usualmente utiliza los 12 bits
más bajos.

El registro **Vf** no debería ser usado por ningún programa y es usado como una bandera
según la instrucción.

Otros registros a tener en cuenta son 2 de 8-bit y tiene que ver con el delay y con el sonido, cuando 
los registros no son cero estos disminuyen automáticamente a un ritmo de 60hz.

Por último existen pseudo registros el cual no son accesible por los programas de Chip8, 
algunos de ellos son el Program Counter (PC) (16-Bit) y Stack Pointer (SP) (8-Bit).

El Stack es un arreglo de 16 valores de 16-Bit y es usado para almacenar direcciones
que el intérprete debe de activarlo cuando finaliza la subrutina.

### Keyboard
En el teclado hay una representación como es originalmente y como se representó en el
teclado del PC.

<table>
  <tr>
    <th colspan="4">CHIP-8</th>
    <th></th>
    <th>Teclado</th>
  </tr>
  <tr><td>1</td><td>2</td><td>3</td><td>C</td><td>→→→</td><td>1 2 3 4</td></tr>
  <tr><td>4</td><td>5</td><td>6</td><td>D</td><td>→→→</td><td>Q W E R</td></tr>
  <tr><td>7</td><td>8</td><td>9</td><td>E</td><td>→→→</td><td>A S D F</td></tr>
  <tr><td>A</td><td>0</td><td>B</td><td>F</td><td>→→→</td><td>Z X C V</td></tr>
</table>

### Display
Básicamente, la pantalla interna manejada en la emulación respeta el tamaño que es originalmente de (64,32)
para evitar conflictos o código más complejo, por otro lado los sprites ya se cargan por defecto en el interprete
del Chip 8.

### Delay timer, Sound timer y OpCodes
El Chip 8 tiene 2 timer uno es para el sonido y otro de delay en los cuales se decrementan 1 cada 60hz
siempre y cuando sea distinto a 0.

Por último tenemos los opcodes que son demasiados y es mejor leer la propia guía para ver como
interactúa con el sistema mismo, para entender los opcodes es necesario entender las variables que se utilizan 
y estos están descritos en las mismas instrucciones del documento.

## SDL3 - Renderizado
Finalmente, una vez completada la emulación se debe de renderizar en un lugar gráfico
el cual se utiliza la libreria SDL3 para crear ventana, renderizar, aplicar un texture (Aplica píxeles dado un arreglo)
ademas de bloquear y desbloquear la pantalla para grabar pixeles.

## Futuros proyectos
Una vez hecho todo esto es posible utilizarse para futuros proyectos a tener en cuenta, alguno de ellos son:
1. Utilizar una IA que aprenda a jugar alguna ROM
2. Desarrollar aún más el emulador implementando estados de guardado y conectándolo con el lenguaje C#
3. Implementar este modelo Chip 8 en la realidad con Arduino o un Raspberry.

## Generar .exe
### CLion
Presionar CTRL + F9 para buildear el .exe (Puedes usar tanto Debug como Release)
### Consola
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```