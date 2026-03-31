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
        ram[i].numero_pagina=-1;//al inicio se le da /1 como diciendo, esta pagina es un papel en blanco y no representa ninguna pagina aun
        ram[i].usada=false;
        ram[i].ultimo_acceso=0;
    }




    //Logica del destructor, para que no haya memory leak
}
PagedArray :: ~PagedArray() {
    for(int i=0; i<pageCount;i++){
        delete[] ram[i].data;
    }
    delete[] ram;
    ramsita_file.close();

}
//esta funcion lo que hace es retornar el indice de la pagina en ram ultima que se uso
 int PagedArray::ultimoUsado() {
    //esta verificacion es porque el for lo empezamos en ram[1] por lo tanto no verifica si el primero es -1, ya despues de ahi funciona bien
    if (ram[0].numero_pagina==-1) {
        return 0;
    }
    int numeroUltimo = 0;
    int ultimo = ram[0].ultimo_acceso;

    for (int i=1;i<pageCount;i++) {

        if (ram[i].numero_pagina==-1) {
            return i;
        }
        if (ram[i].ultimo_acceso<ultimo) {
            //recordar que ram lo que tiene son indices del 0 al pageCount, no el nombre de las paginas
            ultimo=ram[i].ultimo_acceso;
            numeroUltimo=i;
        }
    }
    return numeroUltimo;

}
int& PagedArray::operator[](int index) {
    int numeroPagina = index/pageSize;
    int lugar = index%pageSize;
    for (int i=0;i<pageCount;i++) {
        if (ram[i].numero_pagina==numeroPagina) {
            ram[i].ultimo_acceso= this->timer;
            this->timer++;
            pageHits++;
            return ram[i].data[lugar];
        }

    }

    //si ese index que pidio el algoritmo no estaba cargado en las paginas en memoria,
    //entonces se hace usa la funcion ultimo usado para saber cual fue la ultima pagina cargada en ram que se uso
    int ultimaPaginaUsada= ultimoUsado();
    pageFaults++;
    ramsita_file.clear();

    //esto es guardar lo que habia en la pagina menos usada y guardarlo en donde estaba en el file normal
    if (ram[ultimaPaginaUsada].numero_pagina !=-1){
    ramsita_file.seekp(pageSize*ram[ultimaPaginaUsada].numero_pagina*sizeof(int), ios::beg);
    ramsita_file.write(reinterpret_cast<char*>(ram[ultimaPaginaUsada].data),pageSize*sizeof(int));
}
    //ahora lo que hacemos es meter la pagina que el algoritmo andaba buscando en la que sacamos de ram
    ramsita_file.seekg(numeroPagina*pageSize*sizeof(int),ios::beg);
    ramsita_file.read(reinterpret_cast<char*>(ram[ultimaPaginaUsada].data),pageSize*sizeof(int));
    ram[ultimaPaginaUsada].numero_pagina=numeroPagina;
    ram[ultimaPaginaUsada].ultimo_acceso=this->timer;
    this->timer++;


    return ram[ultimaPaginaUsada].data[lugar];

}

void PagedArray::estadisticas() {
cout<<"Hubo "<<pageHits<<" pageHits y hubo "<< pageFaults<<" pageFaults en total."<<endl;
}

//Si en algun algorimto no esta pidiendo alguna posicion, loq ue tenemos que hacer es divir por el pageSize, y eso nos daria el numero de apgina en el que se encuentra
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
