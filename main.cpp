#include <stdlib.h>
#include <time.h>
#include <vector>
#include <stdio.h>
#include <memory>
#include "diag.cpp"

#define THREAD_NUM 4

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

void print2D(std::vector<std::vector<int>> *matrixPtr)
{
    printf("\n");
    for (auto &value : (*matrixPtr))
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
    auto N = {10};

    for (auto n : N)
    {
        auto matrix = generateRandom2D(n);
        auto matrixPtr = &matrix;
        printf("Initial Matrix \n");
        print2D(matrixPtr);

        //perform each of the operations and use print2D to print the output
        // I put the check dimension function above so we can just call it before doing anything else

        if (checkDimension(matrix.size(), matrix[0].size()))
        {
            //DIAGONAL
            pthread_t threads[THREAD_NUM];

            // setup threads
            std::vector<threadStruct> structVec;
            for (int i = 0; i < 4; i++)
            {
                structVec.push_back(threadStruct());
                structVec[i].matrixPtr = matrixPtr;
                structVec[i].numberThreads = THREAD_NUM;
                structVec[i].id = i;
            }

            // create threads and do diagonal transpose
            for (int i = 0; i < THREAD_NUM; ++i)
            {
                pthread_create(&threads[i], NULL, diagTranspose, &structVec[i]);
            }

            // join all threads
            for (int j = 0; j < THREAD_NUM; ++j)
                pthread_join(threads[j], NULL);

            printf("Diagonal Transpose \n");
            print2D(matrixPtr);
        }
        else
        {
            printf("Error: matrix needs to be square");
        }
    }

    return 0;
}