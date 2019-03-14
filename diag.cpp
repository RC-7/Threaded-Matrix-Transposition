#include <vector>
#include <memory>
#include <omp.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <typeinfo>
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
    double begin,end;
    begin = omp_get_wtime();

     auto begins = clock();
    #pragma omp for 
    for (auto i = 0; i < n; ++i)


    {
        // if (i==0)
        //      begin = omp_get_wtime();

        // #pragma omp parallel for
        for (auto j = i+1; j < n; ++j)
        {
            (*matrixPtr)[i][j] = (*matrixPtr)[i][j] + (*matrixPtr)[j][i];
            (*matrixPtr)[j][i] = (*matrixPtr)[i][j] - (*matrixPtr)[j][i];
            (*matrixPtr)[i][j] = (*matrixPtr)[i][j] - (*matrixPtr)[j][i];
        }

        // if (i==0)
        //      end = omp_get_wtime();
    }
      end= omp_get_wtime();
      auto ends = clock();

      double times=end-begin;

    std::cout<<end-begin<<std::endl;
    std::cout<<ends-begins<<std::endl;
    std::cout<<typeid(times).name()<<std::endl;


    printf("time: %f s \n", times);
}