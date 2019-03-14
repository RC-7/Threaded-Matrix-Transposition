#include <vector>
#include <memory>
#include <iostream>
using namespace std;



void swap(std::shared_ptr<std::vector<std::vector<int>>> matrixPtr, int xSwap1,int ySwap1, int xSwap2, int ySwap2)
{
	(*matrixPtr)[xSwap1][ySwap1]=(*matrixPtr)[xSwap1][ySwap1]+(*matrixPtr)[xSwap2][ySwap2];
	(*matrixPtr)[xSwap2][ySwap2]=(*matrixPtr)[xSwap1][ySwap1]-(*matrixPtr)[xSwap2][ySwap2];
	(*matrixPtr)[xSwap1][ySwap1]=(*matrixPtr)[xSwap1][ySwap1]-(*matrixPtr)[xSwap2][ySwap2];
	
}


void elementBlockTranspose(std::shared_ptr<std::vector<std::vector<int>>> matrixPtr,int subBlockSize, int startX,int startY)
{
	 
	 if(subBlockSize==2)
	 {

	 	swap(matrixPtr,startX,startY+1,startX+1,startY);
	 }
	 else
	 {
	 	auto newSublockSize=subBlockSize/2;
	 	elementBlockTranspose(matrixPtr, newSublockSize, startX, startY);
	 	elementBlockTranspose(matrixPtr, newSublockSize, startX+newSublockSize, startY);
	 	elementBlockTranspose(matrixPtr, newSublockSize, startX, startY+newSublockSize);
	 	elementBlockTranspose(matrixPtr, newSublockSize, startX+newSublockSize, startY+newSublockSize);

	 }
	 
}

void swapWholeBlock (std::shared_ptr<std::vector<std::vector<int>>> matrixPtr,int i, int j)
{
	swap(matrixPtr,i,j,j,i);
	swap(matrixPtr,i+1,j,j+1,i);
	swap(matrixPtr,i,j+1,j,i+1);
	swap(matrixPtr,i+1,j+1,j+1,i+1);
}

void allBlocksTranspose(std::shared_ptr<std::vector<std::vector<int>>> matrixPtr, int matrixSize)
{
	for(int i=0;i<matrixSize;i=i+2)
	{
		for(int j=i;j<matrixSize;j=j+2)
		{
			if(i!=j)
			{
				swapWholeBlock(matrixPtr,i,j);
			}
		}
	}
		
}


