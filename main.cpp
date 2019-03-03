#include <stdlib.h>
#include <time.h>
#include <vector>
#include <stdio.h>
#include <memory>
#include "diag.cpp"

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

    auto N = {128, 1024, 2048, 4096};

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
            diagTranspose(matrixPtr);
        }
        else
        {
            printf("Error: matrix needs to be square");
        }
    }

    return 0;
}