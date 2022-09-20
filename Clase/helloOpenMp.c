#include <iostream>
#include <omp.h>

using namespace std;
int main()
{
    #pragma omp parallel 
    {
        cout<<"Hello from the thread# "<<omp_get_thread_num()<<"\n";
    }
    return 0;
}

/*

g++ -fopenmp helloOpenMp.c -o ejecutablehelloOpenMp
./ejecutablehelloOpenMp 

modificar uso de threads desde afuera del ejecutable
export OMP_NUM_THREADS=6 

export OMP_NUM_THREADS=6
./ejecutablehelloOpenMp 

*/