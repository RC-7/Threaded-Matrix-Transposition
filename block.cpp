#include <vector>
#include <memory>
#include <iostream>
using namespace std;


void swap(int &x, int &y)
{
	x=x+y;
	y=x-y;
	x=x-y;
}

void swapBlocks(std::vector<std::vector<int>> &matrix)
{
	swap(matrix[0][2],matrix[2][0]);
	swap(matrix[1][2],matrix[3][0]);
	swap(matrix[0][3],matrix[2][1]);
	swap(matrix[1][3],matrix[3][1]);
}

void getSubBlocksTransposed (std::vector<std::vector<int>> &matrix)
{
	//For now assuming even n
	auto n = matrix.size();
	std::vector<std::vector<int>> A(2, std::vector<int>(2, 0));
	std::vector<std::vector<int>> B(2, std::vector<int>(2, 0));
	swap(matrix[0][1],matrix[1][0]);
	swap(matrix[2][1],matrix[3][0]);
	swap(matrix[0][3],matrix[1][2]);
	swap(matrix[2][3],matrix[3][2]);
	swapBlocks(matrix);
	

}


std::vector<std::vector<int>> blockTranspose(std::shared_ptr<std::vector<std::vector<int>>> matrixPtr)
{
    // transpose by only accessing matrix elements with dereference operator to avoid copy
    // initially just dereferencing to check if it works
    auto matrix = *matrixPtr;
    auto n = matrix.size();
    auto subBlockSize=n/2;
    // cout<<"N equals"<<n<<endl;
   if(n==4)
   {
   		 getSubBlocksTransposed(matrix);
   }
   else
   {

   }

    return matrix;
}