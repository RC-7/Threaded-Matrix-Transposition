#include <vector>
#include <memory>
#include <iostream>
using namespace std;


// void swap(int &x, int &y)
// {
// 	x=x+y;
// 	y=x-y;
// 	x=x-y;
// }
void swap(auto matrixPtr, int xSwap1,int ySwap1, int xSwap2, int ySwap2)
{
	(*matrixPtr)[xSwap1][ySwap1]=(*matrixPtr)[xSwap1][ySwap1]+(*matrixPtr)[xSwap2][ySwap2];
	(*matrixPtr)[xSwap2][ySwap2]=(*matrixPtr)[xSwap1][ySwap1]-(*matrixPtr)[xSwap2][ySwap2];
	(*matrixPtr)[xSwap1][ySwap1]=(*matrixPtr)[xSwap1][ySwap1]-(*matrixPtr)[xSwap2][ySwap2];
	
}


void blockTranspose(std::shared_ptr<std::vector<std::vector<int>>> matrixPtr,int subBlockSize, int startX,int startY)
{
	 
	// cout<<"x: "<< startX<<" y: "<<startY<<endl;	 
	 if(subBlockSize==2)
	 {

	 	swap(matrixPtr,startX,startY+1,startX+1,startY);
	 }
	 else
	 {
	 	auto newSublockSize=subBlockSize/2;
	 	blockTranspose(matrixPtr, newSublockSize, startX, startY);
	 	blockTranspose(matrixPtr, newSublockSize, startX+newSublockSize, startY);
	 	blockTranspose(matrixPtr, newSublockSize, startX, startY+newSublockSize);
	 	blockTranspose(matrixPtr, newSublockSize, startX+newSublockSize, startY+newSublockSize);

	 }
	 
}



// std::vector<std::vector<int>> blockTranspose(std::shared_ptr<std::vector<std::vector<int>>> matrixPtr)
// {
//     // transpose by only accessing matrix elements with dereference operator to avoid copy
//     // initially just dereferencing to check if it works
//     auto matrix = *matrixPtr;
//     auto n = matrix.size();
//     auto subBlockSize=n/2;
//     // cout<<"N equals"<<n<<endl;
//    if(n==4)
//    {
//    		 getSubBlocksTransposed(matrix);
//    }
//    else
//    {

//    }

//     return matrix;
// }

