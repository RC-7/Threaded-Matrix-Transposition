#include <vector>
#include <memory>

// change to this when pointer works
// void diagTranspose(std::shared_ptr<std::vector<std::vector<int>>> matrixPtr)
std::vector<std::vector<int>> diagTranspose(std::shared_ptr<std::vector<std::vector<int>>> matrixPtr)
{
    // transpose by only accessing matrix elements with dereference operator to avoid copy
    // initially just dereferencing to check if it works
    auto matrix = *matrixPtr;
    auto n = matrix.size();

    for (auto i = 0; i < n; ++i)
    {
        for (auto j = i+1; j < n; ++j)
        {
            matrix[i][j] = matrix[i][j] + matrix[j][i];
            matrix[j][i] = matrix[i][j] - matrix[j][i];
            matrix[i][j] = matrix[i][j] - matrix[j][i];
        }
    }

    return matrix;
}