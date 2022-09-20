#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <cstdint>
#include <string>
#include <ctime>
#include <string.h>
#include <sstream>
#include <ctime>
#include <pthread.h>

//#define maxSize 1000000000
//#define MAX_THREAD 3 //numero de hilos de cpu
#define maxSize 100000000 // tamaño maximo

// int *matrixA = new int[maxSize]; //[maxSize] = { };
// int *matrixB = new int[maxSize]; //[maxSize] = { };
// int *matrixC = new int[maxSize]; //[maxSize]= { };

using namespace std;
int step_i = 0;
// struct thread_data thread_data_array[maxSize];//[maxSize]

void printMatrix(int *matrix, int M)
{
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < M; j++)
            cout << *matrix++ << "\t";
        cout << endl;
    }
}

//Argumentos de los threads
struct thread_data
{
    //argumentos de la clase multiply, todos punteros
    int *matrixA;
    int *matrixB;
    int *matrixC;
    int *M;
};struct thread_data thread_data_array[50];//TAMAÑO MAXIMO DE THREADS


// This function multiplies

// void *multiply(void *arg)
void *multiply(void *arg)
{
    struct thread_data *my_data;
    my_data = (struct thread_data *)arg;

    int *matrixA = my_data->matrixA;
    int *matrixB = my_data->matrixB;
    int *matrixC = my_data->matrixC;
    int M = *(int *)my_data->M; // de puntero a int?

    int threads_ID = step_i++;

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

int main(int argc, char **argv)
{
    
    int m = 10;
    int n = 10;
    int p = 10;
    // int matrix[3*3] = {3,3,3,3,3,3,3,3,3};
    /*
    int matrix[3][3] = { {3,3,3},
                        {3,3,3},
                        {3,3,3}};
 
    */
    // TAMAÑO A=m*n TAMAÑOB=n*p TAMAÑOC=m*p
    int matrixA[m][n] = {{1, 2, 3, 4, 5, 6, 7, 8, 9, 0},
                         {3, 4, 3, 4, 5, 7, 3, 2, 4, 5},
                         {3, 4, 3, 4, 5, 7, 3, 2, 4, 5},
                         {3, 4, 3, 4, 5, 7, 3, 2, 4, 5},
                         {3, 4, 3, 4, 5, 7, 3, 2, 4, 5},
                         {3, 4, 3, 4, 5, 7, 3, 2, 4, 5},
                         {3, 4, 3, 4, 5, 7, 3, 2, 4, 5},
                         {3, 4, 3, 4, 5, 7, 3, 2, 4, 5},
                         {3, 4, 3, 4, 5, 7, 3, 2, 4, 5},
                         {3, 4, 3, 4, 5, 7, 3, 2, 4, 5}};

    int *pointerA = &matrixA[0][0];

    int matrixB[n][p] = {{1, 2, 3, 4, 5, 6, 7, 8, 9, 0},
                         {1, 2, 3, 4, 5, 6, 7, 8, 9, 0},
                         {1, 2, 3, 4, 5, 6, 7, 8, 9, 0},
                         {1, 2, 3, 4, 5, 6, 7, 8, 9, 0},
                         {1, 2, 3, 4, 5, 6, 7, 8, 9, 0},
                         {1, 2, 3, 4, 5, 6, 7, 8, 9, 0},
                         {1, 2, 3, 4, 5, 6, 7, 8, 9, 0},
                         {1, 2, 3, 4, 5, 6, 7, 8, 9, 0},
                         {1, 2, 3, 4, 5, 6, 7, 8, 9, 0},
                         {3, 4, 3, 4, 5, 7, 3, 2, 4, 5}};

    int *pointerB = &matrixB[0][0];

    int *matrixC = new int[m * p];

    int MAX_THREAD = std::atoi(argv[1]);

    // matrixA = &matrix[0];  // al pasar la matrix se pasa solo lo de la posicion 0
    // matrixB = &matrix1[0]; // lo negativo de esto es que la matrixA y matrixB estan apuntando a la variable matrix

    // matrixA = &matrix[0][0];//dentro no va el tamaño de la matrix si no 0
    // matrixB = &matrix[0][0];

    clock_t cl = clock();

    // declaring four threads
    pthread_t threads[MAX_THREAD];

    // Creating four threads, each evaluating its own part
    for (int bloq = 0; bloq < m; bloq += MAX_THREAD)
    {
        // cout<<"bloq:"<<bloq<<endl;

        for (int i = 0; i < MAX_THREAD; i++)
        {
            thread_data_array[i].matrixA = pointerA;
            thread_data_array[i].matrixB = pointerB;
            thread_data_array[i].matrixC = &matrixC[0];
            thread_data_array[i].M = &m;
            pthread_create(&threads[i], NULL, multiply, (void *) &thread_data_array[i]);
        }
        for (int i = 0; i < MAX_THREAD; i++)
            pthread_join(threads[i], NULL);
    }

    // cout <<"A is matrix:"<<endl;
    // printMatrix(&matrixA[0],M);
    // cout<<endl;

    // cout <<"B is matrix:"<<endl;
    // printMatrix(&matrixB[0],M);

    cout << "Result matrix is C: \n";
    printMatrix(&matrixC[0], m);

    cout << "Time: " << (clock() - cl) * 1000 / CLOCKS_PER_SEC << "ms" << endl;

    return 0;
}
/*
g++ -pthread -o ejecutable-punto1 lab2_punto1.cpp
./ejecutable-punto1 CANTIDADDETHREADS
*/