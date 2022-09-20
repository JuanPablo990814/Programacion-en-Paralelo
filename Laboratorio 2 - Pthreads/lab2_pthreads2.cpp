#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <cstdint>
#include <fstream>
#include <string>
#include <ctime>
#include <string.h>
#include <sstream>
#include <ctime>

//#define maxSize 1000000000
//#define MAX_THREAD 3 //numero de hilos de cpu
#define maxSize 100000000

using namespace std;

int *matrixA = new int[maxSize]; //[maxSize] = { };
int *matrixB = new int[maxSize]; //[maxSize] = { };
int *matrixC = new int[maxSize]; //[maxSize]= { };
int step_i = 0;

void loadMatrix(string fileName, int *matrix)
{
    ifstream infile;
    infile.open(fileName);
    string line, value = "";
    int i = 0;
    if (infile.is_open())
    {
        while (getline(infile, line))
        {
            istringstream iss(line);
            while (getline(iss, value, '\t'))
            {
                *matrix++ = std::atoi(value.c_str());
            }
        }
    }
    else
    {
        cout << "no se puede abrir el archivo que contiene la matriz" << endl;
    }
}

void printMatrix(int *matrix, int M)
{
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < M; j++)
            cout << *matrix++ << "\t";
        cout << endl;
    }
}

// This function multiplies
void *multiply(void *arg)
{
    int threads_ID = step_i++;
    int M = *(int *)arg;
    if (threads_ID < M)
    {
        for (int j = 0; j < M; j++)
        {
            matrixC[threads_ID * M + j] = 0;
            for (int k = 0; k < M; k++)
            {
                matrixC[threads_ID * M + j] += matrixA[threads_ID * M + k] * matrixB[k * M + j];
            }
        }
    }
    return 0;
}

void printTxt(int *matrix, int M, string carpeta)
{
    // imprimir en archivo de texto
    string num = to_string(M);
    // string ubication = ("/home/juan/Escritorio/resultM_"+num+".txt");
    string ubication = (carpeta + "/resultadoMatriz_M" + num + ".txt");
    ofstream file;
    file.open(ubication);
    if (file.is_open())
    {
        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < M; j++)
                file << *matrix++ << "\t";
            file << endl;
        }
        file.close();
        cout << "Resultado Impreso como : resultadoMatriz_M" + num + ".txt en el directorio:" + carpeta << endl;
    }
    else
    {
        cout << "No se puede abrir la matrix";
    }
}

int main(int argc, char **argv)
{
    string fileName = argv[1];
    string fileName2 = argv[2];
    int M = std::atoi(argv[3]);
    int MAX_THREAD = std::atoi(argv[4]);
    string carpeta = argv[5];

    clock_t cl = clock();

    loadMatrix(fileName, matrixA);
    loadMatrix(fileName2, matrixB);

    // declaring four threads
    pthread_t threads[MAX_THREAD];
    // Creating four threads, each evaluating its own part
    for (int bloq = 0; bloq < M; bloq += MAX_THREAD)
    {
        // cout<<"bloq:"<<bloq<<endl;
        for (int i = 0; i < MAX_THREAD; i++)
            pthread_create(&threads[i], NULL, multiply, &M);
        for (int i = 0; i < MAX_THREAD; i++)
            pthread_join(threads[i], NULL);
    }

    // cout <<"A is matrix:"<<endl;
    // printMatrix(&matrixA[0],M);
    // cout<<endl;

    // cout <<"B is matrix:"<<endl;
    // printMatrix(&matrixB[0],M);

    // cout << "Result matrix is C: \n";
    // printMatrix(&matrixC[0], M);

    printTxt(&matrixC[0], M, carpeta);
    // cout << "Compilado. \n";

    cout << "Time: " << (clock() - cl) * 1000 / CLOCKS_PER_SEC << "ms" << endl;

    return 0;
}
/*
g++ -pthread -o ejecutable pthreads.cpp
time ./ejecutable MatrizA MatrizB TamañoM NumHilos ubicacionResultado
time ./ejecutable
MatrizA y B: Se refiere a la ubicación exacta del txt que contiene la matriz.
TamañoM: Tamaño de la matriz a operar.
NumHilos: Cantidad de hilos que el programa va a utilizar.
ubicacionResultado: Carpeta donde se guardara el resultado de la multiplicación.