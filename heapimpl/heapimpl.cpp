#include "pch.h"
#include <vector>


void swap(std::vector<int>& unsortedArray, int idx1, int idx2) {
  int tmp = unsortedArray[idx1];
  unsortedArray[idx1] = unsortedArray[idx2];
  unsortedArray[idx2] = tmp;
}

void heapify(std::vector<int>& unsortedArray, int lastNonLeafIdx = -1) {

    if (lastNonLeafIdx == -1) {
        //
        lastNonLeafIdx = unsortedArray.size() / 2 - 1;
    }
    
    int currNodeIdx = lastNonLeafIdx;
    size_t totalElCnt = unsortedArray.size();
    while (currNodeIdx >= 0) {
        
        int firstChildIdx = currNodeIdx*2 +1;
        int secondChildIdx = currNodeIdx*2 + 2;         
        
        if (firstChildIdx < totalElCnt && unsortedArray[firstChildIdx] > unsortedArray[currNodeIdx]) {
            swap(unsortedArray, firstChildIdx, currNodeIdx);
            heapify(unsortedArray, firstChildIdx); 
        }
        if (secondChildIdx < totalElCnt && unsortedArray[secondChildIdx] > unsortedArray[currNodeIdx]) {
            swap(unsortedArray, secondChildIdx, currNodeIdx);
            heapify(unsortedArray, secondChildIdx);
        }
        
        currNodeIdx--;    
    }
    
}


void heapSort(std::vector<int>& unsortedArray) {

    std::vector<int> sortedArray;

    //build the heap
    //take the max element from the root node
    //then remove the root node and place the last element in its place and repeat
    while (unsortedArray.empty() == false) {
        heapify(unsortedArray);
        sortedArray.push_back(unsortedArray.front());
        unsortedArray.erase(unsortedArray.begin());  //this could be not optimal
        if (unsortedArray.size() > 1) {
          int val = unsortedArray.back();
          unsortedArray.erase(unsortedArray.end()-1);
          unsortedArray.insert(unsortedArray.begin(), val);
        }        
    }
    
    unsortedArray = sortedArray;

}


TEST(HeapImpl, heapifyTest) {

    std::vector<int> unsortedArray = { 3, 6, 9, 12, 4, 1 };
    
    heapify(unsortedArray);
    
    ASSERT_EQ(12, unsortedArray[0]);
    ASSERT_EQ(6, unsortedArray[1]);
    ASSERT_EQ(9, unsortedArray[2]);
    ASSERT_EQ(3, unsortedArray[3]);
    ASSERT_EQ(4, unsortedArray[4]);
    ASSERT_EQ(1, unsortedArray[5]);

}


TEST(HeapImpl, heapSortTest) {
    
    std::vector<int> unsortedArray = { 3, 6, 9, 12, 4, 1 };
    
    heapSort(unsortedArray);
    
    ASSERT_EQ(12, unsortedArray[0]);
    ASSERT_EQ(9, unsortedArray[1]);
    ASSERT_EQ(6, unsortedArray[2]);
    ASSERT_EQ(4, unsortedArray[3]);
    ASSERT_EQ(3, unsortedArray[4]);
    ASSERT_EQ(1, unsortedArray[5]);
    
}






