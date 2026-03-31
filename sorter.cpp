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
#include "algoritmos_ordenamiento.h"
#include "PagedArray.h"
using namespace std;
/*
int convertidor_de_argv2(string SIZE) {
    if (SIZE=="SMALL") {
        return 1;
    }
    else if (SIZE=="MEDIUM") {
        return 2;
    }
    else if (SIZE=="LARGE") {
        return 3;
    }
    else {
        cout<<"Error en el convertidor de argv[2]";
        return 0;
    }
*/
int convertidor_de_argv6(string ALG) {
    if (ALG=="quickSort"){return 1;}
    if (ALG=="bubbleSort"){return 2;}
    if (ALG=="selectionSort"){return 3;}
    if (ALG=="insertionSort"){return 4;}
    if (ALG=="shellSort"){return 5;}
    else {
        cout<<"Error en el convertidor de argv[6]";
        return 0;
    }

}


/*
 *
}

argv[0] es sorter
argv[1] es -input
argv[2] es <INPUT FILE PATH> Es la ruta del archivo que queremos ordenar
argv[3] es -output
argv[4] es <OUTPUT FILE PATH>, es donde queremos que se nos generen los archivos ordenasdos y su nombre
argv[5] es -alg
argv[6] es <ALGORITMO> Que es el tipo de algoritmo con el que queremos ordenar el archivo
ejemplos:
quickSort
bubbleSort
selectionSort
insertionSort
shellSort
argv[7] es -pageSize
argv[8] es <Page-Size>, que es la cantidad de enteros que va a tener cada pagina
argv[9] es -pageCount
argv[10] es <PAGE-COUNT> que es la cantidad maxima de paginas que va a haber en memoria

*/

int main(int argc,char* argv[]) {
    fstream original; // se abre en ifstream porque solo se va a leer para copiarlo en la copia
    fstream copia; // se abre en offstream ya que lo vamos a usar para escribirle
    const int tamañoIntermedio = 4096;
    if (argc != 11) {
        cout<<"Haz tenido un error a la hora de pasarle los argumentos a generator, recuerda que debe verse asi:"<<endl << "sorter –input <INPUT FILE PATH> -output <OUTPUT FILE PATH> -alg <ALGORITMO> -pageSize <PAGE-SIZE> -pageCount <PAGE-COUNT>";
        return 0;
    }

    //abrimos los dos archivos
    original.open(argv[2],ios::in|ios::binary); // no se especifica el ios::in ya que por defecto es in
    copia.open(argv[4],ios::out| ios::binary); //tampoco se especifica el ios::out

    if (original && copia) {  // si se abren los dos correctamente, copiamos lo que esta en el original a la copia
    char intermedio[tamañoIntermedio];
        //cada ves que entra al while mete los datos en el intermedio, si logra meterlos todos entonces sigue en el while, cuando ya no los meta todos, es un false, entonces sale del while
        while (original.read(intermedio,tamañoIntermedio)) {
            copia.write(intermedio,tamañoIntermedio);
        }
        if (original.gcount()>0) { //g.count lo que hace es darnos la cantidad de bytes que se leyeron en el ultimo read
            copia.write(intermedio,original.gcount());
        }
        original.close();
        copia.close();
    }
    int pageSize = stoi(argv[8]);
    int pageCount = stoi(argv[10]);
    copia.open(argv[4],ios::in| ios:: binary);
    copia.seekg(0,ios::end);

    int tamaño = copia.tellg()/sizeof(int);
    copia.close();
    PagedArray arreglo(argv[4],pageSize,pageCount);
    clock_t inicio = clock();
    int algoritmo = convertidor_de_argv6(argv[6]);
    switch (algoritmo) {
        case 1: quickSort(arreglo,0,tamaño-1);
            break;
        case 2: bubbleSort(arreglo,tamaño);
            break;
        case 3: selectionSort(arreglo,tamaño);
            break;
        case 4: insertionSort(arreglo,tamaño);
            break;
        case 5: shellSort(arreglo, tamaño);
            break;
    }
    clock_t fin= clock();
    double tiempo = double(fin-inicio)/CLOCKS_PER_SEC;
    cout<< "El algoritmo ustilizado fue: "<< argv[6]<<endl;
    cout<<"El algoritmo duro " << tiempo<<" segundos en ordenar el archivo."<<endl;
    arreglo.estadisticas();

    ifstream copiaLector;
    ofstream legible;

    copiaLector.open(argv[4], ios::binary);

    string nombreLegible = string(argv[4]);
    nombreLegible = nombreLegible.substr(0, nombreLegible.find_last_of(".")) + ".txt";

    legible.open(nombreLegible);
/*
    char intermedio2[tamañoIntermedio];
    if (copiaLector && legible) {
        while (copiaLector.read(interme))
        */



    }






