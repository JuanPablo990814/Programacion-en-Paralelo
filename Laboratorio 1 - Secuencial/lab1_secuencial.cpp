#include <iostream> 
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <time.h>// for clock_t, clock(), CLOCKS_PER_SEC
#include <unistd.h> //for sleep()

#include <cstdint>
#include <string>
#include <ctime>
#include <string.h>
#include <sstream> 

#define maxSize 100000000
using namespace std; 


void loadMatrix(string fileName, int *matrix)
{
    ifstream infile;
    infile.open(fileName);
    string line, value="";
    if (infile.is_open()) 
    {
        while (getline(infile,line))
        {
            istringstream iss(line);
            while (getline(iss, value, '\t'))
            {
                *matrix++=std::atoi(value.c_str()); //atoi convierte los valores a enteros
            }
        }
    }
    else{
        cout<<"No se puede abrir la matrix";
    }
} 

void printMatrix(int *matrix, int M)
{
    for (int i=0; i<M; i++)
    {
        for (int j=0; j<M; j++)
            cout<<*matrix++<<"\t";
         cout<<endl;
    }
}


// This function multiplies  
void multiply(int *matrixA, int *matrixC, int M) 
{ 
    
    int i, j, k; 
    for (i = 0; i < M; i++) 
    { 
        for (j = 0; j < M; j++) 
        { 
            matrixC[i*M+j] = 0; 
            for (k = 0; k < M; k++) 
                matrixC[i*M+j] += matrixA[i*M+k] * matrixA[k*M+j]; 
        } 
    }
    
}
void printTxt(int *matrix, int M,string carpeta)
{
	//imprimir en archivo de texto
	string num = to_string(M);
	//cambiar dependiendo de la ubicacion
    string ubication = (carpeta+"/resultadoMatriz_M"+num+".txt");
    ofstream file;
    file.open(ubication);
    if (file.is_open()) 
    {
    	for (int i=0; i<M; i++)
    	{
        	for (int j=0; j<M; j++)
            file<<*matrix++<<"\t";
         	file<<endl;
    	}

        //file << "Si funciona";
        file.close();
	cout<<"\nResultado guardado como : resultadoMatriz_M"+num+".txt en el directorio:"+carpeta<<endl;
    }
    else{
        cout<<"\nNo se puede abrir la ubicacion para guardar la matrix, revisar en el codigo la ubicacion";
    }
} 
// Driver Code 
int main(int argc, char** argv) 
{
    string fileName=argv[1];
    int M =std::atoi(argv[2]);
    string carpeta=argv[3];
    
    int *matrixA = new int[maxSize];//[maxSize] = { };
    int *matrixC =  new int[maxSize];//[maxSize]= { };
    
    double time_spent = 0.0;
    clock_t begin = clock();
    loadMatrix(fileName, matrixA);//cargar matriz
    sleep(3);
    clock_t end = clock();
    time_spent += (double)(end - begin)/CLOCKS_PER_SEC;
    printf("\nTiempo de carga de la matriz:%f seconds\n",time_spent);

    //cout << "Matrix value A: \n";
    //printMatrix(&matrixA[0], M);
    time_spent = 0.0;
    begin = clock();
    multiply(matrixA, matrixC, M);//multiplicacion de matriz
    sleep(3);
    end = clock();
    time_spent += (double)(end - begin)/CLOCKS_PER_SEC;
    printf("\nTiempo de multiplicacion matrices:%f seconds\n",time_spent);
    
    //cout << "\nResult matrix is C: \n";
    //printMatrix(&matrixC[0], M);

    time_spent = 0.0;
    begin = clock();
    printTxt(&matrixC[0], M,carpeta);//imprimir matriz en archivo de texto
    sleep(3);
    end = clock();
    time_spent += (double)(end - begin)/CLOCKS_PER_SEC;
    printf("\nImpresion de la matriz en un archivo:%f seconds\n",time_spent);
    
    return 0; 
} 
/*
g++ -o ejecutable secuencial.cpp
time ./ejecutable MatrizA TamañoM ubicacionResultado
time ./ejecutable
MatrizA: Se refiere a la ubicación exacta del txt que contiene la matriz.
TamañoM: Tamaño de la matriz a operar.
ubicacionResultado: Carpeta donde se guardara el resultado de la multiplicación.
*/

//g++ -pthread lab1_secuencial.cpp -o lab1ejecutable
//time ./lab1ejecutable /home/kali/Desktop/m5000.txt 5000 /home/kali/Desktop/
