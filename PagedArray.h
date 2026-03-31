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
    int* data;
    int numero_pagina;
    bool usada;
    int ultimo_acceso;
};



class PagedArray {
private:
    int pageSize; // el tama;o de cada pagina
    int pageCount; //la cantidad de paginas que van a caber en ram
    fstream ramsita_file;// el archivo con los datos binarios
    Page* ram;// el espacio que reservaremos en la memoria, ejemplo, si se piden 4 paginas, entonces el espacio reservado sera 4 paginas
    long long timer; //contador para el lru
    int pageHits;//contador para la cantida de page hits que sucedan
    int pageFaults;//contador para la cantida de page faults que sucedan
    int ultimoUsado();
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