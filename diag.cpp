#include <vector>
#include <memory>
#include <omp.h>
#include <stdio.h>
double omp_get_wtime(void);
// omp_set_num_threads(8);

// change to this when pointer works
// void diagTranspose(std::shared_ptr<std::vector<std::vector<int>>> (*matrixPtr)Ptr)
void diagTranspose(std::shared_ptr<std::vector<std::vector<int>>> matrixPtr)
{
    // double omp_get_wtime(void);
    // transpose by only accessing (*matrixPtr) elements with dereference operator to avoid copy
    // initially just dereferencing to check if it works
    auto n = (*matrixPtr).size();

    // auto begin = omp_get_wtime();
    #pragma omp for
    for (auto i = 0; i < n; ++i)
    {
        // #pragma omp parallel for
        for (auto j = i+1; j < n; ++j)
        {
            (*matrixPtr)[i][j] = (*matrixPtr)[i][j] + (*matrixPtr)[j][i];
            (*matrixPtr)[j][i] = (*matrixPtr)[i][j] - (*matrixPtr)[j][i];
            (*matrixPtr)[i][j] = (*matrixPtr)[i][j] - (*matrixPtr)[j][i];
        }
    }
    // auto end = omp_get_wtime();
    // printf("time: %d \n", ((end-begin)));
}