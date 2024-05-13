#include "pch.h"
#include <vector>
#include <iostream>

int partition(std::vector<int>& unsortedArray, int startIdx, int endIdx) {

    int pivot = endIdx;
    int firstHigh = startIdx;
    for (int i = startIdx; i < endIdx; i++) {
        if (unsortedArray[i] < unsortedArray[pivot]) {
            int firstHighVal = unsortedArray[firstHigh];
            unsortedArray[firstHigh] = unsortedArray[i];
            unsortedArray[i] = firstHighVal;
            firstHigh++;    
        }        
    }
    
    int pivotVal = unsortedArray[pivot];
    unsortedArray[pivot] = unsortedArray[firstHigh];
    unsortedArray[firstHigh] = pivotVal;
    
    return firstHigh;     
}


void quickSort(std::vector<int>& unsortedArray, int startIdx = -1, int endIdx = -1) {

    if (startIdx == -1 && endIdx == -1) {
        startIdx = 0;
        endIdx = (int)unsortedArray.size()-1;
    }

    if ((endIdx - startIdx) > 0) {
        int pivot = partition(unsortedArray, startIdx, endIdx);
        quickSort(unsortedArray, startIdx, pivot-1);
        quickSort(unsortedArray, pivot+1, endIdx);  
    } 
    
}


TEST(QuickSort, basicTest) {

    std::vector<int> unsortedArray = { 3, 5, 2 , 4, 1, 8 };
    quickSort(unsortedArray);
    ASSERT_EQ(1, unsortedArray[0]);
    
    std::vector<int> unsortedArray2 = { 7, 35, 59, 2, 19, 98, 1005, 587, 74 };
    quickSort(unsortedArray2);
    ASSERT_EQ(2, unsortedArray2[0]);

}