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
void multiply(int *matrixA, int *matrixB, int *matrixC, int M) 
{ 
    
    int i, j, k; 
    for (i = 0; i < M; i++) 
    { 
        for (j = 0; j < M; j++) 
        { 
            matrixC[i*M+j] = 0; 
            for (k = 0; k < M; k++) 
                matrixC[i*M+j] += matrixA[i*M+k] * matrixB[k*M+j]; 
        } 
    }
    
}

int main(int argc, char** argv) 
{
    string fileName=argv[1];
    string fileName2=argv[2];
    int M =std::atoi(argv[3]);
    
    int *matrixA = new int[maxSize];//[maxSize] = { };
    int *matrixB =  new int[maxSize];//[maxSize]= { };
    int *matrixC =  new int[maxSize];//[maxSize]= { };
    
    loadMatrix(fileName, matrixA);
    loadMatrix(fileName2, matrixB);

    cout << "Matrix value A: \n";
    printMatrix(&matrixA[0], M);

    cout << "\nMatrix value B: \n";
    printMatrix(&matrixB[0], M);

    multiply(matrixA, matrixB, matrixC, M);
  
    cout << "\nResult matrix is C: \n";
    printMatrix(&matrixC[0], M);
    
  
    return 0; 
} 

//g++ lab1_punto2.cpp -o ejecutable-punto2
//./ejecutable-punto2 matriz1 matriz2 tamañomatriz
