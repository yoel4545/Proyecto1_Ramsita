//
// Created by yoelr on 4/4/2026.
//

#include <iostream>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <string>
#include <cstring>

using namespace std;

void quickSort(int *array, int low, int high)
{
    int i = low;
    int j = high;
    int pivot = array[(i + j) / 2];
    int temp;

    while (i <= j)
    {
        while (array[i] < pivot)
            i++;
        while (array[j] > pivot)
            j--;
        if (i <= j)
        {
            temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            i++;
            j--;
        }
    }
    if (j > low)
        quickSort(array, low, j);
    if (i < high)
        quickSort(array, i, high);
}


void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {  
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}




void selectionSort(int *array, int n)
{
    int temp;
    int min;

    for (int i = 0; i < n; ++i)
    {
        min = i;
        for (int j = i + 1; j < n; ++j)
        {
            if (array[j] < array[min])
                min = j;
        }
        if (min != i)
        {
            temp = array[i];
            array[i] = array[min];
            array[min] = temp;
        }
    }
}

void insertionSort(int* arr, int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;


        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int shellSort(int arr[], int n)
{
    // Start with a big gap, then reduce the gap
    for (int gap = n/2; gap > 0; gap /= 2)
    {
        // Do a gapped insertion sort for this gap size.
        // The first gap elements a[0..gap-1] are already in gapped order
        // keep adding one more element until the entire array is
        // gap sorted
        for (int i = gap; i < n; i += 1)
        {
            // add a[i] to the elements that have been gap sorted
            // save a[i] in temp and make a hole at position i
            int temp = arr[i];

            // shift earlier gap-sorted elements up until the correct
            // location for a[i] is found
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];

            // put temp (the original a[i]) in its correct location
            arr[j] = temp;
        }
    }
    return 0;
}

int main(int argc, char* argv[]) {

    if (argc != 3) {
        cout << "Ejemplo: " << argv[0] << " quickSort mini256.bin" << endl;
        return 1;
    }

    string algoritmo = argv[1];
    string archivo = argv[2];

    ifstream file(archivo, ios::binary | ios::ate);

    if (file) {
        long long size = file.tellg();
        int n = size / sizeof(int);
        file.seekg(0, ios::beg);
        //se meten todos los numeros en datos que tiene el tama;o necesario gracias a n
        int* datos = new int[n];
        file.read(reinterpret_cast<char*>(datos), size);
        file.close();

        cout << "Archivo: " << archivo << endl;
        cout << "Algoritmo: " << algoritmo << endl;
        cout << "Ordenando " << n << " elementos..." << endl;

        clock_t inicio = clock();

        // se selecciona el algoritmo dado y se empieza el tiempo
        if (algoritmo == "quickSort") {
            quickSort(datos, 0, n - 1);
        }
        else if (algoritmo == "bubbleSort") {
            bubbleSort(datos, n);
        }
        else if (algoritmo == "selectionSort") {
            selectionSort(datos, n);
        }
        else if (algoritmo == "insertionSort") {
            insertionSort(datos, n);
        }
        else if (algoritmo == "shellSort") {
            shellSort(datos, n);
        }
        else {

            cout << "Usa: quick, bubble, selection, insertion o shell" << endl;
            delete[] datos;
            return 1;
        }

        clock_t fin = clock();

        double tiempoTotal = (double)(fin - inicio) / CLOCKS_PER_SEC;

        cout << "Tiempo total: " << tiempoTotal << " segundos" << endl;
        cout << "Tiempo por elemento: " << (tiempoTotal / n) << " segundos por entero" << endl;

        delete[] datos;
    } else {
        cout << "No se pudo abrir el archivo: " << archivo << endl;
        return 1;
    }

    return 0;
}