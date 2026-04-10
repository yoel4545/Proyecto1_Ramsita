# Proyecto - PagedArray

## Descripción:
Es una implementación de una clase "PagedArray" que permite manejar arreglos de gran tamaño sin mantener todo su contenido en memoria principal, utilizando conceptos de paginación y el algoritmo de reemplazo LRU(Least Recently Used).

# Estructura del proyecto
-PagedArray.h //Definición de la clase PagedArray
-PagedArray.cpp # Implementación de PagedArray
-algoritmos_ordenamiento.h # Declaración de algoritmos de ordenamiento
-algoritmos_ordenamiento.cpp # Implementación de algoritmos
-generator.cpp # Generador de archivos binarios
-sorter.cpp # Ordenador con PagedArray
-README.md # Este archivo

# Requisitos
-Compilador C++
-Windows: MinGW
-Linux/Mac: g++

______________________________________________________________________________________________________
# Compilaciones

# Compilar generator
g++ -O2 -o generator.exe generator.cpp

# Compilar sorter
g++ -O2 -o sorter sorter.cpp PagedArray.cpp algoritmos_ordenamiento.cpp

______________________________________________________________________________________________________

## Uso
# generator
Crea archivos binarios con números alearotios.

# Sintaxis
./generator -size <TAMAÑO> -output <archivo_salida>

# Tamaños disponibles
 SMALL  -> 32 MB  (8,388,608 enteros)
 MEDIUM -> 64 MB  (16,777,216 enteros)
 LARGE  -> 128 MB (33,554,432 enteros)

# Ejemplos
./generator -size SMALL -output datos.bin
./generator -size MEDIUM -output pruebas/medium.bin
./generator -size LARGE -output large.bin

# Sorter
Ordena archivos binarios usando PagedArray.

# Sintaxis
./sorter -input <archivo_entrada> -output <archivo_salida> -alg <algoritmo> -pageSize <PAGESIZE> -pageCount <PAGECOUNT>

# Algoritmos disponibles
 - quickSort      (recomendado para archivos grandes)
 - shellSort      (aceptable para archivos medianos)
 - insertionSort  (solo para archivos pequeños < 8MB)
 - selectionSort  (solo para archivos pequeños < 8MB)
 - bubbleSort     (solo para archivos pequeños < 8MB)

# Recomendaciones de pageSize y pageCount según el tamaño del archivo:

 Para archivos de 32 MB (SMALL)
 - pageSize: 1,048,576 (1 MB)
 - pageCount: 32
 - Tiempo esperado (quickSort): ~1.7 segundos

# Para archivos de 64 MB (MEDIUM)
 - pageSize: 2,097,152 (2 MB)
 - pageCount: 32
 - Tiempo esperado (quickSort): ~3.6 segundos

# Para archivos de 128 MB (LARGE)
 - pageSize: 4,194,304 (4 MB)
 - pageCount: 32
- Tiempo esperado (quickSort): ~7.4 segundos

# Ejemplos
./sorter -input datos.bin -output ordenado.bin -alg quickSort -pageSize 4096 -pageCount 10

# Configuración óptima para 32MB (recomendada)
./sorter -input datos.bin -output out.bin -alg quickSort -pageSize 1048576 -pageCount 32



_________________________________________________________________________________________-

# Parametros

-input	Archivo binario de entrada a ordenar
-output	Archivo de salida (sin extensión, se generará .bin y .txt)
-alg	Algoritmo de ordenamiento
-pageSize	Cantidad de enteros por página
-pageCount	Máximo de páginas que caben en memoria RAM
