#include <stdlib.h>
#include <time.h>
#include <vector>
#include <stdio.h>
#include <memory>
#include <pthread.h>
#include "diag.cpp"



typedef struct threadStruct {
   std::vector<std::vector<int>>*  A;
   std::vector<std::vector<int>>*  B;
   std::vector<std::vector<int>>*  C;
   int id;
   int numberThreads;

} threadStruct;


void *transposeMatrix(void *threadStructInput){


    auto *ts = (threadStruct*)threadStructInput;
    auto A=ts->A;
    auto C=ts->C;


    for (int i = ts->id; i < (*A).size(); i += ts->numberThreads){
        for (int j = 0; j < (*A).size(); j++){
            (*C)[j][i]=(*A)[i][j];
        }
    }

    pthread_exit(NULL);
}



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
    auto N = {10};

    for (auto n : N)
    {
        const auto matrix = generateRandom2D(n);
        auto matrixPtr = std::make_shared<std::vector<std::vector<int>>>(matrix);
        printf("Initial Matrix \n");
        print2D(matrix);

        //perform each of the operations and use print2D to print the output
        // I put the check dimension function above so we can just call it before doing anything else
        // we might have to use pointers to move our matrices around since it asks for in place transposition and passing by value might cause memory issues

        if (checkDimension(matrix.size(), matrix[0].size()))
        {
            printf("Diagonal Transpose \n");
            print2D(diagTranspose(matrixPtr));
        }
        else
        {
            printf("Error: matrix needs to be square");
        }
    }


    // Rashaad basic parallel transpose below
    std::vector<threadStruct> structVec;
    // threadStruct thread_struct;
    auto A=generateRandom2D(8);
    auto B=generateRandom2D(8);
    auto C=generateRandom2D(8);

    for (int i=0;i<4;i++){

        structVec.push_back(threadStruct());
        structVec[i].A=&A;
        structVec[i].B=&B;
        structVec[i].C=&C;

    }



     pthread_t thread[4];
  // int tid[4];
    for (int i = 0; i < 4; i++) {
            structVec[i].id = i;
            structVec[i].numberThreads=4;
            pthread_create(&thread[i], NULL, transposeMatrix, &structVec[i]);
    }
   
    for (int i = 0; i < 4; i++){
        pthread_join(thread[i], NULL);
    }

    print2D(A);
    print2D(C);

    return 0;
}