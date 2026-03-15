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

// esta funcion es capricho mio para hacer un switch, se le da un char* y retorna 1,2 o 3 dependiendo si dice SMALL MEDIUM O LARGE.

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

}
// el argv es la lista de las palabras que se le pasan a la terminal
// va a tener 5 cosas
// argv[0] es el generator
// argv[1] es -size
// argv[2] es <SIZE>, que puede ser
// SMALL: genera un archivo de 256 MB
// MEDIUM: genera un archivo de 512 MB
// LARGE: genera un archivo de 1GB
// argv[3] es -output
// argv[4] es <OUT FILE PATH>
// es la ruta donde va a estar el archivo y le puedes poner el nombre ahi junto con el .bin .dat
// ejemplo de lo que puedes poner ahi:
//C:\Users\yoelr\Desktop\datos.bin

int main(int argc,char* argv[]) {
    srand(time(0));
    fstream ramsita_file;

    if (argc != 5) {
        cout<<"Haz tenido un error a la hora de pasarle los argumentos a generator, recuerda que debe verse asi: generator –size <SIZE> -output <OUTPUT FILE PATH>";
        return 0;
    }
    int numero = convertidor_de_argv2(argv[2]);
    int cantidad;
    switch (numero) {
        // si es un small entonces va a ser de tamanio 256 mb, que son 268435456 bytes, que son 67108864 ints
        // si es un medium entonces va a ser de tamanio 512 mb, que son 536870912 bytes, que son 134217728 ints
        // si es un large entonces va a ser de tamanio 1Gb que son 1073741824 bytes, que son 268435456 ints
            case 1:
            cantidad= 67108864;
            break;
            case 2:
            cantidad= 134217728;
            break;
            case 3:
            cantidad= 268435456;
            break;
            default:
            cout <<"Tamaño no válido"<<endl;
            return 0;
            }
    //se pone el argv[4] como la ruta y nombre, un ejemplo normal seria asi ramsita_file.open("output.dat",ios::out | ios::binary);
    ramsita_file.open(argv[4], ios::out | ios::binary); // el ios::out indica que se le va a escribir datos al archivo y el ios::binary se pone para que se escriban los 4 bytes directamente y que no se trraduscan ni nada
    if (ramsita_file){
    for (int i=0; i<cantidad; i++) {
            int n =rand();
            ramsita_file.write(reinterpret_cast<char*>(&n),sizeof(int));
        }
        ramsita_file.close();
    }
    else{
        cout<<"Hubo un error abriendo el file";


    }




    //ramsita_file.open("output.dat",ios::out | ios::binary);
    //if (ramsita_file) {
     //   ramsita_file.write(reinterpret_cast<char*>(&x), sizeof(int));
     //   ramsita_file.close();
    //}
   // else {
    //    cout<<"Error opening file";
    //}
}


