#include <iostream>
#include <omp.h>
using namespace std;
int main (int argc, char *argv[]) 
{

  int th_id, nthreads;
  #pragma omp parallel private(th_id)
  {
    th_id = omp_get_thread_num();
    cout<<"Hello World from thread"<<th_id<<endl;
    
    #pragma omp barrier        
    if ( th_id == 0 ) 
    {
      nthreads = omp_get_num_threads();
      cout<<"There are threads: "<<nthreads<<endl;
    }
  }
}

/*

g++ -fopenmp OpenMPBarrier.c -o ejecutableOpenMpBarrier
./ejecutableOpenMPBarrier

*/