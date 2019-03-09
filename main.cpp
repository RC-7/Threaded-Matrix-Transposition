#include <stdlib.h>
#include <time.h>
#include <vector>
#include <stdio.h>
#include <memory>
#include "diag.cpp"
#include "block.cpp"
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
    auto N = {16};

    for (auto n : N)
    {
         auto matrix = generateRandom2D(n);
       // auto matrixPtr = std::make_shared<std::vector<std::vector<int>>>(matrix);
         auto matrixPtr=&matrix;
        printf("Initial Matrix \n");
        print2D(matrixPtr);

        //perform each of the operations and use print2D to print the output
        // I put the check dimension function above so we can just call it before doing anything else
        // we might have to use pointers to move our matrices around since it asks for in place transposition and passing by value might cause memory issues

        if (checkDimension(matrix.size(), matrix[0].size()))
        {

            //Block
            pthread_t threads[THREAD_NUM];

            // setup threads
            std::vector<threadStructBlock> structVecBlock;
            for (int i = 0; i < 4; i++)
            {
                structVecBlock.push_back(threadStructBlock());
                structVecBlock[i].matrixPtr = matrixPtr;
                structVecBlock[i].numberThreads = THREAD_NUM;
                structVecBlock[i].id = i;
                structVecBlock[i].subBlockSize=n/2;
                structVecBlock[i].startX=0;
                structVecBlock[i].startY=0;
            }


            for (int i=0;i<2;i++)//thread 0: 0 0; thread 1: 0 n/2
            {
                structVecBlock[i].startX=0;
                structVecBlock[i].startY=i*n/2;
            }

            for (int i=2;i<4;i++)
            {
                structVecBlock[i].startX=n/2;
                structVecBlock[i].startY=(i-2)*n/2;
            }
          

            //First Transposition
            for (int i = 0; i < THREAD_NUM; ++i)
            {
                pthread_create(&threads[i], NULL, elementBlockTransposeThread, &structVecBlock[i]);
            }
           
            for (int j = 0; j < THREAD_NUM; ++j)
                pthread_join(threads[j], NULL);

            //matrix=*matrixPtr;
           //allBlocksTranspose(matrixPtr,n);
            
            for (int i = 0; i < THREAD_NUM; ++i)
            {
                pthread_create(&threads[i], NULL,lastTranspose, &structVecBlock[i]);
            }

            for (int j = 0; j < THREAD_NUM; ++j)
                pthread_join(threads[j], NULL);

             printf("\nTransposed Matrix \n");
            print2D(matrixPtr);


        }
        else
        {
            printf("Error: matrix needs to be square");
        }
    }

    return 0;
}