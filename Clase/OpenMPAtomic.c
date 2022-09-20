#include <iostream>
#include <omp.h>
using namespace std;
#define CPUs 10
int main() 
{
   int count = 0;
   #pragma omp parallel num_threads(CPUs)
   {
      #pragma omp atomic //para que solo un thread pueda usar count a la vez
      count++;
   }
   cout<<"Number of threads: "<< count<<endl;
}

/*
g++ -fopenmp OpenMPAtomic.c -o ejecutableOpenMPAtomic
./ejecutableOpenMPAtomic 
*/