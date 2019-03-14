#include <stdlib.h>
#include <time.h>
#include <vector>
#include <stdio.h>
#include <memory>
#include "diag.cpp"
#include "block.cpp"
#include <omp.h>

std::vector<std::vector<int>> generateRandom2D(int n)
{

    std::vector<std::vector<int>> randomMatrix(n, std::vector<int>(n, 0));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            randomMatrix[i][j] = rand() % 21;
        }
    }

    return randomMatrix;
}

void print2D(std::vector<std::vector<int>> A)
{
    printf("\n");
    for (auto &value : A)
    {

        for (auto &entry : value)
        {

            printf("%d  \t", entry);
        }

        printf("\n");
    }
}

bool checkDimension(int aLength, int aWidth)
{
    if (aLength == aWidth)
    {
        return true;
    }

    return false;
}

int main()
{
    srand(time(NULL));

    // uncomment when finished testing
    // auto N = {128, 1024, 2048, 4096};
    auto N = {4096};

    for (auto n : N)
    {
        auto matrix = generateRandom2D(n);
        auto matrixPtr = &matrix;
        printf("Initial Matrix \n");
        print2D(matrix);

        if (checkDimension(matrix.size(), matrix[0].size()))
        {
            double begin, end, timeDiff;

            printf("Naive Transpose without Threading \n");
            begin = omp_get_wtime();
            // call transpose
            end = omp_get_wtime();
            double naiveNoTime = end-begin;

            printf("Diagonal Transpose without Threading \n");
            begin = omp_get_wtime();
            // call transpose
            end = omp_get_wtime();
            double diagNoTime = end-begin;

            printf("Block Transpose without Threading \n");
            begin = omp_get_wtime();
            int startX=0;
            int startY=0;
            elementBlockTranspose(matrixPtr, n, startX, startY);
            allBlocksTranspose(matrixPtr, n);
            end = omp_get_wtime();
            double blockNoTime = end-begin;


            printf("Naive Transpose with PThreads \n");
            begin = omp_get_wtime();
            // call transpose
            end = omp_get_wtime();
            double naivePTime = end-begin;

            printf("Diagonal Transpose with PThreads \n");
            begin = omp_get_wtime();
            // call transpose
            end = omp_get_wtime();
            double diagPTime = end-begin;

            printf("Block Transpose with PThreads \n");
            begin = omp_get_wtime();
            // call transpose
            end = omp_get_wtime();
            double blockPTime = end-begin;
            
    
            printf("Naive Transpose with OpenMP \n");
            begin = omp_get_wtime();
            // call transpose
            end = omp_get_wtime();
            double naiveOTime = end-begin;

            printf("Diagonal Transpose with OpenMP \n");
            begin = omp_get_wtime();
            // call transpose
            end = omp_get_wtime();
            double diagOTime = end-begin;

            printf("Block Transpose with OpenMP \n");
            begin = omp_get_wtime();
            // call transpose
            end = omp_get_wtime();
            double blockOTime = end-begin;

            // auto ompDiagTime = (end - begin);
            // print2D(*matrixPtr);
            // printf("Diagonal time: %d \n", ompDiagTime);
            // printf("Block Transpose \n");
            // int startX=0;
            // int startY=0;
            // elementBlockTranspose(matrixPtr,n, startX, startY);
            // allBlocksTranspose(matrixPtr,n);
            // matrix=*matrixPtr;
            // print2D(matrix);
            
            printf("\nNaive with no threading %f s\n", naiveNoTime);
            printf("Diagonal with no threading %f s\n", diagNoTime);
            printf("Block with no threading %f s\n", blockNoTime);

            printf("\nNaive with pthreads %f s\n", naivePTime);
            printf("Diagonal with pthreads %f s\n", diagPTime);
            printf("Block with pthreads %f s\n", blockPTime);

            printf("\nNaive with pthreads %f s\n", naiveOTime);
            printf("Diagonal with pthreads %f s\n", diagOTime);
            printf("Block with pthreads %f s\n", blockOTime);
        }
        else
        {
            printf("Error: matrix needs to be square");
        }
    }

    return 0;
}