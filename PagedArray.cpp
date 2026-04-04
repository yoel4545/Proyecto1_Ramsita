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
#include <cstring>
using namespace std;
#include "PagedArray.h"




PagedArray::PagedArray(string nombreArchivo, int pageSize, int pageCount ) {
    // tenemos estas variables para contabilizar cada vez que hay hits o faults y darnos la cantidad de paginas que caberan en memoria
    // y el tama;o de cada pagina
    this->pageHits=0;
    this->pageFaults=0;
    this->pageSize =pageSize;
    this->pageCount=pageCount;
    this->timer = 0;

    this->ramsita_file.open(nombreArchivo,ios::in|ios::out|ios::binary);


    ramsita_file.seekg(0,ios::end);
    long long  tamañoarchivo = ramsita_file.tellg();
    cantidadElementos = tamañoarchivo/sizeof(int);
    ramsita_file.seekg(0,ios::beg);




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
        ram[i].ultimo_acceso=0;
    }




    //Logica del destructor, para que no haya memory leak
}
PagedArray::~PagedArray() {
    // ESTO ES LO QUE GUARDA LOS CAMBIOS FINALES

    for (int i = 0; i < pageCount; i++) {
        if (ram[i].numero_pagina != -1) {
            int enPagina = elementosEnPagina(ram[i].numero_pagina);
            ramsita_file.clear();
            ramsita_file.seekp(pageSize * ram[i].numero_pagina * sizeof(int), ios::beg);
            ramsita_file.write(reinterpret_cast<char*>(ram[i].data), enPagina * sizeof(int));
        }
    }


    for(int i=0; i<pageCount; i++) {
        delete[] ram[i].data;
    }
    delete[] ram;
    ramsita_file.close();
}


int PagedArray::elementosEnPagina(int numeroPagina) const {
    int inicial = numeroPagina* pageSize;
    int final = inicial + pageSize -1; //-1 porque es el ultimo elemento antes de que pase a otra pagina
    if (final >= cantidadElementos) {
        return cantidadElementos-inicial; //esto es para si es la pagina es la ultima, entonces que al inicio de esa pagina se le reste el tama;o de todo, entonces da el tama;o de esa pagina final
    }
    return pageSize; //si no es la pagina final, todas tienen el mismo tama;o que es page size
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
        if (ram[i].ultimo_acceso<ultimo) {// se busca el menor .ultimo_acceso que seria el ultimo que se ha usado
            //recordar que ram lo que tiene son indices del 0 al pageCount, no el nombre de las paginas
            ultimo=ram[i].ultimo_acceso;//
            numeroUltimo=i;
        }
    }
    return numeroUltimo;

}


int& PagedArray::operator[](int index) {
    int numeroPagina = index/pageSize; // aqui agarramos el indice que no esten dando y nos tira la pagina en la que esta ese indice
    int lugar = index%pageSize; // aqui agarramos el indice y nos tira la posicion
    // este es el pagehit, cuando resulta que lo que se estaba buscando si estaba cargado en las paginas de ram, si no lo encuentra entoces se sigue el codigo de abajo
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
    // si el codigo llego hasta aqui entonces significa q es un pagefault tonces se suma 1
    pageFaults++;
    //esto es para evitar errores al buscar
    ramsita_file.clear();

    //esto es guardar lo que habia en la pagina menos usada y guardarlo en donde estaba en el file normal
    if (ram[ultimaPaginaUsada].numero_pagina !=-1){ //se hace esta verificacion porque si es -1 entonces no tiene nada, entonces no es necesario meter nada en disco
        int enPaginaV = elementosEnPagina(ram[ultimaPaginaUsada].numero_pagina);
        ramsita_file.clear();
    ramsita_file.seekp((long long)pageSize*ram[ultimaPaginaUsada].numero_pagina*sizeof(int), ios::beg);// se busca el lugar donde inician los datos de esa pagina
    ramsita_file.write(reinterpret_cast<char*>(ram[ultimaPaginaUsada].data),enPaginaV*sizeof(int));//se escriben los datos de esa pagina
}



    //ahora lo que hacemos es meter la pagina que el algoritmo andaba buscando en la que sacamos de ram
    int enPaginaN = elementosEnPagina((numeroPagina));
    ramsita_file.clear();
    ramsita_file.seekg((long long )numeroPagina*pageSize*sizeof(int),ios::beg);//se busca la pagina saltando desde el inicio con, size of int, que es 4, * page size, que se define y el numero de pagina para saber cuantos bloques saltar
    ramsita_file.read(reinterpret_cast<char*>(ram[ultimaPaginaUsada].data),enPaginaN*sizeof(int));//se lee y se mete en la pagina en ram
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
        cout<<dato_leido<<endl; mmm
    }
*/
