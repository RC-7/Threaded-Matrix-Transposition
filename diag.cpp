#include <vector>
#include <stdio.h>

typedef struct threadStruct {
   std::vector<std::vector<int>>*  matrixPtr;
   int id;
   int numberThreads;
} threadStruct;

void* diagTranspose(void* threadStructInput)
{
    threadStruct* ts = (threadStruct*)threadStructInput;
    auto n = (*(ts->matrixPtr)).size();

    for (auto i = ts->id; i < n; i += ts->numberThreads)
    {
        for (auto j = i+1; j < n; ++j)
        {
            (*(ts->matrixPtr))[i][j] = (*(ts->matrixPtr))[i][j] + (*(ts->matrixPtr))[j][i];
            (*(ts->matrixPtr))[j][i] = (*(ts->matrixPtr))[i][j] - (*(ts->matrixPtr))[j][i];
            (*(ts->matrixPtr))[i][j] = (*(ts->matrixPtr))[i][j] - (*(ts->matrixPtr))[j][i];
        }
    }

    pthread_exit(NULL);
}