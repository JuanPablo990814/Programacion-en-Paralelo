#include <iostream>

using namespace std;

int main()
{
    // TAMAÑO A=m*n TAMAÑOB=n*p TAMAÑOC=m*p
    int m = 10;
    int n = 10;
    int p = 10;

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

    int matrixC[m][p];

    int i, j, k;

    /*#TAMAÑO A=m*n TAMAÑO B=n*p TAMAÑO C=m*p
    m=3
    n=2
    p=2

    for i in range(3):
      for j in range(2):
        C[i][j]=0
        for k in range(2):
          C[i][j]=C[i][j]+(A[i][k]B[k][j])*/

    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            matrixC[i][j] = 0;
            for (k = 0; k < p; k++)
                matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
        }
    }

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
            cout << matrixC[i][j] << "\t";
        cout << endl;
    }

    return 0;
}
// g++ lab1_punto1.cpp -o ejecutable-punto1
//./ejecutable-punto1
