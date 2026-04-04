//
// Created by yoelr on 12/3/2026.
//

#ifndef PROYECTO1_RAMSITA_PAGEDARRAY_H
#define PROYECTO1_RAMSITA_PAGEDARRAY_H

#include <iostream> //la de siempre
#include <cmath> // matematicas
#include <iomanip>// para los cout
#include <fstream> //para los file
#include <string> //para poder usar string en el convertidor
#include <ctime> //para time
#include <cstdlib> //para rand y srand
using namespace std;

struct Page {
    int* data;//en la pagina cada pagina va a tener un puntero que es la informacion de los numeros
    int numero_pagina;//numero de pagina es el basicamente el nombre de la pagina
    int ultimo_acceso;// se usa con el timer que se va subiendo y cuando se usa la pagina se iguala al timer
};



class PagedArray {
private:
    int pageSize; // el tama;o de cada pagina
    int pageCount; //la cantidad de paginas que van a caber en ram
    fstream ramsita_file;// el archivo con los datos binarios
    Page* ram;// el espacio que reservaremos en la memoria, ejemplo, si se piden 4 paginas, entonces el espacio reservado sera 4 paginas
    unsigned long long timer; //contador para el lru
    unsigned long long pageHits;//contador para la cantida de page hits que sucedan
    unsigned long long pageFaults;//contador para la cantidad de page faults que sucedan
    int ultimoUsado();
    long long cantidadElementos;
    int elementosEnPagina(int numeroPagina) const;// muestra la cantidad de numeros que tiene la pagina(se usa para la pagina final)
public:
    //constructor
    PagedArray(string nombreArchivo, int pageSize, int pageCount);
    //destructor que limpia la memoria antes de cerrar el archivo
    ~PagedArray();
    //sobrecargador
    int& operator[](int index);
    //estadisticas
    void estadisticas();
};




#endif //PROYECTO1_RAMSITA_PAGEDARRAY_H