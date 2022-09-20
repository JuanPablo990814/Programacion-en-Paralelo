#include <iostream>
#include <omp.h>

#define cpus 10

using namespace std;
int main()
{
    #pragma omp parallel num_threads(cpus)
    {
        cout<<"Hello from the thread# "<<omp_get_thread_num()<<"\n";
    }
    return 0;
}

/*

g++ -fopenmp helloOpenMpCpu.c -o ejecutablehelloOpenMpCpu
./ejecutablehelloOpenMpCpu

*/