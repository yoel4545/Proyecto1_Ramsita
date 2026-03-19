//
// Created by yoelr on 12/3/2026.
//
#include <iostream> //la de siempre
#include <cmath> // matematicas
#include <iomanip>// para los cout
#include <fstream> //para los file
#include <string> //para poder usar string en el convertidor
#include <ctime> //para time
#include <cstdlib> //para rand y srand
using namespace std;
#include "PagedArray.h"




PagedArray::PagedArray(string nombreArchivo, int pageSize, int pageCount ) {
    // tenemos estas variables para contabilizar cada vez que hay hits o faults y darnos la cantidad de paginas que caberan en memoria
    // y el tama;o de cada pagina
    this->pageHits=0;
    this->pageFaults=0;
    this->pageSize =pageSize;
    this->pageCount=pageCount;

    this->ramsita_file.open(nombreArchivo,ios::in|ios::out|ios::binary);

/*
 * en esta parte es asi, tenemos
 *  ram, que es el puntero principal
 *  que apunta al inicio de la fila de pages en memoria
 *  ram[i], es cada pagina de esa fila de memoria
 *  ram[i].data es otro puntero, que vive dentro de cada una de esas paginas
 *  al hacer new int[pageSize] estamos haciendo que haya un puntero apuntando a un array de enteros del tama;o de pageSize
 *  ejemplo, ram[1].data=new int[512]; esto lo que hace es hacernos un espacio de 2048 bytes en memoria, el resto de usada y ultimo acceso es para
 *  la logica del LRU y saber cual cambiar
 */
    ram = new Page[pageCount];
    for (int i=0;i<pageCount;i++) {
        ram[i].data=new int[pageSize];
        ram[i].numero_pagina=-1;
        ram[i].usada=false;
        ram[i].ultimo_acceso=0;
    }




    //Logica del destructor, para que no haya memory leak
    void Destructor() {
        for (int i=1; i<pageCount;i++ ) {

        }
    }


}


/*
fstream ramsita_file;
int x[5]={10,20,30,40,50};
ramsita_file.open("ramsita.txt", ios::out| ios::binary);
if (ramsita_file) {
    for (int i=0; i<5; i++) {
        ramsita_file.write(reinterpret_cast<char*>(&x[i]),sizeof(x[i]));
    }
    ramsita_file.close();
    ramsita_file.open("ramsita.txt", ios::in|ios::out | ios::binary);

    if (ramsita_file) {
        int numero_leido;
        ramsita_file.seekg(3*sizeof(int),ios::beg);
        ramsita_file.read(reinterpret_cast<char*>(&numero_leido),sizeof(int));
        cout<<numero_leido<<endl;
        ramsita_file.close();
    }
    ramsita_file.open("ramsita.txt", ios::out | ios::in | ios::binary);
    if (ramsita_file) {
        int nuevo_dato=77;
        ramsita_file.seekp(1*sizeof(int),ios::beg);
        ramsita_file.write(reinterpret_cast<char*>(&nuevo_dato),sizeof(int));
        int dato_leido;
        ramsita_file.seekg(1*sizeof(int),ios::beg);
        ramsita_file.read(reinterpret_cast<char*>(&dato_leido),sizeof(int));
        cout<<dato_leido<<endl;
    }
*/
